#ifndef SYNTAXANALYSIS_H
#define SYNTAXANALYSIS_H
#include "includes.h"


class SyntaxAnalysis
{
public:
    SyntaxAnalysis();
    vector<string> origin = {
        /**
         * 文法G是LL(1)的，当且仅当对于G的每个非终结符Α的任何两个不同产生式
            Α→α,Α→β均满足下面条件(其中α和β不能同时推出ε):
            1、FIRST(α)∩FIRST(β)=Φ
            2、假若β=>*ε，那么FIRST(α)∩FOLLOW(A)＝Φ
        */

        //main过程为主入口，之前定义全局变量,之后定义过程
        "S -> program",   //文法增广
        "program -> vardefinition main ( ) { body } funcdefinition",

        //变量和过程的声明，声明时不可赋值
        "vardefinition -> vardef vardefinition",
        "funcdefinition -> funcdef funcdefinition",
        "vardefinition -> empty",
        "funcdefinition -> empty",

        //变量定义，支持数组，只有int一种类型
        "vardef -> type var ;",
        "type -> int",
        "var -> id varextra",
        "varextra -> , var",
        "varextra -> empty",
        "varextra -> [ num ] varextra",

        //过程定义,支持参数列表
        "funcdef -> id ( paramlist ) { body }",
        "paramlist -> type param",
        "paramlist -> empty",
        "param -> num paramextra",
        "param -> id paramextra",
        "paramextra -> empty",
        "paramextra -> , paramlist",

        //body
        "body -> vardefinition statlist",    //先定义 再语句列表
        "statlist -> empty",
        "statlist -> ifelsestat statlist",     //if-else语句
        "statlist -> forstat statlist",    //for循环语句
        "statlist -> whilestat statlist",      //while循环语句
        "statlist -> aorf statlist",     //提取左公因子的赋值或函数调用
        "aorf -> id assignorfunc",
        "assignorfunc -> funccall",
        "assignorfunc -> assignstat",

        //过程调用
        "funccall -> ( inparamlist ) ;",
        "inparamlist -> factor inparams",
        "inparamlist -> empty",
        "inparams -> , inparamlist",
        "inparams -> empty",
        //赋值语句
        "assignstat -> = expression ;",

        //表达式(四则运算, 乘除优先级大于加减)
        "expression -> exp exp1",
        "exp1 -> + exp exp1",
        "exp1 -> - exp exp1",
        "exp1 -> empty",
        "exp -> factor exp2",
        "exp2 -> * factor exp2",
        "exp2 -> / factor exp2",
        "exp2 -> empty",
        "factor -> ( expression )",
        "factor -> id",
        "factor -> num",

        //条件判断句
        "judgement -> factor relop factor",
        "relop -> !=",
        "relop -> >=",
        "relop -> <=",
        "relop -> ==",
        "relop -> <",
        "relop -> >",
        //if-else语句
        "ifelsestat -> if ( judgement ) { body } elsestat",
        "elsestat -> empty",
        "elsestat -> else { body }",
        //for循环语句
        "forstat -> for ( id assignstatfor ; judgement ; id assignstatfor ) { body }",
        "assignstatfor -> = expression",
        //while循环语句
        "whilestat -> while ( judgement ) { body }"
    };
    map<string, string> vttype = {
        { "<","cop" },
        { "<=","cop" },
        { ">","cop" },
        { ">=","cop" },
        { "==","cop" },
        { "!=","cop" },
        { "=","aop" },
        { "+","oop" },
        { "-","oop" },
        { "*","oop" },
        { "/","oop" },
        { ";","eop" },
        { ",","sop" },
        { "(","sop" },
        { ")","sop" },
        { "[","sop" },
        { "]","sop" },
        { "{","sop" },
        { "}","sop" },
        { "int","reserved" },
        { "if","reserved" },
        { "else","reserved" },
        { "for","reserved" },
        { "main","reserved" },
        { "while","reserved" },
        { "num","num" },
        { "id","id" },
        { "empty","empty" },
        { "#","#" }
    };

    string syntaxError;

    PAtable patable;
    vector<string> vn;			//非终结符集合
    vector<string> vt;			//终结符集合
    map<string, vector<string>> firstlist;		//first集
    map<string, vector<string>> followlist;		//follow集
    map<int, vector<string>> grammarmap;		//存储语法的产生式
    map<int, vector<string>>::iterator gmaper;//迭代器
    vector<string>::iterator iter;       //迭代器
    map<string, string>::iterator iter_map;      //迭代器
    map<string, vector<string>>::iterator maper;    //迭代器

    Stack stack;
    ParseTreeNode *treenode;
    int nodenum = 0;		//节点编号
    map<int, vector<string>> placelistmap;    //各节点存储字符串信息表

    void cal_vn_vt();//计算终结符集合以及非终结符集合
    int check_exist(vector<string> vec, string str);//判断集合中是否存在str元素
    void cal_first();//求first集
    void cal_follow();//求follow集
    void init_patable();//初始化预测分析表
    void cal_patable(); //计算预测分析表
    void fix(string &str);//去除字符串前后多余的空格
    void del(vector<string> &vec, string str);//删除vt集中应该为vn的元素

    void init_stack();
    void stack_pushin(string str);  //元素入栈
    void stack_popout();    //栈顶元素出栈
    string stack_gettop();  //获取栈顶元素
    string stack_show();    //显示栈中内容

    void init_tree();
    string make_tree(vector<Token> &tokenlist);   //通过词法分析得到的tokenlist构造语法树,并返回分析过程（栈的信息）
    string handle_error(vector<Token>::iterator tokeniter);  //返回对应的错误信息

    QString firstlistToString();
    QString followlistToString();
    QString patableToString();
    QString originToString();
    QString treeToString();
};


#endif // SYNTAXANALYSIS_H
