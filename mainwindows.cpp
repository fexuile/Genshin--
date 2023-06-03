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

    /*Button StyleSheet*/

    ui->BeginButton->setFixedSize(BUTTON_WEIGHT,BUTTON_HEIGHT);
    ui->EndButton->setFixedSize(BUTTON_WEIGHT,BUTTON_HEIGHT);

    /*Click Button and Slog*/
    QSound *ClickSound=new QSound(":/media/medias/clickbutton.wav",this);

    connect(ui->BeginButton,&QPushButton::clicked,[=](){
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


