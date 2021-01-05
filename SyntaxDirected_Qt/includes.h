#ifndef INCLUDES_H
#define INCLUDES_H

#include <QMainWindow>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

typedef enum{
    BROWSE,
    EDIT,
}editorMode;

static const int maxsize = 255;
static const string firststr = "S";

//token结构体
typedef struct Token
{
    string lexeme;		//token实际词素
    string type;		//token类型
    int line;			//token所在行
    int pos;            //token在行中的位置
}Token;

//保留字字符表
const string key[6] = { "int","float","if","for","while","main"};

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
typedef struct PtreeNode
{
    char lexeme[255];		//结点元素实际词素（终结符是lexeme、非终结符就是非终结符）
    char type[255];		//结点元素类型	非终结符为derivation 终结符为自身类型 根节点为root
    int childnum;			//结点孩子节点个数
    int gnum;			//如为非终结符 记录产生编号
    int nodenum;
    struct PtreeNode * sons[255];		//孩子节点地址数组
    struct PtreeNode *brother;			//兄弟节点地址
    struct PtreeNode *father;			//父亲节点地址
    struct info *info;				//语义信息
}ParseTreeNode;

//栈结构体
typedef struct
{
    vector<string> st;		//栈
    int current;			//当前栈中元素个数
}Stack;


#endif // INCLUDES_H
