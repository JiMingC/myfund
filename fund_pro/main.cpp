#include "widget.h"
#include "mynetwork.h"
#include "myjsonwork.h"
#include "myfund.h"
#include <iostream>
using namespace std ;
//http://fund.eastmoney.com/f10/F10DataApi.aspx?type=lsjz&code=377240
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.show();
   // QByteArray data = mynetwork::geturldata(QString("http://fund.eastmoney.com/pingzhongdata/001511.js") );
   // myjsonwork::getstrbyvar("fS_name",QString(data));
    //cout<<data.toStdString()<<endl;
   // w.setText(QString(data));

    //myfund funda = myfund("001511");


    return a.exec();
}
