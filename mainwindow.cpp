#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProcess>
#include <QString>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QTimer *timer;
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(StatusUpdate()));
  timer->start(10000);
  StatusUpdate();
}
MainWindow::~MainWindow() { delete ui; }
/* Robust Status Update */
void MainWindow::StatusUpdate() {
  // Check Apache
  // pidof returns 0 if found, 1 if not.
  bool apacheRunning =
      (QProcess::execute("pidof", QStringList() << "-s" << "apache2") == 0);
  if (apacheRunning)
    ui->label_8->setText(tr("Running"));
  else
    ui->label_8->setText(tr("Not Running"));

  // Check MariaDB
  bool mysqlRunning =
      (QProcess::execute("pidof", QStringList() << "-s" << "mariadb") == 0);
  if (mysqlRunning)
    ui->label_5->setText(tr("Running"));
  else
    ui->label_5->setText(tr("Not Running"));

  // Check FTP (FileZilla)
  bool ftpRunning =
      (QProcess::execute("pidof", QStringList() << "-s" << "filezilla") == 0);
  if (ftpRunning)
    ui->label_7->setText(tr("Running"));
  else
    ui->label_7->setText(tr("Not Running"));
}

void MainWindow::bash(QString command) {
  QProcess *p = new QProcess(this);

  if (p) {
    // Ensure the process is deleted when done to avoid memory leaks
    connect(p, SIGNAL(finished(int, QProcess::ExitStatus)), p,
            SLOT(deleteLater()));

    p->setEnvironment(QProcess::systemEnvironment());
    p->setProcessChannelMode(QProcess::MergedChannels);

    // Split command and arguments for better robustness
    QStringList parts = command.split(' ', Qt::SkipEmptyParts);
    if (!parts.isEmpty()) {
      QString program = parts.takeFirst();
      p->start(program, parts);
      // Only wait for started, don't block main thread indefinitely
      if (!p->waitForStarted()) {
        ui->textBrowser->append(tr("Failed to start command: ") + command);
        p->deleteLater();
        return;
      }

      connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(ReadOut()));
      connect(p, SIGNAL(readyReadStandardError()), this, SLOT(ReadErr()));
    }
  }
}

void MainWindow::ReadOut() {
  QProcess *p = dynamic_cast<QProcess *>(sender());

  if (p) {
    ui->textBrowser->append(p->readAllStandardOutput());
  }
}
void MainWindow::ReadErr() {
  QProcess *p = dynamic_cast<QProcess *>(sender());

  if (p) {
    ui->textBrowser->append(p->readAllStandardError());
  }
}

void MainWindow::on_apache_clicked() { bash("service apache2 restart"); }

void MainWindow::on_mysql_clicked() { bash("service mariadb restart"); }

void MainWindow::on_ftp_clicked() { bash("service filezilla restart"); }

void MainWindow::on_startall_clicked() {
  bash("service apache2 restart");
  bash("service mariadb restart");
  bash("service filezilla restart");
}

void MainWindow::on_stopall_clicked() {
  bash("service apache2 stop");
  bash("service mariadb stop");
  bash("service filezilla stop");
}

void MainWindow::on_refreshall_clicked() { StatusUpdate(); }
