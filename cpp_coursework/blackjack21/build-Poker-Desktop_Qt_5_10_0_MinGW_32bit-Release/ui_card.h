/********************************************************************************
** Form generated from reading UI file 'card.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARD_H
#define UI_CARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Card
{
public:
    QLabel *label;

    void setupUi(QWidget *Card)
    {
        if (Card->objectName().isEmpty())
            Card->setObjectName(QStringLiteral("Card"));
        Card->resize(120, 200);
        Card->setMinimumSize(QSize(120, 200));
        Card->setMaximumSize(QSize(120, 200));
        Card->setCursor(QCursor(Qt::PointingHandCursor));
        label = new QLabel(Card);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(3, 1, 120, 200));
        label->setMinimumSize(QSize(120, 200));
        label->setMaximumSize(QSize(120, 200));
        label->setCursor(QCursor(Qt::PointingHandCursor));

        retranslateUi(Card);

        QMetaObject::connectSlotsByName(Card);
    } // setupUi

    void retranslateUi(QWidget *Card)
    {
        Card->setWindowTitle(QApplication::translate("Card", "Form", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Card: public Ui_Card {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARD_H
