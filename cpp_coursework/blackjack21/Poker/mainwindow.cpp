#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <vector>
#include <time.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    onStartGame(game.gameCards);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newGameButton_clicked()
{
    onStartGame(game.gameCards);
}

void MainWindow::on_addCardButton_clicked()
{
    onAddCardToPlayer();
    onAddCardToBanker();
}

void MainWindow::on_compareButton_clicked()
{
    onCompare();

}


void MainWindow::onStartGame(vector<Card *> &Cards){
    ui->scoreLabel->setText("0");
    game.StartGame();
    for(int i=0;i<Cards.size();i++){
        if(i<13)
            ui->subTableLayout1->layout()->addWidget(Cards[i]);
        else if(i<26)
            ui->subTableLayout2->layout()->addWidget(Cards[i]);
        else if(i<39)
            ui->subTableLayout3->layout()->addWidget(Cards[i]);
        else
            ui->subTableLayout4->layout()->addWidget(Cards[i]);

        Cards[i]->showFront();
    }

    game.SendCard(game.bankerCards);
    ui->bankerLayout->layout()->addWidget(game.bankerCards[0]);
    game.bankerCards[0]->showBack();
    onAddCardToPlayer();
    onAddCardToBanker();
    onAddCardToPlayer();

    ui->messageLabel->setText("开始游戏...");
    ui->newGameButton->setDisabled(true);
    ui->addCardButton->setDisabled(false);
    ui->compareButton->setDisabled(false);
}

void MainWindow::onAddCardToPlayer(){
    ui->messageLabel->setText("是否继续加牌...");
    game.SendCard(game.playerCards);
    game.playerScore=game.CountScore(game.playerCards);
    for(int i=0;i<game.playerCards.size();i++){
        ui->playerLayout->layout()->addWidget(game.playerCards[i]);
        game.playerCards[i]->showFront();
    }
    ui->scoreLabel->setText(QString("您现在的分数为%1").arg(game.playerScore));
    onJudge();

}

void MainWindow::onAddCardToBanker(){
    if(game.CountScore(game.bankerCards) < 13)
        game.SendCard(game.bankerCards);
    //game.bankerScore=game.CountScore(game.bankerCards);
    for(int i=0;i<game.bankerCards.size();i++){
        ui->bankerLayout->layout()->addWidget(game.bankerCards[i]);
        if(i!=0){
            game.bankerCards[i]->showFront();
        }

    }
}

void MainWindow::onCompare(){
    if(game.CountScore(game.playerCards)<=21 && game.CountScore(game.bankerCards)<=21){
        if(game.CountScore(game.playerCards) > game.CountScore(game.bankerCards))
            ui->messageLabel->setText(QString("恭喜你赢了...庄家的分数为%1").arg(game.CountScore(game.bankerCards)));
        else if(game.CountScore(game.playerCards) < game.CountScore(game.bankerCards))
            ui->messageLabel->setText(QString("很遗憾你输了...庄家的分数为%1").arg(game.CountScore(game.bankerCards)));
        else
            ui->messageLabel->setText(QString("震惊！！！双方竟然打成了平手...庄家的分数也为%1").arg(game.CountScore(game.bankerCards)));
    }else{
     if(game.CountScore(game.playerCards)>21)
         ui->messageLabel->setText(QString("很遗憾你输了...你爆牌了...庄家的分数为%1").arg(game.CountScore(game.bankerCards)));
     else
         ui->messageLabel->setText(QString("恭喜你赢了...庄家爆牌了...庄家的分数为%1").arg(game.CountScore(game.bankerCards)));
    }
    onEnd();

}

void MainWindow::onJudge(){
    if(game.isPlayerBombCard() && !game.isBankerBombCard()){
        ui->messageLabel->setText(QString("很遗憾你输了...你爆牌了...庄家的分数为%1").arg(game.CountScore(game.bankerCards)));
        onEnd();
    }else if(!game.isPlayerBombCard() && game.isBankerBombCard()){
        ui->messageLabel->setText(QString("恭喜你赢了...庄家爆牌了...庄家的分数为%1").arg(game.CountScore(game.bankerCards)));
        onEnd();
    }else if(game.isPlayerBlackJack() && !game.isBankerBlackJack()){
        ui->messageLabel->setText(QString("恭喜你赢了...你拿到了黑杰克...庄家的分数为%1").arg(game.CountScore(game.bankerCards)));
        onEnd();
    }else if(!game.isPlayerBlackJack() && game.isBankerBlackJack()){
        ui->messageLabel->setText(QString("很遗憾你输了...庄家是黑杰克...庄家的分数为%1").arg(game.CountScore(game.bankerCards)));
        onEnd();
    }else if(game.isPlayerBlackJack() && game.isBankerBlackJack()){
        ui->messageLabel->setText(QString("奇迹!!!...双方都是黑杰克!!!再战再战!!!...庄家的分数为%1").arg(game.CountScore(game.bankerCards)));
        onEnd();
    }else if(game.isPlayerBombCard() && game.isBankerBombCard()){
        ui->messageLabel->setText(QString("真惨!!!...双方都爆牌了!!!再战再战!!!...庄家的分数为%1").arg(game.CountScore(game.bankerCards)));
        onEnd();
    }
}

void MainWindow::onEnd(){
    game.bankerCards[0]->showFront();
    ui->newGameButton->setDisabled(false);
    ui->addCardButton->setDisabled(true);
    ui->compareButton->setDisabled(true);
}
