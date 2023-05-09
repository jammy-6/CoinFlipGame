
#include "coin.h"
#include <algorithm>
#include <QPixmap>
#include<QIcon>
#include <QTimer>
#include <QDebug>
Coin::Coin(int posx,int posy,bool gold):posx(posx),posy(posy),gold(gold)
{

    if(!gold) std::reverse(vec.begin(),vec.end());

    isAnimation = false;
    QString iconFilePath = QString(":/res/Coin000%1.png").arg(QString::number((vec[0])));
    drawIcon(iconFilePath);


    timer = new QTimer(this);
    //硬币反转动画
    connect(timer,&QTimer::timeout,[=](){
        drawIcon(QString(":/res/Coin000%1.png").arg(*it));
        it++;
        if(it==vec.end())
        {
            timer->stop();
            //翻转完成，其它参数设置
            this->gold = !this->gold;
            std::reverse(vec.begin(),vec.end());
            it=vec.begin();
            isAnimation = false;
        }
    });

}
//画icon的函数
void Coin::drawIcon(QString iconFilePath)
{
    QPixmap *pix = new QPixmap;
    bool ret = pix->load(iconFilePath);

    setIcon(QIcon(*pix));
    setFixedSize(pix->width(),pix->height());
    setIconSize(QSize(pix->width(),pix->height()));
    setStyleSheet("QPushButton{border:0px;}");
}

//硬币翻转函数
void Coin::flip()
{
    //翻转动画
    isAnimation = true;
    timer->start();
    timer->setInterval(50);
}

bool Coin::getIsAnimation() const
{
    return isAnimation;
}

void Coin::setIsAnimation(bool newIsAnimation)
{
    isAnimation = newIsAnimation;
}


void Coin::mousePressEvent(QMouseEvent *e)
{
    if(isAnimation){
        return;
    }
    QPushButton::mousePressEvent(e);
}
