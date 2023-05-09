
#ifndef PLAYSCENE_H
#define PLAYSCENE_H


#include <QWidget>
#include <dataconfig.h>
#include <QLabel>
#include <vector>
#include "coin.h"
#include <map>

using std::vector;
using std::map;

class PlayScene : public QWidget
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    void disableCoins();
    void enableCoins();
    void initGame(int);//初始化游戏
signals:
    void deleteUI();
    void saveProcess();
private:
    //关卡数
    int num;

    vector<vector<Coin*>> coins;//保存的硬币矩阵
    int coinRowNum=0;//硬币的行数
    int coinColumnNum=0;//硬币的列数

    dataConfig config;//所有关卡初始信息
    QMap<int, QVector< QVector<int> > >  gameInfo;//保存的游戏进度信息

    QPixmap map_border = QPixmap(":/res/BoardNode.png");
    QLabel *successLabel;

    vector<vector<QLabel *>> boarders;
    void paintEvent(QPaintEvent *event);
    bool checkSuccess();//判断游戏是否胜利
    void drawUI();//用于绘制UI
    QLabel * drawBoarder();//绘制硬币边框
    void display();//用于显示当前游戏进度
    void successAnimation();

};

#endif // PLAYSCENE_H
