#ifndef ROLE_H
#define ROLE_H
#include <set>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

class my_genshin;

const double react[4][4]={{1,2,1.2,1.2},
                          {1.2,1,2,2},
                          {1.2,0.8,1,1.1},
                          {1.2,2,1.2,1}
};//反应倍率
const double shield_react[4][4]={{0,1,1,0.5},
                                 {0.5,0,1,1.5},
                                 {0.5,0.8,0,0.2},
                                 {0.2,1,0.5,0}
};//破盾倍率
class person{
public:
    int element_type;
    double hp,all_hp;
    //速度，行动条
    double speed, mv_len;
    //效果及其剩余回合数
    //增加攻击，加速，减速，减伤，易伤
    pair<int, int> add_atk;
    pair<double, int> add_speed, dec_speed, dec_dmg, vulnerable;;
    int atk;
    double def;
    virtual void under_attack(person* enemy)=0;
    virtual void action(); //获取决策（从客户端/bot）
    virtual void end_round(); //回合结束
};

class Player:public person{
public:
    Player(){}
    Player(int ELEMENT,int ALL_HP,int ATK,int DEF, int SPEED = 100){}
    virtual void under_attack(person* enemy){}
    virtual void attack();
    virtual void skill();
    virtual void action();
};

//技能，回血
class Qiqi:public Player {
public:
    //技能：回复单体生命值
    virtual void attack(vector<person*> enemys);
    virtual void skill(vector<person*> players);
    virtual void action(my_genshin* game);
};

class Monster:public person{
public:
    double shield,shield_hp;
    int shield_time;
    int has_element = -1;

    virtual void under_attack(person* enemy);
    void SHIELD_BUILD();
    virtual void attack();
    virtual void skill();
    virtual void action();
};

class Boss1:public Monster{
public:
    int atk_cnt;
    Boss1(){}
    Boss1(int ELEMENT,int ALL_HP,int ATK,int DEF,int SHIELD);

    virtual void under_attack(person* enemy);
    void SHIELD_BUILD();
    void attack(vector<person*> enemys);
    void skill(vector<person*> enemys);
    virtual void action(my_genshin* game);
};

//游戏主进程
class my_genshin
{
public:
    int level;
    person* Boss;
    vector<person*> players;

    my_genshin(const int &LEVEL);
    vector<pair<double, person*> > get_mv_list(); //获取行动条
    vector<pair<double, person*> > get_virtual_mv_list(); //获取假设行动条
    void run_game(); //游戏主进程
private:
    void set_player();
};

#endif // ROLE_H
