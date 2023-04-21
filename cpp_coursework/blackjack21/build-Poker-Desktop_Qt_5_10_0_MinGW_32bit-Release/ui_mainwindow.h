/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *newGameButton;
    QPushButton *addCardButton;
    QPushButton *compareButton;
    QLabel *messageLabel;
    QLabel *scoreLabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *subTableLayout3;
    QHBoxLayout *subTableLayout2;
    QHBoxLayout *subTableLayout4;
    QHBoxLayout *subTableLayout1;
    QSpacerItem *verticalSpacer;
    QWidget *layoutWidget1;
    QHBoxLayout *bankerLayout;
    QWidget *layoutWidget2;
    QHBoxLayout *playerLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 720);
        MainWindow->setMinimumSize(QSize(400, 300));
        MainWindow->setMaximumSize(QSize(1280, 720));
        QPalette palette;
        QBrush brush(QColor(20, 20, 20, 196));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush1(QColor(46, 47, 48, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush2(QColor(0, 153, 204, 128));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        QBrush brush3(QColor(164, 166, 168, 96));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        MainWindow->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(12);
        MainWindow->setFont(font);
        MainWindow->setWindowOpacity(1);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(9, 9, 91, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(520, 10, 71, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 210, 71, 31));
        newGameButton = new QPushButton(centralWidget);
        newGameButton->setObjectName(QStringLiteral("newGameButton"));
        newGameButton->setGeometry(QRect(187, 610, 80, 25));
        QFont font1;
        font1.setPointSize(10);
        newGameButton->setFont(font1);
        addCardButton = new QPushButton(centralWidget);
        addCardButton->setObjectName(QStringLiteral("addCardButton"));
        addCardButton->setGeometry(QRect(364, 610, 80, 25));
        addCardButton->setFont(font1);
        compareButton = new QPushButton(centralWidget);
        compareButton->setObjectName(QStringLiteral("compareButton"));
        compareButton->setGeometry(QRect(542, 610, 80, 25));
        compareButton->setFont(font1);
        messageLabel = new QLabel(centralWidget);
        messageLabel->setObjectName(QStringLiteral("messageLabel"));
        messageLabel->setGeometry(QRect(20, 460, 511, 31));
        QPalette palette1;
        QBrush brush4(QColor(255, 209, 43, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush5(QColor(49, 235, 244, 128));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush5);
        messageLabel->setPalette(palette1);
        QFont font2;
        font2.setFamily(QStringLiteral("Arial Rounded MT Bold"));
        font2.setPointSize(18);
        messageLabel->setFont(font2);
        scoreLabel = new QLabel(centralWidget);
        scoreLabel->setObjectName(QStringLiteral("scoreLabel"));
        scoreLabel->setGeometry(QRect(103, 210, 261, 31));
        QPalette palette2;
        QBrush brush6(QColor(170, 255, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        scoreLabel->setPalette(palette2);
        QFont font3;
        font3.setFamily(QStringLiteral("Arial Narrow"));
        font3.setPointSize(14);
        font3.setItalic(false);
        scoreLabel->setFont(font3);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(520, 20, 461, 441));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        verticalLayout->addLayout(horizontalLayout);

        subTableLayout3 = new QHBoxLayout();
        subTableLayout3->setSpacing(6);
        subTableLayout3->setObjectName(QStringLiteral("subTableLayout3"));
        subTableLayout3->setSizeConstraint(QLayout::SetNoConstraint);
        subTableLayout3->setContentsMargins(0, 0, 10, -1);

        verticalLayout->addLayout(subTableLayout3);

        subTableLayout2 = new QHBoxLayout();
        subTableLayout2->setSpacing(6);
        subTableLayout2->setObjectName(QStringLiteral("subTableLayout2"));
        subTableLayout2->setSizeConstraint(QLayout::SetNoConstraint);
        subTableLayout2->setContentsMargins(10, -1, 10, -1);

        verticalLayout->addLayout(subTableLayout2);

        subTableLayout4 = new QHBoxLayout();
        subTableLayout4->setSpacing(6);
        subTableLayout4->setObjectName(QStringLiteral("subTableLayout4"));
        subTableLayout4->setSizeConstraint(QLayout::SetNoConstraint);
        subTableLayout4->setContentsMargins(-1, -1, 10, -1);

        verticalLayout->addLayout(subTableLayout4);

        subTableLayout1 = new QHBoxLayout();
        subTableLayout1->setSpacing(6);
        subTableLayout1->setObjectName(QStringLiteral("subTableLayout1"));
        subTableLayout1->setSizeConstraint(QLayout::SetNoConstraint);
        subTableLayout1->setContentsMargins(10, -1, 10, 10);

        verticalLayout->addLayout(subTableLayout1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(3, 3);
        verticalLayout->setStretch(4, 4);
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(9, 24, 461, 171));
        bankerLayout = new QHBoxLayout(layoutWidget1);
        bankerLayout->setSpacing(6);
        bankerLayout->setContentsMargins(11, 11, 11, 11);
        bankerLayout->setObjectName(QStringLiteral("bankerLayout"));
        bankerLayout->setContentsMargins(0, 0, 0, 0);
        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 230, 461, 194));
        playerLayout = new QHBoxLayout(layoutWidget2);
        playerLayout->setSpacing(6);
        playerLayout->setContentsMargins(11, 11, 11, 11);
        playerLayout->setObjectName(QStringLiteral("playerLayout"));
        playerLayout->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "21\347\202\271", nullptr));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:20pt; font-weight:600; color:#00ff7f;\">\345\272\204\345\256\266\357\274\232</span></p></body></html>", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:20pt; font-weight:600; color:#ffaa00;\">\345\215\241\347\211\214\357\274\232</span></p></body></html>", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:20pt; font-weight:600; color:#ff557f;\">\347\216\251\345\256\266\357\274\232</span></p></body></html>", nullptr));
        newGameButton->setText(QApplication::translate("MainWindow", "\346\226\260\346\270\270\346\210\217", nullptr));
        addCardButton->setText(QApplication::translate("MainWindow", "\350\246\201\347\211\214", nullptr));
        compareButton->setText(QApplication::translate("MainWindow", "\346\257\224\347\211\214", nullptr));
        messageLabel->setText(QString());
        scoreLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
