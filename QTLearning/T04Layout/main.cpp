

/* 应用程序抽象类 */
#include <QApplication>

/*窗口类*/
#include <QWidget>

/* 按钮 */
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    /* 构造一个窗口*/
    QWidget w;
    w.setWindowTitle("hello world");

    /*显示窗口*/
    w.show();

    /* 按钮也是个窗口 */
    QPushButton button;
    button.setText("Button");
    /* 窗口对象的父子关系，影响显示位置 */
    /* 没有父窗口的窗口，我们称之为主窗口 */
    //button.setParent(&w);
    //button.show();
    QLineEdit edit;
    //edit.setParent(&w);
    //edit.show();
    QObject::connect(&button, SIGNAL(clicked()), &w, SLOT(close()));
    //QVBoxLayout layout;
//    QHBoxLayout layout;
//    layout.addStretch(1);
//    layout.addWidget(&button);
//    layout.addSpacing(50);
//    layout.addWidget(&edit);
//    layout.addStretch(1);
    QGridLayout layout;
//    layout.addWidget(&button,0,0);
//    layout.addWidget(&edit,0,1);
//    layout.addWidget(new QPushButton("1,0"),1,0);
//    layout.addWidget(new QPushButton("1,1"),1,1);
//    //layout.setColumnStretch(2,1);
//    //layout.setRowStretch(2,1);
//    layout.addWidget(new QPushButton("HELLO"),2,0,2,2);
    QLineEdit *password=new QLineEdit();
    layout.setColumnStretch(3,1);
    layout.setRowStretch(4,1);
    layout.setColumnStretch(0,1);
    layout.setRowStretch(0,1);
    layout.addWidget(new QLabel("username:"),1,1);
    layout.addWidget(new QLineEdit(),1,2);
    layout.addWidget(new QLabel("password:"),2,1);
    layout.addWidget(password,2,2);
    password->setEchoMode(QLineEdit::Password);
    QHBoxLayout *hbox=new QHBoxLayout();
    layout.addLayout(hbox,3,2);
    hbox->addStretch(1);
    hbox->addWidget(new QPushButton("Login"));
    //layout.addWidget(new QPushButton("Login"),3,2);
    w.setLayout(&layout);
    /* QT对C++的拓展 */
    // std::bind std::function
    w.setWindowTitle("Hello World");

    /*在exec中有一个消息循环*/
    return app.exec();
}
