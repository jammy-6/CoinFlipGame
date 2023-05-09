
#include "playscene.h"
#include <QPixmap>
#include "mybutton.h"
#include <QStyleOption>
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include "coin.h"
#include <QPixmap>
#include <QPushButton>
#include <QVector>
#include <QTimer>
#include <vector>
#include <QPropertyAnimation>
#include <iostream>
PlayScene::PlayScene(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(320,588);
    successLabel = new QLabel(this);
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    successLabel->setPixmap(pix);
    successLabel->setFixedSize(pix.width(),pix.height());
    successLabel->move((this->width()-successLabel->width())*0.5,-successLabel->height());


    //保存进度
    connect(this,&PlayScene::saveProcess,[=](){
        for(int i=0;i<coinRowNum;i++){
            for(int j=0;j<coinColumnNum;j++){
                delete coins[i][j];
                delete boarders[i][j];
                coins[i][j] = nullptr;
                boarders[i][j]=nullptr;
            }
        }
        //移动胜利标语至原位置
        successLabel->move((this->width()-successLabel->width())*0.5,-successLabel->height());
    });

    //删除游戏
    connect(this,&PlayScene::deleteUI,this,[=](){
        for(int i=0;i<coinRowNum;i++){
            for(int j=0;j<coinColumnNum;j++){
                delete coins[i][j];
                delete boarders[i][j];
                coins[i][j] = nullptr;
                boarders[i][j]=nullptr;
            }
        }
        //删除游戏信息
        if(gameInfo.find(num)!=gameInfo.end())
            gameInfo.erase(gameInfo.find(num));
        //移动胜利标语至原位置
        successLabel->move((this->width()-successLabel->width())*0.5,-successLabel->height());
    });



}

void PlayScene::initGame(int num){

    qDebug()<<"初始化第"<<num<<"关卡";

    this->num = num;
    if(!gameInfo.contains(num))
        gameInfo[num] = config[num];

    //硬币行数及列数
    coinRowNum    = gameInfo[num].size();
    coinColumnNum = gameInfo[num][0].size();

    display();
    //初始化硬币矩阵
    coins = vector<vector<Coin*>>{coinRowNum,{coinColumnNum,nullptr}};
    boarders = vector<vector<QLabel*>>{coinRowNum,{coinColumnNum,nullptr}};

    drawUI();

    if(checkSuccess()){
        disableCoins();
        qDebug()<<"游戏胜利";
        successAnimation();
    }


}
QLabel * PlayScene::drawBoarder()
{

    QLabel* label = new QLabel(this);
    label->setPixmap(map_border);
    label->setFixedSize(map_border.width(),map_border.height());

    return label;
}


void PlayScene::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool PlayScene::checkSuccess()
{
    for(int i=0;i<coinRowNum;i++)
    {
        for(int j=0;j<coinColumnNum;j++){
            if(gameInfo[num][i][j]==0)
                return false;
        }
    }
    return true;

}

void PlayScene::display(){
    qDebug()<<"当前游戏信息：";
    for(int i=0;i<coinRowNum;i++){
        qDebug()<<gameInfo[num][i][0]<<" "<<gameInfo[num][i][1]<<" " <<gameInfo[num][i][2]<<" "<<gameInfo[num][i][3];
    }
}


void PlayScene::successAnimation()
{

    QPropertyAnimation *animation = new QPropertyAnimation(successLabel,"geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect((this->width()-successLabel->width())*0.5,-successLabel->height(),successLabel->width(),successLabel->height()));
    animation->setEndValue(QRect((this->width()-successLabel->width())*0.5,-successLabel->height()+150,successLabel->width(),successLabel->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}


//胜利之后将所有金币设置为动画进行中，禁用所有金币
void PlayScene::disableCoins()
{
    for(int i=0;i<coinRowNum;i++)
        for(int j=0;j<coinColumnNum;j++)
            coins[i][j]->setIsAnimation(true);

}

void PlayScene::enableCoins()
{
    for(int i=0;i<coinRowNum;i++)
        for(int j=0;j<coinColumnNum;j++)
            coins[i][j]->setIsAnimation(false);

}

void PlayScene::drawUI()
{
    QLabel* board_label;
    int init_x  = (this->width()-map_border.width()*coinColumnNum)*0.5;
    int init_y = (this->height()-map_border.height()*coinRowNum)*0.5;

    for(int i =0;i<coinRowNum;i++)
    {
        for(int j=0;j<coinColumnNum;j++)
        {

            //画硬币边框
            boarders[i][j] = drawBoarder();
            board_label = boarders[i][j];
            board_label->move(init_x+j*board_label->width(),init_y+i*board_label->height());

            //画硬币
            coins[i][j] = new Coin(i,j,gameInfo[num][i][j]);
            coins[i][j]->setParent(this);
            coins[i][j]->move(init_x+j*board_label->width()+2,init_y+i*board_label->height()+2);

            connect(coins[i][j],&QPushButton::clicked,[=](){
                disableCoins();
                //翻转点击硬币
                coins[i][j]->flip();
                gameInfo[num][i][j] = gameInfo[num][i][j]?0:1;
                //周围金币延时反转
                QTimer::singleShot(300,this,[=](){
                    //翻转左边
                    if(j-1>=0){
                        coins[i][j-1]->flip();
                        gameInfo[num][i][j-1] = gameInfo[num][i][j-1]?0:1;
                    }
                    //翻转右边
                    if(j+1<coinColumnNum){
                        coins[i][j+1]->flip();
                        gameInfo[num][i][j+1] = gameInfo[num][i][j+1]?0:1;
                    }

                    //翻转上边
                    if(i-1>=0){
                        coins[i-1][j]->flip();
                        gameInfo[num][i-1][j] = gameInfo[num][i-1][j]?0:1;
                    }
                    //翻转下边
                    if(i+1<coinRowNum){
                        coins[i+1][j]->flip();
                        gameInfo[num][i+1][j] = gameInfo[num][i+1][j]?0:1;
                    }
                    display();
                    //检查胜利
                    if(checkSuccess())
                    {
                        QTimer::singleShot(500,this,[=](){
                            disableCoins();
                        });
                        qDebug()<<"游戏胜利";
                        successAnimation();
                    }else{
                        enableCoins();
                    }
                });
            });
        }
    }
}
