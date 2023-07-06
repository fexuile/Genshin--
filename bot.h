#ifndef BOT_H
#define BOT_H

#include <random>
#include <vector>
#include "role.h"
#include <map>

using std::vector;
using std::pair;

namespace boss1_bot
{
    pair<int, vector<person*>> get_action(my_genshin* game, Boss1* boss) ;
}

#endif // BOT_H
