#ifndef COMINTERFACE_H
#define COMINTERFACE_H

#include <QHostAddress>
#include <QUdpSocket>
#include <QEventLoop>

#include <app/qassoclist.h>

#include <l1/result.h>
#include <l1/xarg.h>
#include <l1/str.h>

#define ARDUINO_COM_PORT 12345

class ComInterface
{
public:
    ComInterface();
    ~ComInterface();
    bool begin( );
    void end( );
    void send( QHostAddress & address );
    bool put(const char* name, const char* value );
    bool put(QString title, QString value );
    static void sendText( const QByteArray & data, QHostAddress & address );
    bool makeMessage( QAssocList & data );
    void makeText( const QByteArray & data );
private:
    QUdpSocket socket;
    PTR ptr;
    char* msg;
    size_t msg_size;
};

#endif // COMINTERFACE_H
