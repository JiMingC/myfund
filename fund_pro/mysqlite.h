#ifndef MYSQLITE_H
#define MYSQLITE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QString>
struct SqliteData
{
    int ID;
    int itemnum;
    QString fS_name;
    QString fS_code ;
    QString date;
    float unit_value;
    float cumulative_value;
    float growth_rate;
};

class mysqlite : public QObject
{
    Q_OBJECT

public:
    mysqlite(QString name,QObject *parent=0);
    mysqlite();
    ~mysqlite();

public:
    bool insertData(SqliteData data);
    bool deleteData(int itemnum);
    bool getDataByCode(QString fS_code,SqliteData & data);
    bool getDataList(QList<SqliteData> & list);
    bool updateID(int ID,int curitemnum);
    bool fund_code_isexist(QString code, QList<SqliteData> & list);
private:
    QSqlDatabase m_DataBase;
private:
    bool initTable();
    bool isExistTable(QString table);
    bool createTable(QString table);
};


#endif // MYSQLITE_H
