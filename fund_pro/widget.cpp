#include "widget.h"
#include "ui_widget.h"
#include "QListWidget"
#include "qdebug.h"

#include <ui_widget.h>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    itemnum = 1;
    fundID = 0;
    vtmp = new QVBoxLayout;
    dblist.clear();
    ui->label_input->setText("Input fund code:");
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    ui->listWidget->setFixedSize(455,400);

    ui->listWidget->setMouseTracking(true);
    listwidget_inti();
    ui->pushButton_addfund->setText("add");
    ui->pushButton_delfund->setText("del");
    fundsqlit = new mysqlite("funds",this);
    fundsqlit->getDataList(dblist);
    qDebug() <<"db item num:" << dblist.size();
    for(int i =0; i < dblist.size(); i++){
        add_funds_to_listWidget(dblist.at(i).fS_code);
    }

    codemap.clear();

}


Widget::~Widget()
{
    delete ui;
}

void Widget::add_funds_to_listWidget(QString code)
{
    QPalette pa_up;
    QPalette pa_down;
    pa_up.setColor(QPalette::WindowText,Qt::red);
    pa_down.setColor(QPalette::WindowText,Qt::green);
    myfund *fundtmp = new myfund(code);
    if(fundtmp->isnull()){
            return;
    }
    QWidget *wtmp = new QWidget(ui->listWidget);
    wtmp->setFixedSize(448,25);
    QHBoxLayout *tmp = new QHBoxLayout;
    tmp->setMargin(0);
    tmp->setSpacing(0);

    QLabel *a = new QLabel(fundtmp->fS_code);
    QLabel *b = new QLabel(fundtmp->fS_name);

    QLabel *c = new QLabel();
    QLabel *d = new QLabel();
    QLabel *e = new QLabel();

//    QPushButton *btn = new QPushButton();
//    btn->setText("rm");
//    btn->setFixedSize(25,20);

    //set label view
    a->setFixedSize(50,25);
    b->setFixedSize(190,25);
    c->setFixedSize(70,25);
    d->setFixedSize(68,25);
    e->setFixedSize(68,25);

    a->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    b->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    c->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    d->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    e->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    a->setMargin(0);
    b->setMargin(0);
    c->setMargin(0);
    d->setMargin(0);
    e->setMargin(0);

    c->setNum(fundtmp->unit_value);
    d->setNum(fundtmp->cumulative_value);
    if(fundtmp->growth_rate > 0)
        e->setStyleSheet("font: bold; font-family: Microsoft YaHei UI;font-size:13px;color:red");
    if(fundtmp->growth_rate < 0)
        e->setStyleSheet("font: bold; font-family: Microsoft YaHei UI;font-size:13px;color:green");
    e->setNum(fundtmp->growth_rate);

    tmp->addWidget(a);
    tmp->addWidget(b);
    //tmp->addStretch();
    tmp->addWidget(c);
    tmp->addWidget(d);
    tmp->addWidget(e);

//    tmp->addWidget(btn);
    wtmp->setLayout(tmp);

    QListWidgetItem *item=new QListWidgetItem(ui->listWidget,itemnum);

    item->setSizeHint(QSize(448,25));

    itemnum++;
    ui->listWidget->setItemWidget(item,wtmp);

}

void Widget::listwidget_inti()
{
    QWidget *item0widget = new QWidget(ui->listWidget);
    item0widget->setFixedSize(450,20);

    QHBoxLayout *item0_layout = new QHBoxLayout;
    item0_layout->setSpacing(0);
    item0_layout->setMargin(0);
    QPushButton *a = new QPushButton("代码");
    QPushButton *b = new QPushButton("基金");
    QPushButton *c = new QPushButton("单位净值");
    QPushButton *d = new QPushButton("累计净值");
    QPushButton *e = new QPushButton("增长率%");

    a->setFixedSize(50,20);
    b->setFixedSize(190,20);
    c->setFixedSize(70,20);
    d->setFixedSize(70,20);
    e->setFixedSize(71,20);



    item0_layout->addWidget(a);
    item0_layout->addWidget(b);
    //item0_layout->addStretch();
    item0_layout->addWidget(c);
    item0_layout->addWidget(d);
    item0_layout->addWidget(e);
    QListWidgetItem *item=new QListWidgetItem(ui->listWidget,0);
    item->setSizeHint(QSize(450,20));
    item0widget->setLayout(item0_layout);
    ui->listWidget->setItemWidget(item,item0widget);
}


void Widget::on_pushButton_addfund_clicked()
{
    QString code = ui->lineEdit_code->text();
    if(code == NULL || fundsqlit->fund_code_isexist(code,dblist)){
        qDebug() << "code is null or isexist";
        return;
    }
//    QMap<int, QString>::iterator iter;
//    for(iter=codemap.begin();iter!=codemap.end();iter++){
//        if(iter.value() == code)
//            return;
//    }

    codemap.insert(itemnum,code);
    dbtmp.ID = itemnum;
    dbtmp.itemnum = itemnum;
    dbtmp.fS_code = code;
    fundsqlit->insertData(dbtmp);
    add_funds_to_listWidget(code);
}

void Widget::on_pushButton_rmfund_clicked()
{
    //int row = ui->listWidget->;
    //qDebug() << "clicked rmfund" << row;

}

void Widget::on_listWidget_itemEntered(QListWidgetItem *item)
{
    qDebug() << "clicked rmfund";
}

void Widget::on_pushButton_delfund_clicked()
{
    if(ui->listWidget->currentItem() == NULL)
        return;
    int count = ui->listWidget->count();
    int curRow = ui->listWidget->currentRow();
    qDebug() << ui->listWidget->currentItem()->type();
    //ui->listWidget->removeItemWidget(ui->listWidget->currentItem());
    ui->listWidget->takeItem(curRow);
    fundsqlit->deleteData(curRow);
    for(int i = curRow; i < count; i++){
        fundsqlit->updateID(i+1, i);
    }
    itemnum--;

}
