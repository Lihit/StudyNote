#include "mywidget.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QTextEdit>
#include <QTextBrowser>
#include <QSlider>
#include <QSpinBox>
#include <QTimeEdit>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QTableWidget>
#include <QGroupBox>
#include <QLCDNumber>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCompleter>
#include <QDebug>
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *vbox=new QVBoxLayout(this);
    vbox->addWidget(new QLabel("<font color=red>hello</font>"));
    vbox->addWidget(new QPushButton("button"));
    QPushButton * button1=new QPushButton("button1");
    button1->setStyleSheet("QPushButton {font:bold 16px;color:red}");
    vbox->addWidget(button1);
    QRadioButton* radio;
    vbox->addWidget(radio=new QRadioButton("radiobutton"));
    connect(radio, &QRadioButton::clicked, [](bool v){
        qDebug() << v;
    });
    vbox->addWidget(new QCheckBox("checkbox"));
    QComboBox *comb=new QComboBox();
    vbox->addWidget(comb);
    comb->addItem("item1");
    comb->addItem("item2");
    comb->setEditable(true);
    comb->setCompleter(new QCompleter(comb->model()));
    connect(comb, SIGNAL(currentTextChanged(QString)), this, SLOT(slotComboBoxIndexChanged(QString)));


    QTextEdit* edit=new QTextEdit();
    vbox->addWidget(edit);
    edit->setText("<table border=1><tr><th>head1</th><th>head2</th></tr>"
                  "<tr><th>value1</th><th>value2</th></tr>"
                  "<tr><th>value3</th><th>value4</th></tr>"
                  "</table>"
                  "<img src=../aaa.png></img>"
                );
    edit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _edit = edit;
    connect(edit, &QTextEdit::textChanged, [&](){
     //   QTextEdit* edit = (QTextEdit*)this->sender();
        qDebug() << _edit->toPlainText();
    });

    QGroupBox* group=new QGroupBox("some items");
    QHBoxLayout* hbox=new QHBoxLayout();
    hbox->addWidget(new QPushButton("hello"));
    hbox->addWidget(new QPushButton("world"));
    vbox->addWidget(group);
    group->setLayout(hbox);

    QSlider* slider=new QSlider(Qt::Horizontal);
    QSpinBox* spinBox;
    vbox->addWidget(slider);
    slider->setMaximum(100);
    slider->setMinimum(0);
    vbox->addWidget(spinBox = new QSpinBox);
    spinBox->setMaximum(100);
    spinBox->setMinimum(0);

    connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));


    QLabel* label=new QLabel("<a href=www.baidu.com>baidu</a>");
    vbox->addWidget(label);
    connect(label, &QLabel::linkActivated, [](QString str){
        qDebug() << str;
    });
    label->setPixmap(QPixmap("../aaa.png"));


    vbox->addWidget(new QDateTimeEdit);
    QLCDNumber* lcd;
    vbox->addWidget(lcd = new QLCDNumber(10));
    lcd->display(12345);
    lcd->setMode(QLCDNumber::Hex);
    lcd->setSegmentStyle(QLCDNumber::Outline);
}
void MyWidget::slotComboBoxIndexChanged(const QString &str)
{
    qDebug() << "slotComboBoxIndexChanged" << str;
}
int main(int argc,char* argv[]){
    QApplication app(argc,argv);
    MyWidget w;
    w.show();
    return app.exec();
}
