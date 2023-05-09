
#ifndef COIN_H
#define COIN_H


#include <QWidget>
#include <QPushButton>
#include <vector>
class Coin : public QPushButton
{
    Q_OBJECT
public:
//    explicit Coin(QWidget *parent = nullptr);
    Coin(int,int,bool);
    void flip();
    bool getIsAnimation() const;
    void setIsAnimation(bool newIsAnimation);

signals:



private:
    int posx,posy;
    bool gold,isAnimation;
    std::vector<int> vec = {1,2,3,4,5,6,7,8};
    std::vector<int>::iterator it = vec.begin();    
    QTimer *timer;

    void mousePressEvent(QMouseEvent *e);
    void drawIcon(QString iconFilePath);
};

#endif // COIN_H
