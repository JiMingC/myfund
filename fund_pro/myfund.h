#ifndef MYFUND_H
#define MYFUND_H

#include "QString"
class myfund
{
public:
    myfund();
    myfund(QString code);

    void getinfofromStringList(QStringList list);
    //void *operator new(QString code);
    bool isnull();
    bool status = 0;
    QString fS_name;
    QString fS_code ;
    QString date;
    float unit_value;
    float cumulative_value;
    float growth_rate;

};

#endif // MYFUND_H
