#ifndef MYJSONWORK_H
#define MYJSONWORK_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

class myjsonwork
{
public:
    myjsonwork();
    myjsonwork(QByteArray data);
    static QString getstrbyvar(QString var,QString data);
    static QStringList handledata(QString data);


    static QString getcontentbytag(QString tag,QString data);

};

#endif // MYJSONWORK_H
