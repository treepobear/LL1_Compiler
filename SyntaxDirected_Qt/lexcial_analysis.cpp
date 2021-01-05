#include "lexcial_analysis.h"

LexcialAnalysis::LexcialAnalysis()
{

}

QString LexcialAnalysis::delBlanks(QString src){
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
                {
                    if (temp == ' '||temp == '\t'){
                        status = 2;
                        pre = ' ';
                    }
                    else
                    {
                        result += temp;
                    }
                    break;
                }
                case 2:
                    if (temp != ' ' && temp != '\t')
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

QString LexcialAnalysis::delComments(QString src){
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

int LexcialAnalysis::isReserved(string strToken){
    int i;
    for (i = 0; i < 6; i++) {
        if (strToken.compare(key[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void LexcialAnalysis::analyze(QString qsrc){

    tokenList.clear();
    string src = qsrc.toStdString();

    string strToken;
    char ch;
    size_t i;
    int line=1,pos=0;  //当前位置

    for(i=0;i<src.length();)
    {
        ch = src[i];

        if (ch==' ') { //遇到空白字符
            strToken = "";
            i++;pos++;
        }
        else if(ch=='\n'){ //遇到换行符
            line++;
            pos=0;
            i++;
        }
        else if (isalpha(ch)) { //遇到字母

            while (isalpha(ch) || isdigit(ch)) { //读取整个token 直到下一个空白字符
                strToken.push_back(ch);
                pos++;
                i++;
                ch = src[i];
            }

            if (isReserved(strToken)) { //判断token是否为保留字
                Token token = {strToken,"reserved",line,pos-(int)strToken.length()};
                tokenList.push_back(token);
            }
            else {
                Token token = {strToken,"id",line,pos-(int)strToken.length()};
                tokenList.push_back(token);
            }

            strToken = "";
        }
        else if (isdigit(ch)) { //遇到数字
            while (isdigit(ch)) {	//读取整个数
                strToken.push_back(ch);
                pos++;
                i++;
                ch = src[i];
            }
            //数字之后出现字母 发现错误格式的ID 报错
            if (isalpha(ch)) {
                stringstream error;
                error<< "[LEXCIAL ERROR] "
                    << "["<< line<<","<<pos-strToken.length()<<"]"<<" "
                    <<"INVALID ID:";

                while (isdigit(ch) || isalpha(ch)) {
                    strToken.push_back(ch);
                    pos++;i++;
                    ch = src[i];
                }

                error << strToken;
                error << endl;

                lexcialError.push_back(error.str());
            }
            else {
                Token token = {strToken,"num",line,pos-(int)strToken.length()};
                tokenList.push_back(token);
            }

            strToken = "";
        }
        else {
            switch (ch) //其他OP类字符
            {
                case '=':
            {
                i++;
                ch = src[i];
                if (ch == '=')
                {
                    Token token = {"==","cop",line,pos};
                    tokenList.push_back(token);
                    pos=pos+2;i++;
                }
                else {
                    Token token = {"=","aop",line,pos};
                    tokenList.push_back(token);
                    pos++;
                }
                break;
            }
                case '<':
            {
                i++;
                ch = src[i];
                if (ch == '=') {
                    Token token = {"<=","cop",line,pos};
                    tokenList.push_back(token);
                    pos=pos+2;i++;
                }
                else {
                    Token token = {"<","cop",line,pos};
                    tokenList.push_back(token);
                    pos++;
                }
                break;
            }
                case '>':
            {
                i++;
                ch = src[i];
                if (ch == '=') {
                    Token token = {">=","cop",line,pos};
                    tokenList.push_back(token);
                    pos=pos+2;i++;
                }
                else {
                    Token token = {">","cop",line,pos};
                    tokenList.push_back(token);
                    pos++;
                }
                break;
            }
                case '!':
            {
                i++;
                ch = src[i];
                if (ch == '=') {
                    pos++;
                    Token token = {"!=","cop",line,pos};
                    tokenList.push_back(token);
                    pos=pos+2;i++;
                }
                else
                {
                    Token token = {"!","cop",line,pos};
                    tokenList.push_back(token);
                    pos++;
                }
                break;
            }
                case '+':
                case '-':
                case '/':
                case '*':
            {
                Token token = {string(1,ch),"oop",line,pos};
                tokenList.push_back(token);
                i++;pos++;
                break;
            }
                case ';':
            {
                Token token = {string(1,ch),"eop",line,pos};
                tokenList.push_back(token);
                i++;pos++;
                break;
            }
                case '(':
                case ')':
                case ',':
                case '[':
                case ']':
                case '{':
                case '}':
            {
                Token token = {string(1,ch),"sop",line,pos};
                tokenList.push_back(token);
                i++;pos++;
                break;
            }
                default:	//未识别成功的信息 显示出错信息
            {
                stringstream error;
                error<<"[LEXCIAL ERROR] "
                    <<"["<<line<< ","<<pos<<"]"
                    <<"UNKNOW EXPRESSION: "<<ch<<" ";
                lexcialError.push_back(error.str());
                i++;pos++;
            }
            }
        }
    }
}
