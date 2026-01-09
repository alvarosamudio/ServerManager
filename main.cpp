#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication> // Added for QCoreApplication::applicationDirPath()
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();

  QStringList potentialPaths;
  potentialPaths
      << QCoreApplication::applicationDirPath() + "/translations"
      << QCoreApplication::applicationDirPath() +
             "/../share/servermanager/translations" // For some bundle layouts
      << "/usr/share/servermanager/translations"    // Standard Linux install
      << "translations";                            // Local dev

  for (const QString &locale : uiLanguages) {
    const QString baseName = "servermanager_" + QLocale(locale).name();

    for (const QString &path : potentialPaths) {
      if (translator.load(baseName, path)) {
        a.installTranslator(&translator);
        goto translation_found;
      }
      // Try without country code
      if (translator.load("servermanager_" +
                              QLocale(locale).name().split('_').first(),
                          path)) {
        a.installTranslator(&translator);
        goto translation_found;
      }
    }

    // Fallback to resource system if setup
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      goto translation_found;
    }
  }

translation_found:

  MainWindow w;
  w.show();

  return a.exec();
}
