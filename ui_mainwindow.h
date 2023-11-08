/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "piecesview.h"
#include "puzzleview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    PuzzleView *puzzleWidget;
    QSpacerItem *horizontalSpacer;
    PiecesView *piecesWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *newGameButton;
    QPushButton *sizeButton;
    QPushButton *closeButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *saveButton;
    QPushButton *openButton;
    QSpacerItem *verticalSpacer_3;
    QPushButton *rulesButton;
    QSpacerItem *verticalSpacer_4;
    QLabel *scoreLTextLabel;
    QLabel *scoreLNumLabel;
    QSpacerItem *verticalSpacer;
    QPushButton *aboutButton;
    QSpacerItem *verticalSpacer_5;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1445, 1169);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icons/components.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        puzzleWidget = new PuzzleView(centralWidget);
        puzzleWidget->setObjectName(QString::fromUtf8("puzzleWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(puzzleWidget->sizePolicy().hasHeightForWidth());
        puzzleWidget->setSizePolicy(sizePolicy2);
        puzzleWidget->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(puzzleWidget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        piecesWidget = new PiecesView(centralWidget);
        piecesWidget->setObjectName(QString::fromUtf8("piecesWidget"));
        sizePolicy2.setHeightForWidth(piecesWidget->sizePolicy().hasHeightForWidth());
        piecesWidget->setSizePolicy(sizePolicy2);
        piecesWidget->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(piecesWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        newGameButton = new QPushButton(centralWidget);
        newGameButton->setObjectName(QString::fromUtf8("newGameButton"));
        QFont font;
        font.setPointSize(10);
        newGameButton->setFont(font);

        verticalLayout->addWidget(newGameButton);

        sizeButton = new QPushButton(centralWidget);
        sizeButton->setObjectName(QString::fromUtf8("sizeButton"));
        sizeButton->setFont(font);

        verticalLayout->addWidget(sizeButton);

        closeButton = new QPushButton(centralWidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setFont(font);

        verticalLayout->addWidget(closeButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setFont(font);

        verticalLayout->addWidget(saveButton);

        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setFont(font);

        verticalLayout->addWidget(openButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        rulesButton = new QPushButton(centralWidget);
        rulesButton->setObjectName(QString::fromUtf8("rulesButton"));
        rulesButton->setFont(font);

        verticalLayout->addWidget(rulesButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        scoreLTextLabel = new QLabel(centralWidget);
        scoreLTextLabel->setObjectName(QString::fromUtf8("scoreLTextLabel"));
        QFont font1;
        font1.setPointSize(14);
        scoreLTextLabel->setFont(font1);

        verticalLayout->addWidget(scoreLTextLabel);

        scoreLNumLabel = new QLabel(centralWidget);
        scoreLNumLabel->setObjectName(QString::fromUtf8("scoreLNumLabel"));
        QFont font2;
        font2.setPointSize(28);
        font2.setBold(true);
        font2.setWeight(75);
        scoreLNumLabel->setFont(font2);

        verticalLayout->addWidget(scoreLNumLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        aboutButton = new QPushButton(centralWidget);
        aboutButton->setObjectName(QString::fromUtf8("aboutButton"));
        aboutButton->setFont(font);

        verticalLayout->addWidget(aboutButton);

        verticalSpacer_5 = new QSpacerItem(77, 37, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(puzzleWidget, SIGNAL(placeIsSelectedSignal(int)), MainWindow, SLOT(placeIsSelectedSlot(int)));
        QObject::connect(piecesWidget, SIGNAL(pieceIsSelectedSignal(QImage)), MainWindow, SLOT(pieceIsSelectedSlot(QImage)));
        QObject::connect(puzzleWidget, SIGNAL(pieceToMoveSignal(int,int)), MainWindow, SLOT(pieceToMoveSlot(int,int)));
        QObject::connect(puzzleWidget, SIGNAL(pieceToDeleteSignal(int)), MainWindow, SLOT(pieceToDeleteSlot(int)));
        QObject::connect(puzzleWidget, SIGNAL(pieceToRightPlaceSignal(int)), MainWindow, SLOT(pieceToRightPlaceSlot(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Puzzle", nullptr));
        newGameButton->setText(QCoreApplication::translate("MainWindow", "New Game", nullptr));
        sizeButton->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        closeButton->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        openButton->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        rulesButton->setText(QCoreApplication::translate("MainWindow", "Rules", nullptr));
        scoreLTextLabel->setText(QCoreApplication::translate("MainWindow", "Pieces left:", nullptr));
        scoreLNumLabel->setText(QString());
        aboutButton->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
