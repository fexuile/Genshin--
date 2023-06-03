#include "mainwindows.h"
#include "ui_mainwindows.h"


mainwindows::mainwindows(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindows)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
    this->setWindowTitle("Genshin: Star Rail");
    this->setWindowIcon(QIcon(":/image/images/Star_rail.png"));

}

mainwindows::~mainwindows()
{
    delete ui;
}

void mainwindows::on_pushButton_clicked()
{
    QSound *ClickSound=new QSound(":/media/medias/clickbutton.wav",this);
    ClickSound->play();
    delete ui;
}

