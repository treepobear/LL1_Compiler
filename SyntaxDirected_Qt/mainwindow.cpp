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
    QString out = "--------------------------Lexical error---------------------------\n";
    for(size_t i=0;i<lexcialAnalyzer->lexcialError->size();i++){
        out += (*lexcialAnalyzer->lexcialError)[i];
        out += "\n";
    }
    stringstream ss;
    out += "-------------------------Token list------------------------------\n";
    vector<Token>  tokenList = *lexcialAnalyzer->tokenList;
    for(size_t i=0;i<tokenList.size();i++){
        ss<<tokenList[i].lexeme.toStdString().data()<<left<<setw(30);
        ss<<right<<tokenList[i].type.toStdString().data()<<left<<setw(40);
        ss<<right<<tokenList[i].line<<right<<setw(10);
        ss<<right<<tokenList[i].pos<<"\n";
    }
    out += QString::fromStdString(ss.str());
    ui->plainTextEdit_out->setPlainText(out);

}

void MainWindow::onaction_firstshow(){

}

void MainWindow::onaction_followshow(){


}

void MainWindow::onaction_grammarshow(){
    stringstream ss;
    vector<string>::iterator iter;

    for(iter = syntaxAnalyzer->origin.begin();iter != syntaxAnalyzer->origin.end();iter++){
        ss<<*iter<<endl;
    }

    QString out = QString::fromStdString(ss.str());
    ui->plainTextEdit_out->setPlainText(out);
}

void MainWindow::onaction_patableshow(){
    stringstream ss;
    vector<string>::iterator iter;

    ss << setw(20) << "";
    for (iter = syntaxAnalyzer->vt.begin();iter != syntaxAnalyzer->vt.end();iter++)
        if (*iter != "empty")
            ss << setw(8) << left << *iter;
    ss << endl;
    int i,j;
    for (iter = syntaxAnalyzer->vn.begin(), i = 1;iter != syntaxAnalyzer->vn.end();iter++, i++)
    {
        ss << setw(20) << left << *iter;
        for (j = 1;j <= syntaxAnalyzer->patable.vtnum;j++)
            ss << setw(8) << left << syntaxAnalyzer->patable.pat[i][j];
        ss << endl;
    }

    QString out = QString::fromStdString(ss.str());
    ui->plainTextEdit_out->setPlainText(out);
}
