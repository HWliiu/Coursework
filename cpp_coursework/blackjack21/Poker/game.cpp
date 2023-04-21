#include "game.h"
#include "mainwindow.h"
#include <vector>

Game::Game()
{
    playerScore=0;
    bankerScore=0;

    for(int i=0;i<4;i++)
        for(int j=0;j<13;j++){
            gameCards.push_back(new Card(nullptr,i,j));
        }
}

void Game::StartGame(){
    playerScore=0;
    while(bankerCards.size() > 0){
        gameCards.push_back(bankerCards.back());
        bankerCards.pop_back();
    }
    while(playerCards.size() > 0){
        gameCards.push_back(playerCards.back());
        playerCards.pop_back();
    }
}

void Game::SendCard(vector<Card *> &Cards){
    if(gameCards.size()>0){
        srand(time(NULL));
        int pos=rand()%gameCards.size();
        Cards.push_back(gameCards[pos]);
        gameCards.erase(gameCards.begin()+pos);
    }
}

void Game::EndGame(){

}

int Game::CountScore(vector<Card *> &Cards){
    int totalScore=0;
    int flag=false;
    for(int i=0;i<Cards.size();i++){
        int score=Cards[i]->number+1;
        if(score == 1){
            flag=true;
         }
        score=score>10 ? 10 : score;
        totalScore+=score;
    }
    if(flag && totalScore<11){
        totalScore+=10;
    }

    return totalScore;
}

bool Game::isPlayerBombCard(){
    if(CountScore(playerCards) >21)
        return true;
    return false;
}

bool Game::isBankerBombCard(){
    if(CountScore(bankerCards) >21)
        return true;
    return false;
}

bool Game::isPlayerBlackJack(){
    if(CountScore(playerCards) == 21)
        return true;
    return false;
}

bool Game::isBankerBlackJack(){
    if(CountScore(bankerCards) == 21)
        return true;
    return false;
}

