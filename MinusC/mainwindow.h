#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include.h"
#include "codeeditor.h"
#include "highlighter.h"
#include "typedef.h"
#include "preprocess.h"
#include "lexical_analysis.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void on_preprocessButton_clicked();
    void on_lexicalButton_clicked();
    void on_grammarButton_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString srcfile;
    CodeEditor *configEditor;
    Highlighter *highlighter;
    Preprocess *preprocessor;
    LexicalAnalysis *lexicalAnalyzer;
    vector<Token> tokenList;
    vector<QString> lexicalError;
};
#endif // MAINWINDOW_H
