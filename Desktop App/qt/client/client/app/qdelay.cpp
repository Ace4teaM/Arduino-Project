#include "qdelay.h"

QDelay::QDelay()
{
    this->timestamp = 0;
}

QDelay::QDelay(const QTime& t){
    this->timestamp = (long)(t.hour()*3600 + t.minute()*60 + t.second());
}


QDelay::QDelay(long timestamp)
{
    this->timestamp = timestamp;
}

QDelay::QDelay(int h,int m,int s){
    fromTime(h,m,s);
}

void QDelay::fromTime(int h,int m,int s){
    this->timestamp = (long)(h*3600 + m*60 + s);
}

void QDelay::fromSeconds(long s){
    this->timestamp = s;
}

void QDelay::toTime(int* h,int* m,int* s){
    *h = hours();
    *m = minutes();
    *s = seconds();
}

long QDelay::hours() const{
    return (timestamp / 3600);
}

long QDelay::minutes() const{
    return (timestamp % 3600) / 60;
}

long QDelay::seconds() const{
    return (timestamp % 3600) % 60;
}

long QDelay::time() const{
    return timestamp;
}

double QDelay::toDecimal() const{
    return ((double)timestamp / 3600.0);
    //return ((double)hours()) + ((double)minutes()/60.0) + ((double)minutes()/3600.0);
}

QString QDelay::toString() const{
    //QDelay::HourFormat
    return QString::number(hours())+":"+
            QString("%1").arg(QString::number(minutes()), 2, QChar('0'))+":"+
            QString("%1").arg(QString::number(seconds()), 2, QChar('0'));
}

QString QDelay::toString(int format) const{
    switch(format){
        case QDelay::DecimalFormat:
            QPRINT("decimale="+QString::number(toDecimal()));
            return QString::number(toDecimal(),'f',2);
    }

    //QDelay::HourFormat
    return toString();
}
