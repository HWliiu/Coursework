#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "game.h"
#include <QMainWindow>
#include <QString>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void onStartGame(std::vector<Card *> &Cards);
    void onAddCardToPlayer();
    void onAddCardToBanker();
    void onCompare();
    void onJudge();
    void onEnd();
private slots:
    
    void on_newGameButton_clicked();
    
    void on_addCardButton_clicked();
    
    void on_compareButton_clicked();
    
private:
    Ui::MainWindow *ui;
    Game game;
};

#endif // MAINWINDOW_H
