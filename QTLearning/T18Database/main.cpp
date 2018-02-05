
#include <QApplication>
#include "Widget03.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "Contact.h"
#include "Widget04.h"

int main(int argc, char*argv[])
{
    QApplication app(argc, argv);

    /* QSQLITE QODBC QPLSQL */
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setPort(3306);
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("137688");
    db.setDatabaseName("test");
    bool bRet = db.open();
    if(bRet == false)
    {
        qDebug() << "error open database" << db.lastError().text();
        exit(0);
    }
    qDebug() << "open database success";

//    db.exec("insert into tuser(username,password,gender) values('wenshao','137688',1)");
//    QSqlQuery query = db.exec("select * from tuser");
//    //int size = query.size();
//    bool b = query.first();
//    while(b){
//        //QSqlResult* result = query.result();
//        //QVector<QVariant>values = result->boundValues();
//        qDebug()<<values;
//        b=query.next();
//    }
    Widget04 w4;
    w4.show();
    return app.exec();
}
