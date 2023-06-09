#include "mainwindows.h"
#include "ui_mainwindows.h"
#include <iostream>
#include <fstream>
#include "role.h"

int level = 1;

mainwindows::mainwindows(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindows)
{
    ui->setupUi(this);
    this->setFixedSize(MAX_WINDOWS_WEIGHT,MAX_WINDOWS_HEIGHT);
    this->setWindowTitle("Genshin: Star Rail");
    this->setWindowIcon(QIcon(":/image/images/icon.png"));
    /*BackGround and BGM*/
    ui->label->setGeometry(350,200,1000,200);
    Background = new QLabel(this);
    Background->setGeometry(0,0,MAX_WINDOWS_WEIGHT,MAX_WINDOWS_HEIGHT);
    Background->setPixmap(QPixmap(":/image/images/background.jpg"));
    Background->setScaledContents(true);
    Background->lower();
    MainSound=new QSound(":/media/medias/bgm.wav",this);
    MainSound->setLoops(QSound::Infinite);
    MainSound->play();

    /*Button Size and Geometry*/

    ui->BeginButton->setFixedSize(BUTTON_WEIGHT,BUTTON_HEIGHT);
    ui->BeginButton->move(700,400);
//    ui->BeginButton->setFlat(true);

    ui->LoadButton->setFixedSize(BUTTON_WEIGHT,BUTTON_HEIGHT);
    ui->LoadButton->move(700,500);
//    ui->LoadButton->setFlat(true);

    ui->RuleButton->setFixedSize(BUTTON_WEIGHT,BUTTON_HEIGHT);
    ui->RuleButton->move(700,600);
//    ui->RuleButton->setFlat(true);

    ui->EndButton->setFixedSize(BUTTON_WEIGHT,BUTTON_HEIGHT);
    ui->EndButton->move(700,700);
//    ui->EndButton->setFlat(true);

    /*Click Button and Slog*/
    QSound *ClickSound=new QSound(":/media/medias/clickbutton.wav",this);

    New_Game = new gamewindow(level);
    ui->stackedWidget->addWidget(New_Game);

    Rule_Page = new rulewindow();
    ui->stackedWidget->addWidget(Rule_Page);
    Load_Game = new gamewindow(level);
    ui->stackedWidget->addWidget(Load_Game);
    connect(ui->LoadButton,&QPushButton::clicked,[=](){
        ClickSound->play();
        level = load_save::load_game();
        Load_Game->update(level);
        ui->stackedWidget->setCurrentWidget(Load_Game);
    });

    connect(ui->BeginButton,&QPushButton::clicked,[=](){
        ClickSound->play();
        ui->stackedWidget->setCurrentWidget(New_Game);
    });
    connect(New_Game,&gamewindow::closeWindow,[=]()
            {
        ui->stackedWidget->setCurrentWidget(ui->main);
            });
    connect(New_Game,&gamewindow::closeAll,[=]()
            {
                QTimer::singleShot(200,this,&QWidget::close);
            });
    connect(Load_Game,&gamewindow::closeWindow,[=]()
            {
                ui->stackedWidget->setCurrentWidget(ui->main);
            });
    connect(Load_Game,&gamewindow::closeAll,[=]()
            {
                QTimer::singleShot(200,this,&QWidget::close);
            });
    connect(ui->RuleButton,&QPushButton::clicked,[=](){
        ClickSound->play();
        ui->stackedWidget->setCurrentWidget(Rule_Page);
    });
    connect(Rule_Page,&rulewindow::closeWindow,[=](){
        ui->stackedWidget->setCurrentWidget(ui->main);
    });
    connect(ui->EndButton,&QPushButton::clicked,[=](){
        ClickSound->play();
        QTimer::singleShot(200,this,&QWidget::close);
    });
}

mainwindows::~mainwindows()
{
    delete ui;
}
