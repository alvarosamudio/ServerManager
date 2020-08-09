#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QString>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        QTimer *timer;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()),
              this, SLOT(StatusUpdate()));
        timer->start(10000);
    StatusUpdate();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::StatusUpdate(){
    pid_t apache = system("pidof -s apache2");
    pid_t mysqld = system("pidof -s mysqld");
    pid_t ftp = system("pidof -s filezilla");
    if(apache != 256)
        ui->label_8->setText("Running");
    else
        ui->label_8->setText("Not Running");
    if(mysqld != 256)
        ui->label_5->setText("Running");
    else
        ui->label_5->setText("Not Running");
    if(ftp != 256)
        ui->label_7->setText("Running");
    else
        ui->label_7->setText("Not Running");
}

void MainWindow::bash(QString command)
{
    QProcess *p = new QProcess( this );

    if (p)
    {
      p->setEnvironment( QProcess::systemEnvironment() );
      p->setProcessChannelMode( QProcess::MergedChannels );

      p->start( command );
      p->waitForStarted();

      connect( p, SIGNAL(readyReadStandardOutput()), this, SLOT(ReadOut()) );
      connect( p, SIGNAL(readyReadStandardError()), this, SLOT(ReadErr()) );
    }

}

void MainWindow::ReadOut(){
    QProcess *p = dynamic_cast<QProcess *>( sender() );

    if (p){
        ui->textBrowser->append( p->readAllStandardOutput() );
    }
}
void MainWindow::ReadErr(){
    QProcess *p = dynamic_cast<QProcess *>( sender() );

    if (p){
        ui->textBrowser->append( p->readAllStandardError() );
    }
}

void MainWindow::on_apache_clicked()
{
    bash("service apache2 restart");
}

void MainWindow::on_mysql_clicked()
{
    bash("service mysql restart");
}

void MainWindow::on_ftp_clicked()
{
    bash("service filezilla restart");
}

void MainWindow::on_startall_clicked()
{
    bash("service apache2 restart");
    bash("service mysql restart");
    bash("service filezilla restart");

}

void MainWindow::on_stopall_clicked()
{
    bash("service apache2 stop");
    bash("service mysql stop");
    bash("service filezilla stop");
}

void MainWindow::on_refreshall_clicked()
{
    StatusUpdate();
}
