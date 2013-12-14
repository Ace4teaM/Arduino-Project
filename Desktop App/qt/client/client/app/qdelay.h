#ifndef QDELAY_H
#define QDELAY_H

#include <QObject>
#include <QString>
#include <QTime>
#include "result.h"
#include <QMetaType>

class QDelay
{
public:
    //toString formats
    enum{
        HourFormat,
        DecimalFormat
    };

    QDelay();
    QDelay(const QTime& t);
    QDelay(long timestamp);
    QDelay(int h,int m,int s);
    void fromTime(int h,int m,int s);
    void fromSeconds(long s);
    void toTime(int* h,int* m,int* s);
    long hours() const;
    long minutes() const;
    long seconds() const;
    long time() const;
    double toDecimal() const;
    QString toString() const;
    QString toString(int format) const;
    //operateurs
    inline bool operator += (const QTime &t)
    {
        fromTime(this->hours()+t.hour(),this->minutes()+t.minute(),this->seconds()+t.second());
        return true;
    }

    inline const QDelay operator+(const QTime &t)
    {
        return QDelay(this->hours()+t.hour(),this->minutes()+t.minute(),this->seconds()+t.second());
    }

    inline bool operator += (const QDelay &t)
    {
        this->timestamp += t.time();
        return true;
    }

    inline const QDelay operator+(const QDelay &t)
    {
        return QDelay(this->time()+t.time());
    }
private:
    long timestamp;//nombre de secondes
};

Q_DECLARE_METATYPE(QDelay)

#endif // QDELAY_H
