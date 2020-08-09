#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_apache_clicked();
    void on_mysql_clicked();
    void on_ftp_clicked();
    void bash(QString command);
    void ReadOut();
    void ReadErr();
    void on_refreshall_clicked();
    void StatusUpdate();
    void on_startall_clicked();
    void on_stopall_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
