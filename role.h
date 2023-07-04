#ifndef ROLE_H
#define ROLE_H
#include <set>
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
    int atk;
    double def;
    virtual void attack(person* enemy)=0;
};

class Player:public person{
public:
    Player(){}
    Player(int ELEMENT,int ALL_HP,int ATK,int DEF){
        element_type = ELEMENT;
        hp = all_hp = ALL_HP;
        atk = ATK;
        def = DEF;
    }
    virtual void attack(person* enemy){
        hp -= enemy->atk * this->def;
    }
};

class Monster:public person{
public:
    double shield,shield_hp;
    int shield_time;
    int has_element = -1;
    Monster(){}
    Monster(int ELEMENT,int ALL_HP,int ATK,int DEF,int SHIELD){
        element_type = ELEMENT;
        hp = all_hp = ALL_HP;
        atk = ATK;
        def = DEF;
        shield = shield_hp = SHIELD;
    }
    virtual void attack(person* enemy){
        if(shield > 0){
            hp -= 0.5 * enemy->atk * this->def * (~has_element ? react[enemy->element_type][has_element]: 1);
            shield -= enemy->atk * (1 + (~has_element?shield_react[enemy->element_type][has_element]:0));
            if(shield <= 0){
                hp -= 0.2 * enemy->atk * this->def * (~has_element ? react[enemy->element_type][has_element]: 1);
                shield_time = 5;
            }
            if(~has_element)has_element = -1;
            else has_element = enemy->element_type;
        }
        else{
            hp -= enemy->atk * this->def * (~has_element ? react[enemy->element_type][has_element]:1);
            if(~has_element)has_element = -1;
            else has_element = enemy->element_type;
        }
    }
    void SHIELD_BUILD(){
        shield_time -= 1;
        if(shield_time <= 0)shield = shield_hp;
    }
};

#endif // ROLE_H
