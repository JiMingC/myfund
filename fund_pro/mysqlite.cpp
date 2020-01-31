#include "mysqlite.h"
#include <QCoreApplication>
#include <QDebug>
#include <QSqlRecord>
mysqlite::mysqlite(QString name, QObject *parent)
    : QObject(parent)
{

    if (QSqlDatabase::contains(name)) {

        m_DataBase = QSqlDatabase::database(name);
    }
    else {

        m_DataBase = QSqlDatabase::addDatabase("QSQLITE");
        m_DataBase.setDatabaseName(name+".db");
        m_DataBase.setDatabaseName(QCoreApplication::applicationDirPath()+"//"+ name);
    }
    if (!m_DataBase.open())
    {
        qDebug() << "Error: Failed to connect database." << m_DataBase.lastError();
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }

    initTable();
}

mysqlite::~mysqlite()
{
}

bool mysqlite::initTable()
{
    if (!m_DataBase.open()) {
        return false;
    }

    if (!isExistTable("funds")) {
        createTable("funds");
    }
    return false;
}

bool mysqlite::isExistTable(QString table)
{
    bool bRet = false;
    if (!m_DataBase.open()) {
        return bRet;
    }
    QSqlQuery query(m_DataBase);
    query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(table));    //关键的判断
    if (query.next())
    {
        if (query.value(0).toInt() > 0)
        {
            bRet = true;
        }
    }
    return false;
}

bool mysqlite::createTable(QString table)
{
    if (!m_DataBase.open()) {
        return false;
    }

    QSqlQuery query(m_DataBase);
    if (table == QString("funds")) {

        bool success = query.exec("CREATE TABLE funds ("
                                    "ID INT PRIMARY KEY NOT NULL,"
                                    "fS_code TEXT NOT NULL,"
                                    "itemnum INT NOT NULL)");

        if (success) {
            qDebug() << "Succeed to creat table." ;
            return true;   //新建数据库成功
        }
        else {
            QSqlError lastError = query.lastError();
            QString err = lastError.driverText();
            qDebug() << err ;
            return false;
        }
    }
    else {
        return false;
    }
}

bool mysqlite::insertData(SqliteData data)
{
    if (!m_DataBase.open()) {
        return false;
    }
    QSqlQuery query(m_DataBase);

    bool success = query.exec(QString("INSERT INTO funds (ID, fS_code, itemnum) "
        "VALUES (%1, \"%2\", %3)").arg(data.itemnum)
                              .arg(data.fS_code)
                          .arg(data.itemnum));
//    bool success = query.exec(QString("INSERT INTO funds VALUES (1, \"001512\", 1)"));

    if (!success) {

        QSqlError lastError = query.lastError();
        QString err = lastError.driverText();
        qDebug() << "fail to insert data." << err ;
        return false;
    }
    qDebug() << "Succeed to insert data." ;
    return true;
}

bool mysqlite::deleteData(int itemnum)
{
    if (!m_DataBase.open()) {
        return false;
    }
    QSqlQuery query(m_DataBase);
    query.prepare(QString("DELETE FROM funds WHERE ID='%1'").arg(itemnum));
    query.exec();
    return false;
}

bool mysqlite::getDataByCode(QString fS_code, SqliteData & data)
{
    if (!m_DataBase.open()) {
        return false;
    }

    QSqlQuery query(m_DataBase);
    query.prepare(QString("SELECT * FROM funds WHERE fS_code='%1'").arg(fS_code));
    query.exec();
    QSqlRecord rec = query.record();
    if (query.next())
    {

        data.itemnum = query.value(2).toInt();
        //data.score = query.value(1).toInt();
        //data.grade = query.value(2).toString();

        return true;
    }
    return false;
}

bool mysqlite::getDataList(QList<SqliteData>& list)
{
    if (!m_DataBase.open()) {
        return false;
    }

    QSqlQuery query(m_DataBase);
    query.prepare(QString("SELECT * FROM funds"));
    query.exec();
    QSqlRecord rec = query.record();
    while (query.next())
    {
        SqliteData data;
        data.ID = query.value(0).toInt();
        data.fS_code = query.value(1).toString();
        data.itemnum = query.value(2).toInt();
        //qDebug() << data.ID <<  data.fS_code << data.itemnum;
        list.append(data);
        //return true;
    }
    return true;
}

bool mysqlite::updateID(int ID,int curitemnum)
{
    if (!m_DataBase.open()) {
        return false;
    }

    QSqlQuery query(m_DataBase);
    query.prepare(QString("UPDATE funds SET ID = %1 , itemnum = %2 WHERE ID = %3").arg(curitemnum).arg(curitemnum).arg(ID));
    query.exec();
    return false;
}

bool mysqlite::fund_code_isexist(QString code, QList<SqliteData> & list)
{
    for(int i =0; i < list.size(); i++){
        if(code == list.at(i).fS_code)
            return true;
    }
    return false;
}
