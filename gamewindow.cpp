#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "role.h"
#include <QPainter>
#include <QLabel>
#include "config.h"
#include <QString>

Monster* Make_boss(int level);
void gamewindow::set_player(){
    for(int i=0;i<4;i++)
        player[i] = new Player(i,100,10,0.8);
}

gamewindow::gamewindow(int LEVEL, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewindow)
{
    this->level = LEVEL;
    this->set_player();
    player[0]->hp = 50;
    ui->setupUi(this);
//UI Designed:
    ui->backButton->move(1520,20);
    ui->backButton->setFixedSize(BACKBUTTON_WEIGHT,BACKBUTTON_HEIGHT);
    ui->backButton->setStyleSheet("QPushButton{border-image: url(:/image/images/back.png);}");
    Boss = Make_boss(level);

}

gamewindow::~gamewindow()
{
    delete ui;
}

Monster* Make_boss(int level){
    Monster* Boss = new Monster;
    if(level == 1){//yan kui qiuqiuwang
        Boss->shield_hp = 4;
        Boss->hp = Boss->all_hp = 20;
        Boss->atk = 3;
        Boss->def = 0.1;
        Boss->element_type = 1;
        Boss->shield_time = 0;
    }
    if(level == 2){

    }
    return Boss;
}

void gamewindow::paintEvent(QPaintEvent* event){
    QPainter Painter(this);
    int hp[5];
    for(int i=0;i<4;i++)
        hp[i] = CARD_W * player[i]->hp / player[i]->all_hp;
    Painter.drawPixmap(C1_W,C1_H,CARD_W,CARD_H,QPixmap(":/image/images/Mona.png"));
    Painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    Painter.drawRect(C1_W,C1_H-15,hp[0],15);
    Painter.drawPixmap(C2_W,C2_H,CARD_W,CARD_H,QPixmap(":/image/images/diluke.png"));
    Painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    Painter.drawRect(C2_W,C2_H-15,hp[1],15);
    Painter.drawPixmap(C3_W,C3_H,CARD_W,CARD_H,QPixmap(":/image/images/laopo.png"));
    Painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    Painter.drawRect(C3_W,C3_H-15,hp[2],15);
    Painter.drawPixmap(C4_W,C4_H,CARD_W,CARD_H,QPixmap(":/image/images/ying.png"));
    Painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    Painter.drawRect(C4_W,C4_H-15,hp[3],15);
    std::string Boss_name = ":/image/images/boss" +std::to_string(level) + ".png";
    QString boss_name = QString::fromStdString(Boss_name);
    Painter.drawPixmap(BOSS_W,BOSS_H,CARD_W,CARD_H,QPixmap(boss_name));
    Painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    hp[4] = CARD_W * Boss->hp / Boss->all_hp;
    Painter.drawRect(BOSS_W,BOSS_H-15,hp[4],15);

}
