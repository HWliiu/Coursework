#include "card.h"
#include "ui_card.h"
#include <QImage>
#include <QLabel>

QImage * Card::frontImg=nullptr;
QImage * Card::backImg=nullptr;

Card::Card(QWidget *parent,int col,int num) :
    QWidget(parent),
    ui(new Ui::Card),color(col),number(num)
{
    ui->setupUi(this);
    if(frontImg==nullptr){
        frontImg=new QImage();
        frontImg->load("image/pokerMap.jpg");
        *frontImg=frontImg->scaled(1200,512,Qt::KeepAspectRatio);
    }
    if(backImg==nullptr){
        backImg=new QImage();
        backImg->load("image/back.jpg");
        *backImg=backImg->scaled(93,128,Qt::KeepAspectRatio);
    }
}

Card::~Card()
{
    delete ui;
}


void Card::showFront(){
    int w=frontImg->width()/13;
    int h=frontImg->height()/4;
    int col=color*h;
    int row=number*w;
    ui->label->setPixmap(QPixmap::fromImage(frontImg->copy(row, col, w,h)));
}

void Card::showBack(){
    ui->label->setPixmap(QPixmap::fromImage(*backImg));
}
