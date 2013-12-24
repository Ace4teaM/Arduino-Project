#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    udpSocket = new QUdpSocket(this);
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":application/app_icon"));

    // initialise la barre d'outils
    ui->toolBar->addAction("Ajouter Equipement", this, SLOT(tbAddEquipement()));
    ui->toolBar->addAction("Arranger", this, SLOT(tbRearrange()));

    // initialise le menu principale
    connect( ui->actionSauvegrader_sous, SIGNAL(triggered()), this,SLOT(actionSauvegarder_sous()));
    connect( ui->actionOuvrir, SIGNAL(triggered()), this,SLOT(actionOuvrir()));
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

bool MainWindow::findNetwork(){
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    if ( !ifaces.isEmpty() )
    {
      for(int i=0; i < ifaces.size(); i++)
      {
        qDebug() << "Interface: " << ifaces[i].humanReadableName();
        qDebug() << "   MAC:" << ifaces[i].hardwareAddress();

        unsigned int flags = ifaces[i].flags();
        bool isLoopback = (bool)(flags & QNetworkInterface::IsLoopBack);
        bool isP2P = (bool)(flags & QNetworkInterface::IsPointToPoint);
        bool isRunning = (bool)(flags & QNetworkInterface::IsRunning);

        // If this interface isn't running, we don't care about it
        if ( !isRunning ) continue;

        // We only want valid interfaces that aren't loopback/virtual and not point to point
        if ( !ifaces[i].isValid() || isLoopback || isP2P ) continue;

        // Obtient l'IP
        QList<QHostAddress> addresses = ifaces[i].allAddresses();
        for(int a=0; a < addresses.size(); a++)
        {
          // Ignore local host
          if ( addresses[a] == QHostAddress::LocalHost ) continue;

          // Ignore non-ipv4 addresses
          if ( !addresses[a].toIPv4Address() ) continue;

          // Obtient L'IP
          QString ip = addresses[a].toString();
          qDebug() << "   IP: " << ip;
        }
      }
    }
    return true;
}

bool MainWindow::findArduino(){
    udpSocket->bind(QHostAddress::Broadcast, 7755);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(on_findArduinoResponse()));
    return true;
}

/*--------------------------------------------------------------------------------------
 *  SLOT
 *--------------------------------------------------------------------------------------*/

void MainWindow::on_findArduinoResponse(){
    ui->label_connection_status->setText("Recherche...Response");
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        //processTheDatagram(datagram);
    }
}

void MainWindow::on_pushButton_findArduino_clicked(){
    findArduino();
    ui->label_connection_status->setText("Recherche...");
}

void MainWindow::on_pushButton_connect_clicked()
{
    findNetwork();
}

void MainWindow::tbAddEquipement()
{
    Equipment equipment;
    equipment.equipmentId   = 100;
    equipment.type = QString("light");
    equipment.name = QString("Lumiere Salon");
    equipment.posX = 0;
    equipment.posY = 0;
    equipment.posZ = 0;
    this->ui->graphicsView->addEquipment(equipment);
}

void MainWindow::tbRearrange()
{
    this->ui->graphicsView->rearrangeView();
}


/*
 * ACTION MENU
 * Ouvrir ...
*/
void MainWindow::actionOuvrir()
{
    // Ouvre le document
    QFileDialog dialog(this, QString(), QString());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    QStringList filters;
    filters << "Fichier XML (*.xml)" << "Fichier RIFF (*.riff)";
    dialog.setNameFilters(filters);
    if (dialog.exec() != QDialog::Accepted)
        return;
    QString selectedFilter = dialog.selectedNameFilter();
    QString filename = dialog.selectedFiles()[0];

    //RIFF
    if(selectedFilter.contains(".riff")){
        //ouvre le fichier
        QFile fp( filename );
        if( !fp.open( QIODevice::ReadOnly ) ){
            QRESULT(Result::CantOpenFile);
            return;
        }

        //obtient les données
        char* data = fp.readAll().data();
        PTR ptr = {data,data+fp.size(),data};

        //charge le document
        this->ui->graphicsView->fromRIFF(&ptr);

        fp.close();
    }
    //XML
    else if(selectedFilter.contains(".xml")){
        //ouvre le fichier
        QFile fp( filename );
        if( !fp.open( QIODevice::ReadOnly | QIODevice::Text ) ){
            QRESULT(Result::CantOpenFile);
            return;
        }

        //charge le document
        QDomDocument dom;
        dom.setContent(fp.readAll());
        this->ui->graphicsView->fromXML(dom);

        fp.close();
    }

    QRESULT_OK();
}

/*
 * ACTION MENU
 * Sauvegarder sous ...
*/
void MainWindow::actionSauvegarder_sous()
{
    QFileDialog dialog(this, QString(), QString());
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList filters;
    filters << "Fichier XML (*.xml)" << "Fichier RIFF (*.riff)";
    dialog.setNameFilters(filters);
    if (dialog.exec() != QDialog::Accepted)
        return;
    QString selectedFilter = dialog.selectedNameFilter();
    QString filename = dialog.selectedFiles()[0];

    //sauvegarde le fichier

    //RIFF
    if(selectedFilter.contains(".riff")){
        //crée le fichier
        QFile outFile( filename );
        if( !outFile.open( QIODevice::WriteOnly | QIODevice::Truncate ) ){
            QRESULT(Result::CantSaveFile);
            return;
        }

        QDataStream stream( &outFile );
        stream.setByteOrder(QDataStream::LittleEndian);

        //génère le document
        char buf[1024*10];
        PTR mem={buf,buf+sizeof(buf),buf};
        this->ui->graphicsView->toRIFF(&mem);
        stream.writeRawData(mem.up,(uint)(mem.ptr-mem.up));

        outFile.close();
    }
    //XML
    else if(selectedFilter.contains(".xml")){
        //crée le fichier
        QFile outFile( filename );
        if( !outFile.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) ){
            QRESULT(Result::CantSaveFile);
            return;
        }

        QTextStream stream( &outFile );
        QDomDocument dom;
        dom.appendChild(dom.createElement("root"));
        this->ui->graphicsView->toXML(dom);
        stream << dom.toString();

        outFile.close();
    }

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
