#include "bot.h"

pair<int, vector<person*>> boss1_bot::get_action(my_genshin* game, Boss1* boss)
{
    ++boss->atk_cnt;
    if (boss->atk_cnt % 3 == 0)
        return make_pair(1, game->players);
    else {
        int p = rand() % 10;
        if (p < 3) {
            person* choosen_player = game->players[0];
            for (auto player : game->players)
                if (player->hp > 0 && (player->hp < choosen_player->hp || choosen_player->hp < 0))
                    choosen_player = player;
            return make_pair(0, vector<person*>(1, choosen_player));
        } else {
            vector<person*> alive_players;
            for (auto player : game->players)
                if (player->hp > 0)
                    alive_players.push_back(player);
            random_shuffle(alive_players.begin(), alive_players.end());
            return make_pair(0, vector<person*>(1, alive_players[0]));
        }
    }
}