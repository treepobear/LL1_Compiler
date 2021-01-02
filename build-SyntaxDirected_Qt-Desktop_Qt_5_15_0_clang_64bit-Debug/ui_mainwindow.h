/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionshow_grammar;
    QAction *actionshow_predictable_analyze_table;
    QAction *actioncomputing_first_set;
    QAction *actioncompute_follow_set;
    QAction *actionshow_token_list;
    QAction *actionshow;
    QAction *actionshow_symbol_table;
    QAction *actionshow_mid_code;
    QWidget *centralwidget;
    QPlainTextEdit *plainTextEdit_out;
    QPlainTextEdit *plainTextEdit_watch;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_src;
    QMenuBar *menuBar;
    QMenu *open;
    QMenu *save;
    QMenu *construct;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(706, 604);
        actionshow_grammar = new QAction(MainWindow);
        actionshow_grammar->setObjectName(QString::fromUtf8("actionshow_grammar"));
        actionshow_predictable_analyze_table = new QAction(MainWindow);
        actionshow_predictable_analyze_table->setObjectName(QString::fromUtf8("actionshow_predictable_analyze_table"));
        actioncomputing_first_set = new QAction(MainWindow);
        actioncomputing_first_set->setObjectName(QString::fromUtf8("actioncomputing_first_set"));
        actioncompute_follow_set = new QAction(MainWindow);
        actioncompute_follow_set->setObjectName(QString::fromUtf8("actioncompute_follow_set"));
        actionshow_token_list = new QAction(MainWindow);
        actionshow_token_list->setObjectName(QString::fromUtf8("actionshow_token_list"));
        actionshow = new QAction(MainWindow);
        actionshow->setObjectName(QString::fromUtf8("actionshow"));
        actionshow_symbol_table = new QAction(MainWindow);
        actionshow_symbol_table->setObjectName(QString::fromUtf8("actionshow_symbol_table"));
        actionshow_mid_code = new QAction(MainWindow);
        actionshow_mid_code->setObjectName(QString::fromUtf8("actionshow_mid_code"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        plainTextEdit_out = new QPlainTextEdit(centralwidget);
        plainTextEdit_out->setObjectName(QString::fromUtf8("plainTextEdit_out"));
        plainTextEdit_out->setGeometry(QRect(0, 380, 711, 201));
        plainTextEdit_watch = new QPlainTextEdit(centralwidget);
        plainTextEdit_watch->setObjectName(QString::fromUtf8("plainTextEdit_watch"));
        plainTextEdit_watch->setGeometry(QRect(540, 0, 171, 381));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 541, 381));
        gridLayout_src = new QGridLayout(gridLayoutWidget);
        gridLayout_src->setObjectName(QString::fromUtf8("gridLayout_src"));
        gridLayout_src->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 706, 24));
        open = new QMenu(menuBar);
        open->setObjectName(QString::fromUtf8("open"));
        save = new QMenu(menuBar);
        save->setObjectName(QString::fromUtf8("save"));
        construct = new QMenu(menuBar);
        construct->setObjectName(QString::fromUtf8("construct"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(open->menuAction());
        menuBar->addAction(save->menuAction());
        menuBar->addAction(construct->menuAction());
        menuBar->addAction(menu->menuAction());
        construct->addAction(actionshow_grammar);
        construct->addAction(actioncomputing_first_set);
        construct->addAction(actioncompute_follow_set);
        construct->addAction(actionshow_predictable_analyze_table);
        menu->addAction(actionshow_token_list);
        menu->addAction(actionshow);
        menu->addAction(actionshow_symbol_table);
        menu->addAction(actionshow_mid_code);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionshow_grammar->setText(QCoreApplication::translate("MainWindow", "grammar definition", nullptr));
        actionshow_predictable_analyze_table->setText(QCoreApplication::translate("MainWindow", "predictable analyze table", nullptr));
        actioncomputing_first_set->setText(QCoreApplication::translate("MainWindow", "first set", nullptr));
        actioncompute_follow_set->setText(QCoreApplication::translate("MainWindow", "follow set", nullptr));
        actionshow_token_list->setText(QCoreApplication::translate("MainWindow", "show token list", nullptr));
        actionshow->setText(QCoreApplication::translate("MainWindow", "show annotated parse tree", nullptr));
        actionshow_symbol_table->setText(QCoreApplication::translate("MainWindow", "show symbol table", nullptr));
        actionshow_mid_code->setText(QCoreApplication::translate("MainWindow", "show mid code", nullptr));
        open->setTitle(QCoreApplication::translate("MainWindow", "open", nullptr));
        save->setTitle(QCoreApplication::translate("MainWindow", "save", nullptr));
        construct->setTitle(QCoreApplication::translate("MainWindow", "construct analyzer", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "run", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
