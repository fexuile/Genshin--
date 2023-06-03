#include "mainwindows.h"
#include "ui_mainwindows.h"


mainwindows::mainwindows(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindows)
{
    ui->setupUi(this);
    this->setFixedSize(MAX_WINDOWS_WEIGHT,MAX_WINDOWS_HEIGHT);
    this->setWindowTitle("Genshin: Star Rail");
    this->setWindowIcon(QIcon(":/image/images/icon.png"));

    /*BackGround*/
    Background = new QLabel(this);
    Background->setGeometry(0,0,MAX_WINDOWS_WEIGHT,MAX_WINDOWS_HEIGHT);
    Background->setPixmap(QPixmap(":/image/images/bg.jpg"));
    Background->setScaledContents(true);
    Background->lower();

    /*Button Size and Geometry*/

    ui->BeginButton->setFixedSize(BUTTON_WEIGHT,BUTTON_HEIGHT);
    ui->BeginButton->move(110,550);
    ui->BeginButton->setFlat(true);

    ui->LoadButton->setFixedSize(BUTTON_WEIGHT,BUTTON_HEIGHT);
    ui->LoadButton->move(110,650);
    ui->LoadButton->setFlat(true);

    ui->RuleButton->setFixedSize(BUTTON_WEIGHT,BUTTON_HEIGHT);
    ui->RuleButton->move(110,750);
    ui->RuleButton->setFlat(true);

    ui->EndButton->setFixedSize(BUTTON_WEIGHT,BUTTON_HEIGHT);
    ui->EndButton->move(110,850);
    ui->EndButton->setFlat(true);

    /*Click Button and Slog*/
    QSound *ClickSound=new QSound(":/media/medias/clickbutton.wav",this);


    connect(ui->BeginButton,&QPushButton::clicked,[=](){
        ClickSound->play();
    });

    connect(ui->LoadButton,&QPushButton::clicked,[=](){
        ClickSound->play();
    });

    connect(ui->RuleButton,&QPushButton::clicked,[=](){
        ClickSound->play();
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


