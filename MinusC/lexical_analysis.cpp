#include "lexical_analysis.h"

LexicalAnalysis::LexicalAnalysis()
{

}

int LexicalAnalysis::isReserved(QString strToken){
    int i;
    for (i = 0; i < 6; i++) {
        if (strToken.compare(key[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void LexicalAnalysis::analyze(QString src,vector<Token> &tokenList,vector<QString> &lexicalError){


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
                tokenList.push_back(token);
            }
            else {
                Token token = {strToken,"ID",line,pos-strToken.length()};
                tokenList.push_back(token);
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

                lexicalError.push_back(error);
            }
            else {
                Token token = {strToken,"NUM",line,pos-strToken.length()};
                tokenList.push_back(token);
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
                    tokenList.push_back(token);
                    pos=pos+2;i++;
                }
                else {
                    Token token = {"=","AOP",line,pos};
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
                    Token token = {"<=","COP",line,pos};
                    tokenList.push_back(token);
                    pos=pos+2;i++;
                }
                else {
                    Token token = {"<","COP",line,pos};
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
                    Token token = {">=","COP",line,pos};
                    tokenList.push_back(token);
                    pos=pos+2;i++;
                }
                else {
                    Token token = {">","COP",line,pos};
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
                    Token token = {"!=","COP",line,pos};
                    tokenList.push_back(token);
                    pos=pos+2;i++;
                }
                else
                {
                    Token token = {"!","COP",line,pos};
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
                Token token = {ch,"OOP",line,pos};
                tokenList.push_back(token);
                i++;pos++;
                break;
            }
                case ';':
            {
                Token token = {ch,"EOP",line,pos};
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
                Token token = {ch,"SOP",line,pos};
                tokenList.push_back(token);
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
                lexicalError.push_back(error);
                i++;pos++;
            }
            }
        }
    }
}
