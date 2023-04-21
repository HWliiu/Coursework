#ifndef CARD_H
#define CARD_H

#include <QWidget>

namespace Ui {
class Card;
}

class Card : public QWidget
{
    Q_OBJECT

public:
    int color;
    int number;
    explicit Card(QWidget *parent = 0,int color=0,int number=0);
    ~Card();
    void showFront();
    void showBack();

private:
    Ui::Card *ui;
    static QImage *frontImg;
    static QImage *backImg;
};

#endif // CARD_H
