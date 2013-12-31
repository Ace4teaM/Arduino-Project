#include "cominterface.h"

ComInterface::ComInterface()
{
    msg_size=1024;
    msg = (char*)malloc(msg_size);
}

ComInterface::~ComInterface()
{
    if(msg)
        free(msg);
    msg=0;
    msg_size=0;
}

bool ComInterface::begin( ){
    if(msg==0)
        return false;
    bptr(&ptr,msg,msg_size);
    return true;
}

void ComInterface::end( ){
    ptr.down = ptr.ptr;
}

void ComInterface::send( QHostAddress & address ){

    socket.writeDatagram(ptr.up,bsize(&ptr),address,ARDUINO_COM_PORT);
    QEventLoop loop;
    QObject::connect(&socket, SIGNAL(readyRead()), &loop, SLOT(quit()));
    // Execute
    qDebug() << "begin";
    loop.exec();
    qDebug() << "end";
}

bool ComInterface::put(const char* title, const char* value ){
    return xarg_encode_field(&ptr,title,value);
}


bool ComInterface::put(QString title, QString value ){
    return xarg_encode_field(&ptr,title.toLatin1().data(),value.toLatin1().data());
}


void ComInterface::sendText( const QByteArray & data, QHostAddress & address ){

    QUdpSocket socket;
    socket.writeDatagram(data,data.length(),address,ARDUINO_COM_PORT);
}


bool ComInterface::makeText( const QByteArray & data ){
    return bwrite(&ptr,data.data(),data.size());
}

bool ComInterface::makeMessage( QAssocList & data ){
    for (QAssocList::iterator it=data.begin(); it!=data.end(); ++it)
      if(!put(it->first,it->second.toString()))
              return false;
    return true;
}

