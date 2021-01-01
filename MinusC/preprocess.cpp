#include "preprocess.h"

Preprocess::Preprocess()
{

}

//状态转换表见preprocess.h
QString Preprocess::delComments(QString src){
    QString result = "";
    int status = 0;
    QChar temp,pre;
    QString temp_s="";		//存储可能为注释的字符串

    for(int i=0;i<src.length();i++){

        if (!status) status = 1;
        temp = src[i];

        switch (status)
        {
            case 1:
                if (temp != '/')
                {
                    result += temp;
                    status = 1;
                }
                else
                    status = 2;
                pre = temp;
                break;
            case 2:
                if (temp == '/')
                {
                    result += temp;
                    status = 2;
                }
                else
                    if (temp != '*')
                    {
                        result += temp;
                        status = 1;
                    }
                    else
                        status = 3;
                pre = temp;
                break;
            case 3:
                if (temp == '*')
                    status = 4;
                else
                    status = 3;
                temp_s.push_back(temp);
                if (pre == '/' && temp == '*')
                {
                    cout << "出现注释嵌套！" << endl;
                    cout << "[Error Occured!]";
                    exit(0);
                }
                pre = temp;
                break;
            case 4:
                if (temp == '/')
                    status = 5;
                else
                    if (temp == '*')
                        status = 4;
                    else
                        status = 3;
                temp_s.push_back(temp);
                pre = temp;
                break;
            case 5:
                temp_s = "";		//一段注释结束 清空暂存的可能为的注释信息
                if (temp != '/')
                {
                    result += temp;
                    status = 1;
                }
                else
                    status = 2;
                pre = temp;
                break;
            default:
                cout << "An error occured!" << endl;
                break;					//进入default分支 说明发生比较神奇的错误
        };

        //如果最后注释格式右侧没有闭合 则将正在判别的部分输出
        if (status == 2)
        {
//            cout << "/"<<endl;		//cout << "/";
        }
        if (status == 3 || status == 4)
        {
//            cout << "/*" << temp_s.toStdString().data()<<endl;	//cout << "/*" << temp_s;
        }
    }

    return result;
}

//状态转换表见preprocess.h
QString Preprocess::delBlanks(QString src){
    QString result = "";
    int status = 0;
    QChar temp,pre;

    for(int i=0;i<src.length();i++)
        {
            temp = src[i];

            if (!status) status = 1;
            switch (status)
            {
                case 1:
                    if (temp == ' ' || temp == '\n' || temp == '\t')
                        status = 2;
                    else
                    {
                        result += temp;
                    }
                    pre = temp;
                    break;
                case 2:
                    if (temp != ' ' && temp != '\n' && temp != '\t')
                    {
                        status = 1;
                        result += pre;
                        result += temp;
                        pre = temp;
                    }
                    break;
                default:
                    cout << "An error occured!" << endl;
                    break;						//进入default分支 说明发生比较神奇的错误
            };
        }

    return result;

}
