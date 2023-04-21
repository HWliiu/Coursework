#ifndef GAME_H
#define GAME_H
#include <vector>
#include <functional>
#include "card.h"

using namespace std;

class Game
{
public:
    int playerScore;
    int bankerScore;
    vector<Card *> gameCards;
    vector<Card *> playerCards;
    vector<Card *> bankerCards;
    Game();
    void StartGame();
    void EndGame();
    void SendCard(vector<Card *> &Cards);
    int CountScore(vector<Card *> &Cards);
    bool isPlayerBombCard();
    bool isBankerBombCard();
    bool isPlayerBlackJack();
    bool isBankerBlackJack();
};

#endif // GAME_H
