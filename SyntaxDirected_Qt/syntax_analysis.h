#ifndef SYNTAXANALYSIS_H
#define SYNTAXANALYSIS_H
#include "includes.h"

static const int maxsize = 255;
static const string firststr = "S";

//预测分析表结构体 prediction analysis table
typedef struct PAtable
{
    map<string, int>vnname;		//非终结符表
    map<string, int>vtname;		//终结符表
    int pat[maxsize][maxsize];		//预测分析表
    int vnnum;		//记录非终结符个数
    int vtnum;		//记录终结符个数
}PAtable;

//语义信息
typedef struct info
{
    int arrayflag;		//记录变量是否为数组
    int emptyflag;		//记录该非终结符是否推出空
    int whilenum1;		//记录while入口的三地址代码值
    int whilenum2;		//记录while出口的三地址代码值
    int ifnum1;			//记录if语句真出口三地址代码值
    int ifnum2;			//记录if语句假出口三地址代码值
    int elsenum1;		//记录else入口三地址代码值
    int elsenum2;		//记录else出口三地址代码值
    int returnflag;
}info;

//树结点结构体
typedef struct Ptree
{
    char lexeme[255];		//结点元素实际词素
    char type[255];		//结点元素类型	非终结符为derivation 终结符为自身类型 根节点为head
    int childnum;			//结点孩子节点个数
    int gnum;			//如为非终结符 记录产生编号
    int nodenum;
    struct Ptree * sons[255];		//孩子节点地址数组
    struct Ptree *brother;			//兄弟节点地址
    struct Ptree *father;			//父亲节点地址
    struct info *info;				//语义信息
}ParseTree;


class SyntaxAnalysis
{
public:
    SyntaxAnalysis();
    vector<string> origin = {
        //main过程为主入口，之前定义全局变量和过程
        "S -> program",   //文法增广
        "program -> definition main ( ) { body }",
        //变量和过程的定义
        "definition -> vardef definition",
        "definition -> funcdef definition",
        "definition -> empty",
        //变量定义，支持数组，只有int一种类型
        "vardef -> type var ;",
        "type -> int",
        "var -> id varextra",
        "varextra -> empty",
        "varextra -> [ num ]",
        //过程定义,支持参数列表
        "funcdef -> id ( paramlist ) { body }",
        "paramlist -> empty",
        "paramlist -> type id params",
        "params -> , type id params",
        "params -> empty",
        //body
        "body -> definition statlist",    //先定义 再语句列表
        "statlist -> assignstat statlist",     //赋值语句
        "statlist -> ifelsestat statlist",     //if-else语句
        "statlist -> forstat statlist",    //for循环语句
        "statlist -> whilestat statlist",      //while循环语句
        "statlist -> funccall statlist",       //调用过程
        "statlist -> empty",
        //过程调用
        "funccall -> id ( inparamlist ) ;",
        "inparamlist -> var inparams",
        "inparamlist -> num inparams",
        "inparamlist -> empty",
        "inparams -> , var inparams",
        "inparams -> , num inparams",
        "inparams -> empty",
        //赋值语句
        "assignstat -> var = expression ;",
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
        "factor -> var",
        "factor -> num",
        //条件判断句
        "judgement -> var relop var",
        "judgement -> var relop num",
        "judgement -> num relop var",
        "judgement -> num relop num",
        "relop -> !=",
        "relop -> >=",
        "relop -> <=",
        "relop -> ==",
        "relop -> <",
        "relop -> >",
        //if-else语句（嵌套使用时的二义性待解决）
        "ifelsestat -> if ( judgement ) { body } elsestat",
        "elsestat -> empty",
        "elsestat -> else { body }",
        //for循环语句
        "forstat -> for ( var = num ; judgement ; assignstat ) { body }",
        //while循环语句
        "whilestat -> while ( judgement ) { body }"
    };
    map<string, string> vttype = {
        { "<","COP" },
        { "<=","COP" },
        { ">","COP" },
        { ">=","COP" },
        { "==","COP" },
        { "!=","COP" },
        { "=","AOP" },
        { "+","OOP" },
        { "-","OOP" },
        { "*","OOP" },
        { "/","OOP" },
        { ";","EOP" },
        { ",","SOP" },
        { "(","SOP" },
        { ")","SOP" },
        { "[","SOP" },
        { "]","SOP" },
        { "{","SOP" },
        { "}","SOP" },
        { "int","REVERSED" },
        { "if","REVERSED" },
        { "else","REVERSED" },
        { "for","REVERSED" },
        { "main","REVERSED" },
        { "while","REVERSED" },
        { "num","NUM" },
        { "id","ID" },
        { "empty","empty" },
        { "#","#" }
    };

    PAtable patable;
    vector<string> vn;			//非终结符集合
    vector<string> vt;			//终结符集合
    map<string, vector<string>> firstlist;		//first集
    map<string, vector<string>> followlist;		//follow集
    map<int, vector<string>> grammarmap;		//存储语法的推导
    map<string, int> emptymake;			//存储所有非终结符能推导出空字的推导式编号
    map<int, vector<string>>::iterator gmaper;//迭代器
    vector<string>::iterator iter;       //迭代器
    map<string, string>::iterator iter_map;      //迭代器
    map<string, vector<string>>::iterator maper;    //迭代器

    void cal_vn_vt();//计算终结符集合以及非终结符集合
    int check_exist(vector<string> vec, string str);//判断集合中是否存在str元素
    void cal_first();//求first集
    void cal_follow();//求follow集
    void init_patable();//初始化预测分析表
    void cal_patable(); //计算预测分析表
    void fix(string &str);//去除字符串前后多余的空格
    void del(vector<string> &vec, string str);//删除vt集中应该为vn的元素

    QString firstlistToString();
    QString followlistToString();
    QString patableToString();
    QString originToString();

};


#endif // SYNTAXANALYSIS_H
