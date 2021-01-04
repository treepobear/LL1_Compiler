#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QMenu"
#include "QMenuBar"
#include "QAction"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->setNativeMenuBar(false);
    ui->horizontalLayout->setAlignment(Qt::AlignLeft);
    editor = new CodeEditor();
    editor->setMode(EDIT);
    ui->gridLayout_src->addWidget(editor);
    lexcialAnalyzer = new LexcialAnalysis();
    syntaxAnalyzer = new SyntaxAnalysis();

    connect(ui->actionshow_token_list,SIGNAL(triggered()),this,SLOT(onaction_actionshow_token_list()));
    connect(ui->actioncomputing_first_set,SIGNAL(triggered()),this,SLOT(onaction_firstshow()));
    connect(ui->actioncompute_follow_set,SIGNAL(triggered()),this,SLOT(onaction_followshow()));
    connect(ui->actionshow_grammar,SIGNAL(triggered()),this,SLOT(onaction_grammarshow()));
    connect(ui->actionshow_predictable_analyze_table,SIGNAL(triggered()),this,SLOT(onaction_patableshow()));
    connect(ui->actionshow_symbol_table,SIGNAL(triggered()),this,SLOT(onaction_actionshow_symbol_table()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onaction_actionshow_token_list(){

    //1.获取输入的源文件,预处理
    QTextDocument *src = editor->document();
    QString srcfile = "";
    for(QTextBlock c = src->begin();
        c != src->end();
        c = c.next()){
        srcfile += c.text();
        srcfile += "\n";    //因为是一行一行读所以要加上换行符（保留基本格式 好看）
    }
    srcfile = lexcialAnalyzer->delBlanks(srcfile);
    editor->setPlainText(srcfile);
    srcfile = lexcialAnalyzer->delComments(srcfile);

    //2.输出token list
    lexcialAnalyzer->analyze(srcfile);
    QString out = "-------------------------------------Lexical error--------------------------------------\n";
    for(size_t i=0;i<lexcialAnalyzer->lexcialError.size();i++){
        out += QString::fromStdString(lexcialAnalyzer->lexcialError[i]);
        out += "\n";
    }
    stringstream ss;
    out += "--------------------------------------Token list----------------------------------------\n";
    vector<Token>  tokenList = lexcialAnalyzer->tokenList;
    for(size_t i=0;i<tokenList.size();i++){
        ss<<tokenList[i].lexeme<<"\t"<<left<<setw(5);
        ss<<right<<tokenList[i].type<<"\t"<<left<<setw(10);
        ss<<right<<tokenList[i].line<<right<<setw(10);
        ss<<right<<tokenList[i].pos<<"\n";
    }
    out += QString::fromStdString(ss.str());
    ui->plainTextEdit_out->setPlainText(out);

}

void MainWindow::onaction_firstshow(){
    ui->plainTextEdit_out->setPlainText(syntaxAnalyzer->firstlistToString());
}

void MainWindow::onaction_followshow(){
    ui->plainTextEdit_out->setPlainText(syntaxAnalyzer->followlistToString());
}

void MainWindow::onaction_grammarshow(){
    ui->plainTextEdit_out->setPlainText(syntaxAnalyzer->originToString());
}

void MainWindow::onaction_patableshow(){
    ui->plainTextEdit_out->setPlainText(syntaxAnalyzer->patableToString());
}

void MainWindow::onaction_actionshow_symbol_table(){
    syntaxAnalyzer = new SyntaxAnalysis();
    string stackinfo = "------------------------------------Stack info record----------------------------------\n";
    stackinfo += syntaxAnalyzer->make_tree(lexcialAnalyzer->tokenList);
    QString out = "--------------------------------------Syntax error-------------------------------------\n";

    out += QString::fromStdString(syntaxAnalyzer->syntaxError);
    out += "\n";

    ui->plainTextEdit_out->setPlainText(out+QString::fromStdString(stackinfo));
}

void MainWindow::on_clearButton_clicked(){
    lexcialAnalyzer = new LexcialAnalysis();
    syntaxAnalyzer = new SyntaxAnalysis();
    ui->plainTextEdit_out->setPlainText("");
}
