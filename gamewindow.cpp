#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "role.h"
#include <QPainter>
#include <QElapsedTimer>
#include <QLabel>
#include "config.h"
#include <QString>
#include <QSound>
#include <QDebug>
#include <QCloseEvent>

gamewindow::gamewindow(int LEVEL, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewindow)
{
    game = new my_genshin(LEVEL);
    ui->setupUi(this);
//UI Designed:
    ui->backButton->move(1520,20);
    ui->backButton->setFixedSize(BACKBUTTON_WEIGHT,BACKBUTTON_HEIGHT);
    ui->backButton->setStyleSheet("QPushButton{border-image: url(:/image/images/back.png);}");
    ui->A->move(1460,700);
    ui->A->setFixedSize(ATTACK_BUTTON_WEIGHT,ATTACK_BUTTON_HEIGHT);
    ui->A->setStyleSheet("QPushButton{border-image: url(:/image/images/A.png);}");

    ui->R->move(1460,800);
    ui->R->setFixedSize(ATTACK_BUTTON_WEIGHT,ATTACK_BUTTON_HEIGHT);
    ui->R->setStyleSheet("QPushButton{border-image: url(:/image/images/R.png);}");
    QSound *ClickSound=new QSound(":/media/medias/clickbutton.wav",this);
    connect(ui->backButton,&QPushButton::released,[=]()
            {
                ClickSound->play();
                emit closeWindow();
            });
    connect(ui->A,&QPushButton::clicked,this,&gamewindow::A_attack);
    connect(ui->R,&QPushButton::clicked,this,&gamewindow::R_attack);
}

void gamewindow::update(int level){
    game->level = level;
    game->set_player();
    game->Boss = game->Make_boss(level);
    repaint();
}


void GameEnd(int flag){
    QWidget*endwindow = new QWidget;
    endwindow->show();
}

void gamewindow::A_attack(){
    QSound *ClickSound=new QSound(":/media/medias/clickbutton.wav",this);
    ClickSound->play();
    game->Skill_point = min(5, game->Skill_point + 1);
    auto p = (*game->get_mv_list().begin());
    p.second -> action(0, game);
    for (auto player : game->players)
        player->mv_len -= player->speed * p.first;
    game->Boss -> mv_len -= game->Boss->speed * p.first;
    p.second -> mv_len = 1e4;
    if(game->judge_win() == 1)GameEnd(1);
    p = (*game->get_mv_list().begin());
    if(p.second->name[0]=='s'){
        repaint();
        Boss_attack();
        if(game->judge_win() == -1)GameEnd(-1);
    }
    repaint();
}

void gamewindow::R_attack(){
    if(game->Skill_point == 0)return;
    game->Skill_point -= 1;
    QSound *ClickSound=new QSound(":/media/medias/clickbutton.wav",this);
    ClickSound->play();
    auto p = (*game->get_mv_list().begin());
    p.second -> action(1, game);
    for (auto player : game->players)
        player->mv_len -= player->speed * p.first;
    game->Boss -> mv_len -= game->Boss->speed * p.first;
    p.second -> mv_len = 1e4;
    if(game->judge_win() == 1)GameEnd(1);
    p = (*game->get_mv_list().begin());
    if(p.second->name[0]=='s'){
        repaint();
        Boss_attack();
        if(game->judge_win() == -1)GameEnd(-1);
    }
    repaint();
}

void gamewindow::Boss_attack(){
    game->Boss->action(0,game);
    auto p = (*game->get_mv_list().begin());
    p.second -> action(1, game);
    for (auto player : game->players)
        player->mv_len -= player->speed * p.first;
    game->Boss -> mv_len -= game->Boss->speed * p.first;
    p.second -> mv_len = 1e4;
}


gamewindow::~gamewindow()
{
    delete ui;
}

void gamewindow::paintEvent(QPaintEvent* event){
    QPainter Painter(this);
    std::string string_hp[6];
    int hp[5], shield_cv =CARD_W * game->Boss->shield / game->Boss->shield_hp;
    for(int i=0;i<4;i++){
        hp[i] = CARD_W * game->players[i]->hp / game->players[i]->all_hp;
        string_hp[i] = std::to_string((int)game->players[i]->hp) + "/" + std::to_string((int)game->players[i]->all_hp);
    }
    hp[4] = CARD_W * game->Boss->hp / game->Boss->all_hp;
    string_hp[4] = std::to_string((int)game->Boss->hp) + "/" + std::to_string((int)game->Boss->all_hp);
    string_hp[5] = std::to_string((int)game->Boss->shield) + "/" + std::to_string((int)game->Boss->shield_hp);

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
    std::string Boss_name = ":/image/images/boss" +std::to_string(game->level) + ".png";
    QString boss_name = QString::fromStdString(Boss_name);
    Painter.drawPixmap(BOSS_W,BOSS_H,CARD_W,CARD_H,QPixmap(boss_name));
    Painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    Painter.drawRect(rect5_hp);
    Painter.drawText(rect5, Qt::AlignHCenter, QString::fromStdString(string_hp[4]));
    Painter.setBrush(QBrush(Qt::gray));
    Painter.drawRect(rect6_hp);
    Painter.drawText(rect6, Qt::AlignHCenter, QString::fromStdString(string_hp[5]));
    if(~game->Boss->has_element){
        std::string element_name = ":/image/images/element" + std::to_string(game->Boss->has_element);
        Painter.drawPixmap(BOSS_W,BOSS_H - 60, 30,30,QString::fromStdString(element_name));
    }

    std::vector<pair<double, person*> > mv_list = game->get_mv_list();
    int X = MV_W, Y = MV_H;
    for(auto now: mv_list){
        auto p = now.second;
        string name = ":/image/images/" + p->name;
        Painter.drawPixmap(X, Y,60,60,QString::fromStdString(name));
        Y += 80;
    }
    Painter.setPen(Qt::red);
    QFont ft = QFont(("黑体"),20);
    ft.setBold(true);
    Painter.setFont(ft);
    string s = std::to_string(game->Skill_point) + '/' + std::to_string(5);
    Painter.drawText(1460,900,QString::fromStdString(s));
}
