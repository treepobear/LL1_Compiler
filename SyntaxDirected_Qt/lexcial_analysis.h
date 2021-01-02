#ifndef LEXICALANALYSIS_H
#define LEXICALANALYSIS_H

#include "includes.h"

//token结构体
typedef struct Token
{
    QString lexeme;		//token实际词素
    QString type;		//token类型
    int line;			//token所在行
    int pos;            //token在行中的位置
}Token;

//保留字字符表
const QString key[6] = { "int","float","if","for","while","main" };

class LexcialAnalysis
{
public:
    vector<QString> *lexcialError;
    vector<Token> *tokenList;

    LexcialAnalysis();

    /* 删除多余的空白符
     * 遇见重复的空格、tab保留一个空格，遇见重复的换行符保留一个换行符
     * start--status:0
     * status:1	readin-ch
     *		 /blank	goto-2
     *		 other	goto-1
     * status:2	readin-ch
     *	 	 /blank	goto-2
     *	   	 other	goto-1
     */
    QString delBlanks(QString src);

    /* 删除程序中所有注释
     *startstatus:0
     *status:1	readin-ch
     *		'/'		goto-2
     *		'*'		goto-1
     *		other	goto-1
     *status:2	readin-ch
     *		'/'		goto-2
     *		'*'		goto-3
     *		other	goto-1
     *status:3	readin-ch
     *		'/'		goto-3
     *		'*'		goto-4
     *		other	goto-3
     *status:4	readin-ch
     *		'/'		goto-5
     *		'*'		goto-4
     *		other	goto-3
     *status:5	readin-ch
     *		'/'		goto-2
     *		'*'		goto-1
     *		other	goto-1
    */
    QString delComments(QString src);

    //判断是否为保留字 是返回1 否则返回0
    int isReserved(QString strToken);

    //分析
    void analyze(QString src);

};

#endif // LEXICALANALYSIS_H
