#ifndef LEXICALANALYSIS_H
#define LEXICALANALYSIS_H
#include "include.h"

//类别代码	单词符号symbol	类型type	    |类别代码 	单词符号symbol	类型type
//0			#				end		    |14			<=				operator
//1			int             keyword	    |15			>=				operator
//2			float			keyword     |16			==				operator
//3			if				keyword     |17			!=				operator
//4			for             keyword     |18			(				operator
//5			while			keyword     |19			)				operator
//6			main			keyword     |20			[				array
//7			+				operator    |21			]				array
//8			-				operator    |22			;				line_end
//9			*				operator    |23			,				dot
//10		/				operator    |24			{				struct
//11		<				operator    |25			}				struct
//12		>				operator    |26			letter|letter*	id
//13		=				operator    |27			digit|digit*	num

//COP 比较操作符:		<	<=	>	>=	==	!=
//AOP 赋值操作符:		=
//OOP 运算操作符:		+	-	*	/
//EOP 句末操作符:		;
//SOP 结构分隔符:		(	)	,	[	]	{	}
//RESERVED 保留字:	int float if for while main


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

class LexicalAnalysis
{
public:

    LexicalAnalysis();

    //判断是否为保留字 是返回1 否则返回0
    int isReserved(QString strToken);
    //分析
    void analyze(QString src,vector<Token> &tokenList,vector<QString> &lexicalError);

};

#endif // LEXICALANALYSIS_H
