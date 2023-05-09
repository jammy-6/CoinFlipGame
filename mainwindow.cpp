
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QTimer>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QFont>
#include "mybutton.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    QStringList titleList = {"猫猫翻金币","请选择关卡","关卡%1"};
   // setWindowTitle(titleList[ui->stackedWidget->currentIndex()]);

    ui->setupUi(this);
    //菜单栏退出按键
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //开始按钮点击事件
    connect(ui->start_button,&QPushButton::clicked,[=](){
        MyButton::buttonAnimation(ui->start_button);
        QTimer::singleShot(300,this,[=](){
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
            setWindowTitle(titleList[ui->stackedWidget->currentIndex()]);
        });
    });



    //level界面返回按钮点击
    connect(ui->back_button,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
        setWindowTitle(titleList[ui->stackedWidget->currentIndex()]);
    });
    //play界面返回按钮点击
    connect(ui->back_button_2,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
        setWindowTitle(titleList[ui->stackedWidget->currentIndex()]);
        emit ui->playscene->deleteUI();
    });

    //play界面保存按钮点击
    connect(ui->save_button,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
        setWindowTitle(titleList[ui->stackedWidget->currentIndex()]);
        emit ui->playscene->saveProcess();
    });

    //level界面->play界面
    connect(ui->levelscene,&LevelScene::toPlayScene,[=](int num){
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
        setWindowTitle(titleList[ui->stackedWidget->currentIndex()].arg(num));
    });

    ui->levelscene->setPlayScene(ui->playscene);

}

MainWindow::~MainWindow()
{
    delete ui;
}



