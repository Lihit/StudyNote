#include "mywidget.h"
#include <QApplication>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QPainter>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
//    QVBoxLayout* lay = new QVBoxLayout(this);
    QVBoxLayout*lay =new QVBoxLayout();
  //  this->setLayout(lay);
#if 0
    QPushButton* button2;
    lay->addWidget(button = new QPushButton("OK", this));
    lay->addWidget(button2 = new QPushButton("Button2"));

    button->setDefault(true);

    // é¼ æ ‡ä¸éœ€è¦æŒ‰ä¸‹ï¼ŒmouseMoveå°±èƒ½å¾—åˆ°è°ƒç”¨
    this->setMouseTracking(true);

    connect(button2, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
    connect(button, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
#endif
//    lay->addWidget(edit = new QLineEdit());
//    connect(edit, SIGNAL(returnPressed()), this, SLOT(slotButtonClicked()));
}

void MyWidget::slotButtonClicked()
{
    QLineEdit* button = (QLineEdit*)sender();
    qDebug() << button->text();
}
/* QApplicationå…ˆå¾—åˆ°->å…·ä½“åº”è¯¥å¤„ç†çš„çª—å£::event()->event()æ ¹æ®æ¶ˆæ¯ç±»åž‹æ¥è°ƒç”¨å…·ä½“çš„è™šå‡½æ•° */
/* 1ï¼‰å¯ä»¥é‡è½½å…·ä½“çš„è™šå‡½æ•°ï¼Œæ¥å®žçŽ°å¯¹æ¶ˆæ¯çš„å“åº”
   2ï¼‰å¯ä»¥é‡è½½eventå‡½æ•°ï¼Œç”¨æ¥å¤„ç†æˆ–è€…æˆªå–æ¶ˆæ¯ */

/* æˆªå–æ¶ˆæ¯ */
bool MyWidget::event(QEvent *ev)
{
    // é¼ æ ‡æ¶ˆæ¯è¢«æˆªæ–­
   // if(ev->type() == QEvent::MouseButtonPress)
     //   return true;
    ev->accept();

    return QWidget::event(ev);
}
void MyWidget::closeEvent(QCloseEvent *)
{
    qDebug() << "closeEvent";
}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawLine(QPoint(0, 0), QPoint(100, 100));

}

void MyWidget::mousePressEvent1(QMouseEvent *ev)
{
#if 0
    QPoint pt = ev->pos();
    qDebug() << pt;
    if(ev->button() == Qt::LeftButton)
    {

    }
    if(ev->modifiers() == Qt::ShiftModifier)
    {
        qDebug() << "shift press";
    }
#endif
    if(ev->button() == Qt::LeftButton)
    {
        if(ev->modifiers() == Qt::ControlModifier)
        {
            // handle with Control;
            return;
        }

        // handle2 without control;
    }
    else
    {

    }
}
void MyWidget::mouseReleaseEvent(QMouseEvent *)
{}
void MyWidget::mouseMoveEvent(QMouseEvent *)
{
    static int i=0;
    qDebug() << "mouse move"<< i++;
}

void MyWidget::keyPressEvent(QKeyEvent *ev)
{
    ev->modifiers();
    int key = ev->key();
    qDebug() << key;
    char a = key;
    qDebug() << (char)a;
}

void MyWidget::keyReleaseEvent(QKeyEvent *)
{}


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MyWidget w;
    w.show();

    return app.exec();
}
