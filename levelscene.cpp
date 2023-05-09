
#include "levelscene.h"
#include <QPixmap>
#include "mybutton.h"
#include <QStyleOption>
#include <QPainter>
#include <QLabel>
LevelScene::LevelScene(QWidget *parent)
    : QWidget{parent}
{

    for(int i=0;i<20;i++){
        //设置按钮
        MyButton *btn = new MyButton(":/res/LevelIcon.png");
        btn->setParent(this);
        btn->move(45+i%4*btn->width(),120+i/4*btn->height());

        //设置按钮文本标签
        QLabel *label = new QLabel(QString::number(i+1),this);
        label->setGeometry(btn->geometry());
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        //按钮点击事件
        connect(btn,&QPushButton::clicked,[=](){
            playScene->initGame(label->text().toInt());
            emit toPlayScene(label->text().toInt());
        });
    }



}


void LevelScene::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

PlayScene *LevelScene::getPlayScene() const
{
    return playScene;
}

void LevelScene::setPlayScene(PlayScene *newPlayScene)
{
    playScene = newPlayScene;
}

