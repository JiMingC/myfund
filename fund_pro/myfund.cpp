#include "myfund.h"
#include "mynetwork.h"
#include "myjsonwork.h"
#include "qdebug.h"
myfund::myfund()
{

}

myfund::myfund(QString code)
{
    QByteArray data = mynetwork::geturldata(QString("http://fund.eastmoney.com/pingzhongdata/"+code+".js") );

    fS_name = myjsonwork::getstrbyvar("fS_name",data);
    fS_code = myjsonwork::getstrbyvar("fS_code",data);
    if(fS_code == NULL || fS_name == NULL){
        status = 0;
        return;
    }
    QByteArray data2 = mynetwork::geturldata(QString("http://fund.eastmoney.com/f10/F10DataApi.aspx?type=lsjz&code="+code) );

    QString str = myjsonwork::getcontentbytag("tbody",QString(data2));
    QStringList list = myjsonwork::handledata(data2);
    if(list.isEmpty())
        return;
    getinfofromStringList(list);

    //qDebug() << list[0]<<list[1];
    status = 1;
}

void myfund::getinfofromStringList(QStringList list)
{
    date = list.at(0).split("/").at(0);
    unit_value = list.at(0).split("/").at(1).toFloat();
    cumulative_value = list.at(0).split("/").at(2).toFloat();
    growth_rate= list.at(0).split("/").at(3).toFloat();
    //qDebug() << date << unit_value << cumulative_value <<growth_rate;
}

bool myfund::isnull()
{
    return !status;
}
