#ifndef PREPROCESS_H
#define PREPROCESS_H

#include "include.h"

// 预处理，消去注释和无用的空格

//使用有限状态自动机来实现功能

class Preprocess
{
public:
    Preprocess();

    //删除程序中所有注释 FA定义
    //start--status:0
    //status:1	readin-ch
    //		'/'		goto-2	--
    //		'*'		goto-1	output-ch
    //		other	goto-1	output-ch
    //status:2	readin-ch
    //		'/'		goto-2	output-'/'
    //		'*'		goto-3	--
    //		other	goto-1	output-'/'and ch
    //status:3	readin-ch
    //		'/'		goto-3	--
    //		'*'		goto-4	--
    //		other	goto-3	--
    //status:4	readin-ch
    //		'/'		goto-5	--
    //		'*'		goto-4	--
    //		other	goto-3	--
    //status:5	readin-ch
    //		'/'		goto-2	--
    //		'*'		goto-1	output-ch
    //		other	goto-1	output-ch
    QString delComments(QString src);

    //删除空格、tab以及回车 FA定义
    //start--status:0
    //status:1	readin-ch
    //		/blank	goto-2	--
    //		other	goto-1	output-ch
    //status:2	readin-ch
    //		/blank	goto-2	--
    //		other	goto-1	output-pre and ch
    QString delBlanks(QString src);

};

#endif // PREPROCESS_H
