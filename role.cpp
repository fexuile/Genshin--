#include "role.h"
#include "bot.h"
#include <qDebug>

void person::end_round()
{
    if (add_atk.second > 0) {
        if (!(--add_atk.second)) atk -= add_atk.first;
    }
    if (add_speed.second > 0) {
        if (!(--add_speed.second)) speed /= (1 + add_speed.first);
    }
    if (dec_speed.second > 0) {
        if (!(--dec_speed.second)) speed /= (1 - dec_speed.first);
    }
    if (dec_dmg.second > 0) --dec_dmg.second;
    if (vulnerable.second > 0) --vulnerable.second;
    mv_len = 1e4;
}

Player::Player(int ELEMENT, int ALL_HP, int ATK, int DEF, int SPEED)
{
    element_type = ELEMENT;
    hp = all_hp = ALL_HP;
    atk = ATK;
    def = DEF;
    speed = SPEED;
    mv_len = 1e4 / speed;
}

void Player::under_attack(person* enemy)
{
    double dec_hp = enemy->atk * this->def;
    if (dec_dmg.second > 0)
        dec_hp *= (1 - dec_dmg.first);
    if (vulnerable.second > 0)
        dec_hp *= (1 + vulnerable.first);
    hp -= enemy->atk * this->def;
}

void Player::attack(vector<person*> enemys)
{
    if (enemys.size() > 1)
        qWarning("default attack fault : too many objects");    
    for (auto enemy : enemys)
        enemy -> under_attack(this);
}

void Player::action(my_genshin* game)
{
    pair<int, vector<person*> > act = make_pair(0, vector<person*>());
    if (act.first == 0) {
//        this -> attack(act.second);
    } else {
//        this -> skill(act.second);
    }
}

void Qiqi::skill(vector<person*> players)
{
    if (players.size() > 1)
        qWarning("Qiqi skill fault : too many objects");    
    for (auto player : players) {
        player -> hp += all_hp * 0.1;
        player -> hp = max(player -> hp, player -> all_hp);
    }
}

void Keqin::skill(vector<person*> players)
{
    if (players.size() > 1)
        qWarning("Keqin skill fault : too many objects");
    for (auto player : players) {
        if (player->add_atk.second <= 0)
            player->atk += atk / 3;
        player -> add_atk = make_pair(atk / 3, 2);
        player -> mv_len = 0;
    }    
}

void Laoyang::skill(vector<person*> enemys)
{
    for (auto enemy : enemys) {
        enemy -> under_attack(this);
        enemy -> mv_len *= 1.2;
    }
}

void Zhongli::skill(vector<person*> players)
{
    for (auto player : players) {
        player -> dec_dmg = make_pair(0.3, 2);
    } 
}

void Xinhai::skill(vector<person*> players)
{
    for (auto player : players) {
        if (player -> add_speed.second <= 0)
            player -> speed *= 1.3;
        player -> add_speed = make_pair(0.3, 2);
    }    
}

void Monster::under_attack(person* enemy)
{
    if (shield > 0) {
        hp -= 0.5 * enemy->atk * this->def * (~has_element ? react[enemy->element_type][has_element] : 1);
        shield -= enemy->atk * (1 + (~has_element ? shield_react[enemy->element_type][has_element] : 0));
        if (shield <= 0) {
            hp -= 0.2 * enemy->atk * this->def * (~has_element ? react[enemy->element_type][has_element] : 1);
            shield_time = 5;
        }
        if (~has_element)
            has_element = -1;
        else
            has_element = enemy->element_type;
    } else {
        hp -= enemy->atk * this->def * (~has_element ? react[enemy->element_type][has_element] : 1);
        if (~has_element)
            has_element = -1;
        else
            has_element = enemy->element_type;
    }
}

void Monster::SHIELD_BUILD()
{
    shield_time -= 1;
    if (shield_time <= 0)
        shield = shield_hp;
}

Boss1::Boss1(int ELEMENT, int ALL_HP, int ATK, int DEF, int SHIELD)
{
    element_type = ELEMENT;
    hp = all_hp = ALL_HP;
    atk = ATK;
    def = DEF;
    shield = shield_hp = SHIELD;
    atk_cnt = 0;
}

void Boss1::attack(vector<person*> enemys)
{
    for (auto enemy : enemys)
        enemy -> under_attack(this);
}

void Boss1::skill(vector<person*> enemys)
{
    atk *= 2;
    for (auto enemy : enemys)
        enemy -> under_attack(this);
    atk /= 2;
}

void Boss1::action(my_genshin* game)
{
    pair<int, vector<person*> > act = boss1_bot::get_action(game, this);
    if (act.first == 0) {
        attack(act.second);
        ++game -> skill_points;
    } else {
    	if (game -> skill_points <= 0)
        	qWarning("skill points fault : have no skill points");    		
        skill(act.second);
        --game -> skill_points;
    }
}

void my_genshin::set_player(){
    players.push_back(new Qiqi(0, 15, 2, 0.8));
    players.push_back(new Keqin(1, 12,3, 0.6));
    players.push_back(new Laoyang(2, 7, 7, 0.9));
    players.push_back(new Zhongli(3, 10, 1, 0.3));
}

Monster* Make_boss(int level){
    if(level == 1){//yan kui qiuqiuwang
        Boss1* Boss = new Boss1;
        Boss->shield_hp = Boss->shield = 4;
        Boss->hp = Boss->all_hp = 20;
        Boss->atk = 3;
        Boss->def = 0.1;
        Boss->element_type = 1;
        Boss->shield_time = 0;
        Boss->name = "smallboss1";
        return Boss;
    }
    if(level == 2){

    }
}

my_genshin::my_genshin(const int &LEVEL)
{
    this->level = LEVEL;
    this->set_player();
    Boss = Make_boss(level);
}

vector<pair<double, person*> > my_genshin::get_mv_list()
{
    vector<pair<double, person*> > mv_list;
    for (auto player : players)
        mv_list.push_back(make_pair(player->mv_len / player->speed, player));
    mv_list.push_back(make_pair(Boss->mv_len / Boss->speed, Boss));
    sort(mv_list.begin(), mv_list.end());
    return mv_list;
}

void my_genshin::run_game()
{
    round = 0;
    lst_time = 100;
    skill_points = 3; 
    while (1) {
        auto p = (*get_mv_list().begin());
        p.second -> action(this);

        for (auto player : players)
            player->mv_len -= player->speed * p.first;
        Boss -> mv_len -= Boss->speed * p.first;
        p.second -> mv_len = 1e4;    
        while (lst_time < p.first) {
            ++round; lst_time += 100;
        }
        lst_time -= p.first;
    }
} 
