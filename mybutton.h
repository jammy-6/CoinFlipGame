
#ifndef MYBUTTON_H
#define MYBUTTON_H


#include <QWidget>
#include <QPushButton>
#include <QString>
class MyButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyButton(QWidget *parent = nullptr);
    MyButton(QWidget *);
    MyButton(QString oriImgPath,QString pressImgPath="");
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    QString getOriImgPath() const;
    void setOriImgPath(const QString &newOriImgPath);
    void static buttonAnimation(QPushButton* button);
signals:


private:
    QString oriImgPath;
    QString pressImgPath;
};

#endif // MYBUTTON_H
