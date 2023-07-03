#ifndef ROLE_H
#define ROLE_H
const double react[4][4]={{1,2,1.2,1.2},
                          {1.2,1,2,2},
                          {1.2,0.8,1,1.1},
                          {1.2,2,1.2,1}
};
const double shield_react[4][4]={{0,1,1,0.5},
                                 {0.5,0,1,1.5},
                                 {0.5,0.8,0,0.2},
                                 {0.2,1,0.5,0}
};
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
        hp -= enemy->atk * this->def * react[enemy->element_type][this->element_type];
    }
};

class Monster:public person{
public:
    double shield,shield_hp;
    int shield_time;
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
            hp -= 0.5 * enemy->atk * this->def * react[enemy->element_type][this->element_type];
            shield -= enemy->atk * shield_react[enemy->element_type][this->element_type];
            if(shield <= 0){
                hp -= 0.2 * enemy->atk * this->def * react[enemy->element_type][this->element_type];
                shield_time = 5;
            }
        }
        else{
            hp -= enemy->atk * this->def * react[enemy->element_type][this->element_type];
        }
    }
    void SHIELD_BUILD(){
        shield_time -= 1;
        if(shield_time <= 0)shield = shield_hp;
    }
};

#endif // ROLE_H
