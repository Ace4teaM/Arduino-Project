#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    udpSocket = new QUdpSocket(this);
    ui->setupUi(this);

    ui->toolBar->addAction("Ajouter Equipement", this, SLOT(tbAddEquipement()));
    ui->toolBar->addAction("Arranger", this, SLOT(tbRearrange()));
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
    Equipment equipment;
    equipment.equipmentId   = 100;
    equipment.type = QString("light");
    equipment.name = QString("Lumiere Salon");
    this->ui->graphicsView->addEquipment(equipment);
}

void MainWindow::tbRearrange()
{
    this->ui->graphicsView->rearrangeView();
}

void MainWindow::on_btnSaveConfig_clicked()
{
    //obtient le fichier de destination
    QString filename = QFileDialog::getSaveFileName(this, QString(), QString(), tr("Fichier XML (*.xml)"));
    if(filename.isNull()){
        QRESULT_OK();
        return;
    }

    //crée le fichier
    QFile outFile( filename );
    if( !outFile.open( QIODevice::WriteOnly | QIODevice::Text ) ){
        QRESULT(Result::CantSaveFile);
        return;
    }

    //génère le document
    QDomDocument dom;
    dom.appendChild(dom.createElement("root"));
    this->ui->graphicsView->toXML(dom);

    //sauvegarde le fichier
    QTextStream stream( &outFile );
    stream << dom.toString();

    outFile.close();
    QRESULT_OK();
}

void MainWindow::on_actionSauvegarder_sous_clicked()
{
    //obtient le fichier de destination
    QString filename = QFileDialog::getSaveFileName(this, QString(), QString(), tr("Fichier XML (*.xml)"));
    if(filename.isNull()){
        QRESULT_OK();
        return;
    }

    //crée le fichier
    QFile outFile( filename );
    if( !outFile.open( QIODevice::WriteOnly | QIODevice::Text ) ){
        QRESULT(Result::CantSaveFile);
        return;
    }

    //génère le document
    char buf[1024*10];
    PTR mem={buf,buf+sizeof(buf),buf};
    this->ui->graphicsView->toRIFF(&mem);

    outFile.close();
    QRESULT_OK();
}


void MainWindow::on_btnLoadConfig_clicked()
{
    //obtient le fichier de destination
    QString filename = QFileDialog::getOpenFileName(this, QString(), QString(), tr("Fichier XML (*.xml)"));
    if(filename.isNull()){
        QRESULT_OK();
        return;
    }

    //ouvre le fichier
    QFile fp( filename );
    if( !fp.open( QIODevice::ReadOnly | QIODevice::Text ) ){
        QRESULT(Result::CantReadFile);
        return;
    }

    //charge le document
    QDomDocument dom;
    dom.setContent(fp.readAll());
    this->ui->graphicsView->fromXML(dom);

    fp.close();
    QRESULT_OK();
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
