#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <l1/result.cpp>
#include <l1/xarg.cpp>
#include <l1/str.cpp>
#include <l2/cxarg.cpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    udpSocket = new QUdpSocket(this);
    ui->setupUi(this);

    ui->toolBar->addAction("Add Equipement", this, SLOT(tbAddEquipement()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isConnected()
{
    QTcpSocket socket;
    socket.connectToHost("www.google.com", 80);
    // Renvoie false si pas connectée, ou si google ne marche pas
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

void MainWindow::tbAddEquipement()
{
    Equipement equipement;
    equipement.type = QString("light");
    equipement.name = QString("Lumiere Salon");
    this->ui->graphicsView->addEquipement(equipement);
}

/*
void Server::initSocket()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 7755);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void Server::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        processTheDatagram(datagram);
    }
}*/
