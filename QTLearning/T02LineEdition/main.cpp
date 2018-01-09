/* 应用程序抽象类 */
#include <QApplication>

/*窗口类*/
#include <QWidget>

/* 按钮 */
#include <QPushButton>

#include <QLineEdit>
#include <QCompleter>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    /* 构造一个窗口*/
    QWidget w;
    w.setWindowTitle("hello world");
    QLineEdit edit;
    //edit.setEchoMode(QLineEdit::PasswordEchoOnEdit);
    //get the text
    //edit.text();
    //input prompt
    //edit.setPlaceholderText("Please input text:");
    QCompleter comp(QStringList()<<"abc"<<"123"<<"789");
    //comp.setFilterMode(Qt::MatchContains);
    //auto complete
    edit.setCompleter(&comp);
    edit.setParent(&w);
    w.setWindowTitle("Hello World");
    /*显示窗口*/
    w.show();
    /*在exec中有一个消息循环*/
    return app.exec();
}
