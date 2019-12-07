/********************************************************************************
** Form generated from reading UI file 'GBG.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GBG_H
#define UI_GBG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GBGClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_img;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_text;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *textBrowser;
    QSpacerItem *horizontalSpacer;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GBGClass)
    {
        if (GBGClass->objectName().isEmpty())
            GBGClass->setObjectName(QStringLiteral("GBGClass"));
        GBGClass->resize(600, 400);
        centralWidget = new QWidget(GBGClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_img = new QLabel(centralWidget);
        label_img->setObjectName(QStringLiteral("label_img"));
        label_img->setMinimumSize(QSize(580, 170));

        verticalLayout->addWidget(label_img);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_text = new QLabel(centralWidget);
        label_text->setObjectName(QStringLiteral("label_text"));

        horizontalLayout_2->addWidget(label_text);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setMinimumSize(QSize(0, 20));

        verticalLayout_2->addWidget(textBrowser);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);

        GBGClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(GBGClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GBGClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GBGClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GBGClass->setStatusBar(statusBar);

        retranslateUi(GBGClass);

        QMetaObject::connectSlotsByName(GBGClass);
    } // setupUi

    void retranslateUi(QMainWindow *GBGClass)
    {
        GBGClass->setWindowTitle(QApplication::translate("GBGClass", "QtGuiApplication1", Q_NULLPTR));
        label_img->setText(QApplication::translate("GBGClass", "\347\255\211\345\276\205\346\211\223\345\274\200\345\233\276\347\211\207...", Q_NULLPTR));
        pushButton->setText(QApplication::translate("GBGClass", "\345\236\203\345\234\276\345\210\206\347\261\273", Q_NULLPTR));
        label_text->setText(QApplication::translate("GBGClass", "\345\236\203\345\234\276\344\270\272\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GBGClass: public Ui_GBGClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GBG_H
