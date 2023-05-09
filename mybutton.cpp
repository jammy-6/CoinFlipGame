
#include "mybutton.h"
#include <QPropertyAnimation>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QGroupBox>
MyButton::MyButton(QString oriImgPath, QString pressImgPath):oriImgPath(oriImgPath),pressImgPath(pressImgPath)
{
    QPixmap pix;
    pix.load(oriImgPath);
    setFixedSize(pix.width(),pix.height());
    setIcon(QIcon(pix));
    setIconSize(QSize(pix.width(),pix.height()));
    setStyleSheet("QPushButton{border:0px;}");
}

//默认创建的是返回按钮
MyButton::MyButton(QWidget* parent):QPushButton(parent){
    oriImgPath = ":/res/BackButton.png";
    pressImgPath = ":/res/BackButtonSelected.png";
}


void MyButton::mousePressEvent(QMouseEvent *e)
{
    if(pressImgPath!=""){
        QPixmap pix;
        pix.load(pressImgPath);
        QTimer::singleShot(30,this,[=](){
            QPushButton::setIcon(QIcon(pix));
        });
    }

    QPushButton::mousePressEvent(e);
}
void MyButton::mouseReleaseEvent(QMouseEvent *e)
{
    QPixmap pix;
    pix.load(oriImgPath);
    QTimer::singleShot(30,this,[=](){
        QPushButton::setIcon(QIcon(pix));
    });

    QPushButton::mouseReleaseEvent(e);

}

QString MyButton::getOriImgPath() const
{
    return oriImgPath;
}

void MyButton::setOriImgPath(const QString &newOriImgPath)
{
    oriImgPath = newOriImgPath;
}


//按钮向下弹动画
void  MyButton::buttonAnimation(QPushButton* button)
{
    QPropertyAnimation *animation = new QPropertyAnimation(button,"geometry");
    animation->setDuration(300);
    animation->setStartValue(button->geometry());
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->setStartValue(QRect(button->x(),button->y()+30,button->width(),button->height()));
    animation->start();
}
