#include "endwindow.h"
#include <QTimer>
#include "ui_endwindow.h"
#include "config.h"
#include <role.h>
#include "gamewindow.h"

EndWindow::EndWindow(my_genshin*game, int flag, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndWindow)
{
    this->setFixedSize(SMALL_WINDOWS_WEIGHT,SMALL_WINDOWS_HEIGHT);
    this->setWindowTitle("Genshin: Star Rail GameEnd!");
    this->setWindowIcon(QIcon(":/image/images/icon.png"));
    ui->setupUi(this);
    QLabel* Background = new QLabel(this);
    Background->setGeometry(0,0,this->width(),this->height());
    if(flag==1)Background->setPixmap(QPixmap(":/image/images/win.png"));
    else Background->setPixmap(QPixmap(":/image/images/lose.png"));
    Background->setScaledContents(true);
    Background->lower();
    if(flag==-1){
        ui->end->setFixedSize(SMALL_BUTTON_WEIGHT,SMALL_BUTTON_HEIGHT);
        ui->end->setText(QString::fromStdString("保存并退出"));
        ui->end->move(150,140);
    }
    else{
        ui->end->setFixedSize(SMALL_BUTTON_WEIGHT,SMALL_BUTTON_HEIGHT);
        ui->end->setText(QString::fromStdString("保存并退出"));
        ui->end->move(80,140);
    }
    ui->next->move(1000,0);
    if(flag==1){
        ui->next->setFixedSize(SMALL_BUTTON_WEIGHT,SMALL_BUTTON_HEIGHT);
        ui->next->setText(QString::fromStdString("下一关"));
        ui->next->move(220,140);
    }
    connect(ui->end,&QPushButton::clicked,[=](){
        QTimer::singleShot(200,this,&QWidget::close);
        if(flag==1)game->level += 1;
        load_save::save_game(game);
        emit quiting();
    });
    connect(ui->next,&QPushButton::clicked,[=](){
        QTimer::singleShot(200,this,&QWidget::close);
        emit nexting();
    });
}

EndWindow::~EndWindow()
{
    delete ui;
}
