
#ifndef LEVELSCENE_H
#define LEVELSCENE_H


#include <QWidget>
#include "playscene.h"

class LevelScene : public QWidget
{
    Q_OBJECT
public:
    explicit LevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    PlayScene * playScene = nullptr;
    PlayScene *getPlayScene() const;
    void setPlayScene(PlayScene *newPlayScene);

signals:
    void toPlayScene(int);
};

#endif // LEVELSCENE_H
