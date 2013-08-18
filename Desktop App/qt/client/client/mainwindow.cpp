#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    udpSocket = new QUdpSocket(this);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::FindNetwork(){
    QHostAddress adr("192.168.1.29");
    ui->label_connection_status->setText(tr("Connecting to ")+adr.toString());
    QByteArray datagram = "Hello World\0";
    if(!udpSocket->writeDatagram(datagram.data(), datagram.size(), adr, 45454)){
        ui->label_connection_status->setText(tr("Failed to send !"));
        return false;
    }
    ui->label_connection_status->setText(tr("Sended"));
    return false;
}

void MainWindow::on_pushButton_connect_clicked()
{
    FindNetwork();
}
