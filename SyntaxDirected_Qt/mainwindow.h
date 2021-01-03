#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "code_editor.h"
#include "lexcial_analysis.h"
#include "syntax_analysis.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void onaction_actionshow_token_list();
    void onaction_grammarshow();
    void onaction_firstshow();
    void onaction_followshow();
    void onaction_patableshow();
    void on_clearButton_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CodeEditor *editor;
    LexcialAnalysis *lexcialAnalyzer;
    SyntaxAnalysis *syntaxAnalyzer;
};
#endif // MAINWINDOW_H
