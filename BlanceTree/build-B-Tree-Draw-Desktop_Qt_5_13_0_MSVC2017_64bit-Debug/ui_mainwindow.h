/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *input;
    QSpacerItem *horizontalSpacer;
    QPushButton *BT_insert;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *BT_del;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *BT_search;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1255, 633);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(230, 10, 711, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        input = new QLineEdit(layoutWidget);
        input->setObjectName(QString::fromUtf8("input"));
        input->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(input);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BT_insert = new QPushButton(layoutWidget);
        BT_insert->setObjectName(QString::fromUtf8("BT_insert"));

        horizontalLayout->addWidget(BT_insert);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        BT_del = new QPushButton(layoutWidget);
        BT_del->setObjectName(QString::fromUtf8("BT_del"));

        horizontalLayout->addWidget(BT_del);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        BT_search = new QPushButton(layoutWidget);
        BT_search->setObjectName(QString::fromUtf8("BT_search"));

        horizontalLayout->addWidget(BT_search);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(input, BT_insert);
        QWidget::setTabOrder(BT_insert, BT_del);
        QWidget::setTabOrder(BT_del, BT_search);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Balance-Tree", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\346\223\215\344\275\234\346\225\260\357\274\232", nullptr));
        BT_insert->setText(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245", nullptr));
        BT_del->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        BT_search->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
