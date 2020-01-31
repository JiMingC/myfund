#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "myfund.h"
#include <QVBoxLayout>
#include <QString>
#include <QMap>
#include <QPushButton>
#include <QListWidgetItem>
#include <QPalette>
#include "mysqlite.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    QVBoxLayout *vtmp;
    int itemnum;
    QMap<int,QString> codemap;
    mysqlite *fundsqlit;
    SqliteData dbtmp;
    QList<SqliteData> dblist;

    ~Widget();

    void add_funds_to_listWidget(QString code);
    void listwidget_inti();
private slots:
    void on_pushButton_addfund_clicked();
    void on_pushButton_rmfund_clicked();

    void on_listWidget_itemEntered(QListWidgetItem *item);

    void on_pushButton_delfund_clicked();

private:
    Ui::Widget *ui;
    int fundID;
};
#endif // WIDGET_H
