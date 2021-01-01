#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    configEditor = new CodeEditor();
    configEditor->setMode(EDIT);
    ui->gridLayout_src->addWidget(configEditor);
    highlighter = new Highlighter(configEditor->document());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_preprocessButton_clicked(){

    //1.预处理
    //获取输入的源文件
    QTextDocument *src = configEditor->document();
    srcfile = "";
    for(QTextBlock c = src->begin();
        c != src->end();
        c = c.next()){
        srcfile += c.text();
        srcfile += "\n";    //因为是一行一行读所以要加上换行符（为了之后报错的时候提示在第几行）
    }
    //消去注释
    srcfile = preprocessor->delComments(srcfile);
    //消去空格和tab
    srcfile = preprocessor->delBlanks(srcfile);

    configEditor->setPlainText(srcfile);
//    ui->plainTextEdit_out->setPlainText(srcfile);
}

void MainWindow::on_lexicalButton_clicked(){

    //2.词法分析
    lexicalAnalyzer->analyze(srcfile,tokenList,lexicalError);
    QString out = "----------Lexical error----------\n";
    for(size_t i=0;i<lexicalError.size();i++){
        out += lexicalError[i];
        out += "\n";
    }

    out += "----------Token list----------\n";
    for(size_t i=0;i<tokenList.size();i++){
        out += tokenList[i].lexeme.toStdString().data();
        out += " ";
        out += tokenList[i].type.toStdString().data();
        out += " ";
        out += QString::number(tokenList[i].line);
        out += " ";
        out += QString::number(tokenList[i].pos);
        out += "\n";
    }
    ui->plainTextEdit_out->setPlainText(out);
}

void MainWindow::on_grammarButton_clicked(){
    //3.语法、语义分析生成中间代码

}
