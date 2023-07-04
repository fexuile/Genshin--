#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "role.h"
#include <QPainter>
#include <QLabel>
#include "config.h"
#include <QString>
#include <QSound>

Monster* Make_boss(int level);
void gamewindow::set_player(){
    player[0] = new Player(0, 15, 2, 0.8);
    player[1] = new Player(1, 12,3,0.6);
    player[2] = new Player(2, 7, 7, 0.9);
    player[3] = new Player(3, 10, 1, 0.3);
}

gamewindow::gamewindow(int LEVEL, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewindow)
{
    this->level = LEVEL;
    this->set_player();
    Boss = Make_boss(level);
    ui->setupUi(this);
//UI Designed:
    ui->backButton->move(1520,20);
    ui->backButton->setFixedSize(BACKBUTTON_WEIGHT,BACKBUTTON_HEIGHT);
    ui->backButton->setStyleSheet("QPushButton{border-image: url(:/image/images/back.png);}");
    QSound *ClickSound=new QSound(":/media/medias/clickbutton.wav",this);

    connect(ui->backButton,&QPushButton::released,[=]()
            {
                ClickSound->play();
                emit closeWindow();
            });


}

gamewindow::~gamewindow()
{
    delete ui;
}

Monster* Make_boss(int level){
    Monster* Boss = new Monster;
    if(level == 1){//yan kui qiuqiuwang
        Boss->shield_hp = Boss->shield = 4;
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
    std::string string_hp[6];
    int hp[5], shield_cv =CARD_W * Boss->shield / Boss->shield_hp;
    for(int i=0;i<4;i++){
        hp[i] = CARD_W * player[i]->hp / player[i]->all_hp;
        string_hp[i] = std::to_string((int)player[i]->hp) + "/" + std::to_string((int)player[i]->all_hp);
    }
    hp[4] = CARD_W * Boss->hp / Boss->all_hp;
    string_hp[4] = std::to_string((int)Boss->hp) + "/" + std::to_string((int)Boss->all_hp);
    string_hp[5] = std::to_string((int)Boss->shield) + "/" + std::to_string((int)Boss->shield_hp);

    QRectF rect1(C1_W,C1_H-15,CARD_W,15);
    QRectF rect2(C2_W,C1_H-15,CARD_W,15);
    QRectF rect3(C3_W,C1_H-15,CARD_W,15);
    QRectF rect4(C4_W,C1_H-15,CARD_W,15);
    QRectF rect5(BOSS_W,BOSS_H-15,CARD_W,15);
    QRectF rect6(BOSS_W,BOSS_H-30,CARD_W,15);
    QRectF rect1_hp(C1_W,C1_H-15,hp[0],15);
    QRectF rect2_hp(C2_W,C1_H-15,hp[1],15);
    QRectF rect3_hp(C3_W,C1_H-15,hp[2],15);
    QRectF rect4_hp(C4_W,C1_H-15,hp[3],15);
    QRectF rect5_hp(BOSS_W,BOSS_H-15,hp[4],15);
    QRectF rect6_hp(BOSS_W,BOSS_H-30,shield_cv,15);
    Boss->has_element = 0;

    Painter.drawPixmap(C1_W,C1_H,CARD_W,CARD_H,QPixmap(":/image/images/Mona.png"));
    Painter.drawPixmap(C1_W-30,C1_H,30,30,QPixmap(":/image/images/element0.png"));
    Painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    Painter.drawRect(rect1_hp);
    Painter.drawText(rect1, Qt::AlignHCenter, QString::fromStdString(string_hp[0]));
    Painter.drawPixmap(C2_W,C2_H,CARD_W,CARD_H,QPixmap(":/image/images/diluke.png"));
    Painter.drawPixmap(C2_W-30,C2_H,30,30,QPixmap(":/image/images/element1.png"));
    Painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    Painter.drawRect(rect2_hp);
    Painter.drawText(rect2, Qt::AlignHCenter, QString::fromStdString(string_hp[1]));
    Painter.drawPixmap(C3_W,C3_H,CARD_W,CARD_H,QPixmap(":/image/images/laopo.png"));
    Painter.drawPixmap(C3_W-30,C3_H,30,30,QPixmap(":/image/images/element2.png"));
    Painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    Painter.drawRect(rect3_hp);
    Painter.drawText(rect3, Qt::AlignHCenter, QString::fromStdString(string_hp[2]));
    Painter.drawPixmap(C4_W,C4_H,CARD_W,CARD_H,QPixmap(":/image/images/ying.png"));
    Painter.drawPixmap(C4_W-30,C4_H,30,30,QPixmap(":/image/images/element3.png"));
    Painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    Painter.drawRect(rect4_hp);
    Painter.drawText(rect4, Qt::AlignHCenter, QString::fromStdString(string_hp[3]));
    std::string Boss_name = ":/image/images/boss" +std::to_string(level) + ".png";
    QString boss_name = QString::fromStdString(Boss_name);
    Painter.drawPixmap(BOSS_W,BOSS_H,CARD_W,CARD_H,QPixmap(boss_name));
    Painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    Painter.drawRect(rect5_hp);
    Painter.drawText(rect5, Qt::AlignHCenter, QString::fromStdString(string_hp[4]));
    Painter.setBrush(QBrush(Qt::gray));
    Painter.drawRect(rect6_hp);
    Painter.drawText(rect6, Qt::AlignHCenter, QString::fromStdString(string_hp[5]));
    if(~Boss->has_element){
        std::string element_name = ":/image/images/element" + std::to_string(Boss->has_element);
        Painter.drawPixmap(BOSS_W,BOSS_H - 60, 30,30,QString::fromStdString(element_name));
    }
}
