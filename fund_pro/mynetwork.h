#ifndef MYNETWORK_H
#define MYNETWORK_H
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtCore>
#include <iostream>
using namespace std ;

class mynetwork : public QObject
{
    Q_OBJECT
public:
    mynetwork();

    static QByteArray geturldata(QString url);
};



#endif // MYNETWORK_H
