#include "lexcial_analysis.h"

LexcialAnalysis::LexcialAnalysis()
{
    lexcialError = new vector<QString>();
    tokenList = new vector<Token>();
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

int LexcialAnalysis::isReserved(QString strToken){
    int i;
    for (i = 0; i < 6; i++) {
        if (strToken.compare(key[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void LexcialAnalysis::analyze(QString src){


    QString strToken;
    QChar ch;
    int i;
    int line=1,pos=0;  //当前位置

    for(i=0;i<src.length();)
    {
        ch = src[i];

        if (ch==" ") { //遇到空白字符
            strToken = "";
            i++;pos++;
        }
        else if(ch=="\n"){ //遇到换行符
            line++;
            pos=0;
            i++;
        }
        else if (ch.isLetter()) { //遇到字母

            while (ch.isLetterOrNumber()) { //读取整个token 直到下一个空白字符
                strToken.push_back(ch);
                pos++;
                i++;
                ch = src[i];
            }

            if (isReserved(strToken)) { //判断token是否为保留字
                Token token = {strToken,"RESERVED",line,pos-strToken.length()};
                tokenList->push_back(token);
            }
            else {
                Token token = {strToken,"ID",line,pos-strToken.length()};
                tokenList->push_back(token);
            }

            strToken = "";
        }
        else if (ch.isDigit()) { //遇到数字
            while (ch.isDigit()) {	//读取整个数
                strToken.push_back(ch);
                pos++;
                i++;
                ch = src[i];
            }
            //数字之后出现字母 发现错误格式的ID 报错
            if (ch.isLetter()) {
                QString error = "[Lexical ERROR] ";
                error += "[";error += QString::number(line); error += ",";
                error += QString::number(pos-strToken.length());
                error += "]";error+=" ";
                error += "Invalid ID:";

                while (ch.isLetterOrNumber()) {
                    strToken.push_back(ch);
                    pos++;i++;
                    ch = src[i];
                }

                error += strToken;
                error += "\n";

                lexcialError->push_back(error);
            }
            else {
                Token token = {strToken,"NUM",line,pos-strToken.length()};
                tokenList->push_back(token);
            }

            strToken = "";
        }
        else {
            switch (ch.unicode()) //其他OP类字符
            {
                case '=':
            {
                i++;
                ch = src[i];
                if (ch == '=')
                {
                    Token token = {"==","COP",line,pos};
                    tokenList->push_back(token);
                    pos=pos+2;i++;
                }
                else {
                    Token token = {"=","AOP",line,pos};
                    tokenList->push_back(token);
                    pos++;
                }
                break;
            }
                case '<':
            {
                i++;
                ch = src[i];
                if (ch == '=') {
                    Token token = {"<=","COP",line,pos};
                    tokenList->push_back(token);
                    pos=pos+2;i++;
                }
                else {
                    Token token = {"<","COP",line,pos};
                    tokenList->push_back(token);
                    pos++;
                }
                break;
            }
                case '>':
            {
                i++;
                ch = src[i];
                if (ch == '=') {
                    Token token = {">=","COP",line,pos};
                    tokenList->push_back(token);
                    pos=pos+2;i++;
                }
                else {
                    Token token = {">","COP",line,pos};
                    tokenList->push_back(token);
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
                    Token token = {"!=","COP",line,pos};
                    tokenList->push_back(token);
                    pos=pos+2;i++;
                }
                else
                {
                    Token token = {"!","COP",line,pos};
                    tokenList->push_back(token);
                    pos++;
                }
                break;
            }
                case '+':
                case '-':
                case '/':
                case '*':
            {
                Token token = {ch,"OOP",line,pos};
                tokenList->push_back(token);
                i++;pos++;
                break;
            }
                case ';':
            {
                Token token = {ch,"EOP",line,pos};
                tokenList->push_back(token);
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
                Token token = {ch,"SOP",line,pos};
                tokenList->push_back(token);
                i++;pos++;
                break;
            }
                default:	//未识别成功的信息 显示出错信息
            {
                QString error = "[Lexical ERROR] ";
                error += "[";error += QString::number(line); error += ",";
                error += QString::number(pos);
                error += "]";
                error += "UNKNOW EXPRESSION: ";
                error += ch; error += " ";
                lexcialError->push_back(error);
                i++;pos++;
            }
            }
        }
    }
}
