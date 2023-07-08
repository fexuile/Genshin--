#ifndef ROLE_H
#define ROLE_H
#include <set>
#include <algorithm>
#include <vector>
#include <map>
#include <QFile>
#include <QString>
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
    pair<double, int> add_speed, dec_speed, dec_dmg, vulnerable;
    int atk;
    double def;
    string name;
    virtual void under_attack(person* enemy)=0;
    virtual void action(int type, my_genshin* game)=0; //获取决策（从客户端/bot）
    virtual void end_round(); //回合结束
};

class Player:public person{
public:
    Player(){}
    Player(int ELEMENT,int ALL_HP,int ATK,int DEF, int SPEED = 100);
    virtual void under_attack(person* enemy);
    virtual void attack(vector<person*> enemys);
    virtual void skill(vector<person*> enemys){}
    virtual void action(int type, my_genshin* game)=0;
};

//技能：回血
class Qiqi:public Player {
public:
    //技能：回复单体生命值
    Qiqi(int ELEMENT,int ALL_HP,int ATK,double DEF, int SPEED = 100){
        name = "player" + std::to_string(ELEMENT);
        element_type = ELEMENT;
        hp = all_hp = ALL_HP;
        atk = ATK;
        def = DEF;
        speed = SPEED;
        mv_len = 1e4 / speed;
    }
    void skill(vector<person*> players);
    virtual void action(int type, my_genshin* game);
};

//技能：指定我方单体使其行动提前100%并增加攻击力2回合
class Keqin:public Player {
public:
    Keqin(int ELEMENT,int ALL_HP,int ATK,double DEF, int SPEED = 100){
        name = "player" + std::to_string(ELEMENT);
        element_type = ELEMENT;
        hp = all_hp = ALL_HP;
        atk = ATK;
        def = DEF;
        speed = SPEED;
        mv_len = 1e4 / speed;
    }
    virtual void skill(vector<person*> players);
    virtual void action(int type, my_genshin* game);
};

//技能：对敌方全体造成伤害并减速30%
class Laoyang:public Player {
public:
    Laoyang(int ELEMENT,int ALL_HP,int ATK,double DEF, int SPEED = 100){
        name = "player" + std::to_string(ELEMENT);
        element_type = ELEMENT;
        hp = all_hp = ALL_HP;
        atk = ATK;
        def = DEF;
        speed = SPEED;
        mv_len = 1e4 / speed;
    }
    virtual void skill(vector<person*> enemys);
    virtual void action(int type, my_genshin* game);
};

//技能：使我方全体角色减伤30%,持续2回合
class Zhongli:public Player {
public:
    Zhongli(int ELEMENT,int ALL_HP,int ATK,double DEF, int SPEED = 100){
        name = "player" + std::to_string(ELEMENT);
        element_type = ELEMENT;
        hp = all_hp = ALL_HP;
        atk = ATK;
        def = DEF;
        speed = SPEED;
        mv_len = 1e4 / speed;
    }
    virtual void skill(vector<person*> players);
    virtual void action(int type, my_genshin* game);
};

//技能：使我方全体角色加速30%,持续2回合
class Xinhai:public Player {
public:
    Xinhai(int ELEMENT,int ALL_HP,int ATK,double DEF, int SPEED = 100){
        name = "player" + std::to_string(ELEMENT);
        element_type = ELEMENT;
        hp = all_hp = ALL_HP;
        atk = ATK;
        def = DEF;
        speed = SPEED;
        mv_len = 1e4 / speed;
    }
    virtual void skill(vector<person*> players);
    virtual void action(int type, my_genshin* game);
};

class Monster:public person{
public:
    double shield,shield_hp;
    int shield_time;
    int has_element = -1;

    virtual void under_attack(person* enemy);
    void SHIELD_BUILD();
    virtual void attack(){}
    virtual void skill(){}
    virtual void action(int type,my_genshin* game){}
};

class Boss1:public Monster{
public:
    int atk_cnt;
    Boss1(){}
    Boss1(int ELEMENT,int ALL_HP,int ATK,int DEF,int SHIELD);

    //    virtual void under_attack(person* enemy){}
    void SHIELD_BUILD();
    void attack(vector<person*> enemys);
    void skill(vector<person*> enemys);
    virtual void action(int type,my_genshin* game);
};

//游戏主进程
class my_genshin
{
public:
    int level;
    int round, lst_time;
    Monster* Boss;
    vector<person*> players;

    my_genshin(const int &LEVEL);
    vector<pair<double, person*> > get_mv_list(); //获取行动条
    vector<pair<double, person*> > get_virtual_mv_list(); //获取假设行动条
    Monster* Make_boss(int LEVEL);
    void run_game(); //游戏主进程
    void set_player();

    //1 赢 0 没结果 -1 输
    int judge_win();
    int Skill_point;
};

namespace load_save
{

void save_game(my_genshin* game);
int load_game();

}

#endif // ROLE_H
