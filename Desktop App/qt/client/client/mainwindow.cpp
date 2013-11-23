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

bool MainWindow::isConnected()
{
    QTcpSocket socket;
    socket.connectToHost("www.google.com", 80);
    // Renvoie false si pas connecté, ou si google ne marche pas
    return socket.waitForConnected(1000);
}

bool MainWindow::FindNetwork(){
    static int cnt=0;
    cnt++;
    QHostAddress adr("192.168.1.64");
    ui->label_connection_status->setText(tr("Connecting to ")+adr.toString());
    QByteArray datagram = "Hello World\0";
    if(!udpSocket->writeDatagram(datagram.data(), datagram.size(), adr, 45454)){
        ui->label_connection_status->setText(tr("Failed to send !"));
        return false;
    }
    ui->label_connection_status->setText(tr("Sended ")+QString::number(cnt));
    return true;
}

void MainWindow::on_pushButton_connect_clicked()
{
    FindNetwork();
}
