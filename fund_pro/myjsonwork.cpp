#include "myjsonwork.h"
#include "qdebug.h"
#include <iostream>
using namespace std;
myjsonwork::myjsonwork()
{

}

myjsonwork::myjsonwork(QByteArray data)
{

}

QString myjsonwork::getstrbyvar(QString var, QString data)
{
    QString str;
    int pos = data.indexOf(var);
    if(pos < 0)
        return NULL;
    str = data.mid(pos+(var.length()),20);

    QStringList strlist = str.split("\"");
    str = strlist.at(1);
    //qDebug() << QString("var fs_name").length();
    qDebug() << str;
    return str;
}

QStringList myjsonwork::handledata(QString data)
{
    QStringList datalist;
    QString body = getcontentbytag("tbody",data);
    if(body == NULL)
        return datalist;
    QString tmp;
    int i = 0;

    do{
        i = 0;
        tmp = getcontentbytag("tr",body);
        if(tmp == NULL)
            return datalist;
        while(i < tmp.length()){
            if(tmp.at(i) > 57 || tmp.at(i) < 45 )
                tmp.remove(i,1);
            else
                i++;
        }
        datalist.append(tmp);
        body = body.mid(body.indexOf("</tr>")+QString("</tr>").length());
    }while(body != NULL);


    return datalist;
}

QString myjsonwork::getcontentbytag(QString tag,QString data)
{
    int bpos = data.indexOf("<"+tag+">");
    int epos = data.indexOf("</"+tag+">");
    if(bpos < 0 || epos <0)
        return NULL;


    QString str;
    str = data.mid(bpos+QString("<"+tag+">").length(),epos-bpos-QString("<"+tag+">").length());
    //qDebug() << bpos << epos;
    return str;
}

