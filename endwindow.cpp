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
    ui->setupUi(this);
    ui->end->setFixedSize(SMALL_BUTTON_WEIGHT,SMALL_BUTTON_HEIGHT);
    ui->end->setText(QString::fromStdString("保存并退出"));
    ui->end->move(80,200);
    ui->next->move(1000,0);
    if(flag==1){
        ui->next->setFixedSize(SMALL_BUTTON_WEIGHT,SMALL_BUTTON_HEIGHT);
        ui->next->setText(QString::fromStdString("下一关"));
        ui->next->move(220,200);
    }
    connect(ui->end,&QPushButton::clicked,[=](){
        QTimer::singleShot(200,this,&QWidget::close);
        game->level += 1;
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
