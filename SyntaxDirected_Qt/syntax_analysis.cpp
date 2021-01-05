#include "syntax_analysis.h"

SyntaxAnalysis::SyntaxAnalysis()
{
    //构造分析器（计算预测分析表）
    cal_vn_vt();
    cal_first();
    cal_follow();
    cal_patable();
    //初始化语法分析树以及语法栈
    init_stack();
    init_tree();
}

void SyntaxAnalysis::fix(string &str){
    if (str[0] == ' ')
        str.assign(str, 1, str.length() - 1);		//首字符为空格
    if (str[str.length() - 1] == ' ')
        str.assign(str, 0, str.length() - 1);		//末字符为空格
}

void SyntaxAnalysis::del(vector<string> &vec, string str)
{
    iter = find(vec.begin(), vec.end(), str);
    vec.erase(iter);
}

void SyntaxAnalysis::cal_vn_vt(){
    string temp,part1,part2,t;
    size_t split, start, index, num = 1;
    for (size_t i=0;i<origin.size();i++)
    {
        temp = origin[i];
        split = temp.find("->");
        part1.assign(temp, 0, split);
        part2.assign(temp, split + 2, temp.length() - split - 1);
        fix(part1);
        fix(part2);			//将每一行语法分为箭头前后的两个部分
        start = 0;
        grammarmap.insert({ num,{part1} });
        //左侧部分 如果vn集合中还没有出现则加入 如果vt集合中出现则将vt集合中的该元素删除
        if (!check_exist(vn, part1))
            vn.push_back(part1);
        if (check_exist(vt, part1))
            del(vt, part1);
        while (1)		//将箭头后的部分按照空格分开
        {
            index = part2.find(' ',start);
            if (index == part2.npos)
                break;
            t.assign(part2, start, index - start);
            start = index + 1;
            //当右侧部分在 vn中没有出现且vt中没有出现 则将该元素加入vt集合中
            if (!check_exist(vn, t) && !check_exist(vt, t))
                vt.push_back(t);
            grammarmap[num].push_back(t);
        }
        t.assign(part2, start, part2.length() - start);
        if (!check_exist(vn, t) && !check_exist(vt, t))
            vt.push_back(t);
        //填充可以推导出空的非终结符表
        grammarmap[num].push_back(t);
        num++;
    }
    vt.push_back("#");
}

int SyntaxAnalysis::check_exist(vector<string> vec, string str){
    vector<string>::iterator iter;
    iter = find(vec.begin(), vec.end(), str);
    if (iter != vec.end())
        return 1;
    else
        return 0;
}

void SyntaxAnalysis::cal_first(){
    int flag, outflag;
    unsigned int k;
    string vnname, tname, temp;
    while (1)
    {
        flag = 1;
        for (gmaper = grammarmap.begin();gmaper != grammarmap.end();gmaper++)
        {
            vnname = gmaper->second[0];
            if (check_exist(vt, gmaper->second[1]))
            {
                if (!check_exist(firstlist[vnname], gmaper->second[1]))
                {
                    firstlist[vnname].push_back(gmaper->second[1]);
                    flag = 0;
                }	//判断该终结符是否已经在该推导的first集中,没有则添加
            }		//产生式第一个元素为终结符
            else
            {
                k = 1;
                outflag = 1;
                while (1)
                {
                    if (k >= gmaper->second.size())
                        break;
                    //cout << k << " " << gmaper->second.size() << endl;
                    tname = gmaper->second[k];
                    if (check_exist(vn, tname))
                    {
                        //逐个检验是否已经在vnname的first集中,不存在就添加
                        for (iter = firstlist[tname].begin();iter != firstlist[tname].end();iter++)
                        {
                            temp = *iter;
                            if (!check_exist(firstlist[vnname], temp))
                            {
                                firstlist[vnname].push_back(temp);
                                flag = 0;
                            }
                            if (*iter == "empty")	//如果该非终结符的first集中没有empty则进入下一推导式
                                outflag = 0;
                        }
                    }
                    else
                    {		//推导式中出现终结符 判断是否添加后 进入下一个推导式
                        outflag = 1;
                        if (!check_exist(firstlist[vnname], tname))
                        {
                            firstlist[vnname].push_back(tname);
                            flag = 0;
                        }
                    }
                    if (outflag)
                        break;
                    k++;
                }
            }
        }
        //当flag为1时表示已经没有first集发生添加元素 fisrt集合求解完成
        if (flag)
            break;
    }

    //把终结符也加入first集
    for(iter = vt.begin();iter != vt.end();iter++){
        firstlist[*iter].push_back(*iter);
    }
}

void SyntaxAnalysis::cal_follow(){
    //将结束符放入follow(S)
    followlist["S"].push_back("#");

    string vnname, vtname;

    int flag; //是否还有新的终结符可以被加入到任何follow集
    int outflag; //记录一个非终结符是否可以推导出空
    int exflag;
    vector<string>::iterator titer, temp;//titer是当前遍历到的符号后面的一个符号
    while (1)
        {
            flag = 1;
            for (gmaper = grammarmap.begin();gmaper != grammarmap.end();gmaper++)		//遍历推导式
            {
                for (iter = gmaper->second.begin() + 1;iter != gmaper->second.end();iter=titer)		//遍历推导式中个符号
                {
                    titer = iter + 1;

                    //遇到终结符 不需要计算follow集
                    if (check_exist(vt, *iter))
                        continue;
                    else    //遇到一个非终结符开始向后遍历 直到遇到不能推导空的非终结符或是终结符
                    {
                        vnname = *iter;
                        while (1)
                        {
                            iter++;
                            outflag = 1;		//记录一个非终结符能不能推导出空
                            if (iter == gmaper->second.end())		//到推导式结束 当前非终结符follow集操作完成
                                break;
                            if (check_exist(vt, *iter))
                            {
                                if (!check_exist(followlist[vnname], *iter) && *iter != "empty")
                                {
                                    followlist[vnname].push_back(*iter);
                                    flag = 0;
                                }
                            }		//遇到一个终结符 判断是否存在 不存在则加入当前非终结符的follow集中
                            else
                            {
                                for (temp = firstlist[*iter].begin();temp != firstlist[*iter].end();temp++)
                                {
                                    if (!check_exist(followlist[vnname], *temp) && *temp != "empty")
                                    {
                                        followlist[vnname].push_back(*temp);
                                        flag = 0;
                                    }
                                    if (*temp == "empty")
                                        outflag = 0;
                                }		//将当前符号后遇到的所有的first集合判断并加入到follow集中 直到遇到不能推导出空的非终结符
                            }
                            if (outflag)
                                break;
                        }
                    }
                }
                unsigned int i = 1;
                //推导式最后连续i个非终结符可以推导为空 则推导式最前的非终结符的follow集中所有元素判断并添加到这所有的非终结符的follow集中
                while (1)
                {
                    if (check_exist(vn, *(gmaper->second.end() - i)))
                    {
                        string str;
                        if (i >= gmaper->second.size())
                            break;
                        str = *(gmaper->second.end() - i);
                        vnname = gmaper->second[0];
                        for (temp = followlist[vnname].begin();temp != followlist[vnname].end();temp++)
                        {
                            if (!check_exist(followlist[str], *temp) && *temp != "empty")
                            {
                                followlist[str].push_back(*temp);
                                flag = 0;
                            }
                        }
                        exflag = 0;
                        for (iter = firstlist[str].begin();iter != firstlist[str].end();iter++)
                            if (*iter == "empty")
                                exflag = 1;
                        //exflag记录该非终结符的first集中是否有empty
                        if (!exflag)
                            break;
                        else
                            i++;
                    }
                    else
                        break;
                }
            }
            if (flag)
                break;
        }
}

void SyntaxAnalysis::init_patable()
{
    int i, j, vnnum, vtnum;
    for (iter = vn.begin(), vnnum = 1;iter != vn.end();iter++, vnnum++)
        patable.vnname.insert({ *iter,vnnum });
    //预测分析表中的终结符部分需要去除empty 产生空字的列
    for (iter = vt.begin(), vtnum = 1;iter != vt.end();iter++, vtnum++)
        if (*iter != "empty")
            patable.vtname.insert({ *iter,vtnum });
        else
            vtnum--;
    //初始化全赋值为0 推导式编号由1开始
    for (i = 1;i < vnnum;i++)
        for (j = 1;j < vtnum;j++)
            patable.pat[i][j] = 0;
    patable.vnnum = vnnum - 1;
    patable.vtnum = vtnum - 1;
}

void SyntaxAnalysis::cal_patable(){
    string right, left;
    int emptyflag,emptyflaglattar;
    size_t rightnum;   //产生式右侧第几个符号
    init_patable();

    for (gmaper = grammarmap.begin();gmaper != grammarmap.end();gmaper++)
    {
        rightnum=1;
        right = gmaper->second[rightnum];		//当前推导式箭头右侧第一个符号
        left = gmaper->second[0];		//当前推导式箭头左侧的非终结符
        emptyflag = 0;  //first集中是否有empty
        for (iter = firstlist[right].begin();iter != firstlist[right].end();iter++)
        {
            if (*iter == "empty")
            {
                emptyflag = 1;
                continue;
            }
            //将name的所有first集所对应的位置填入当前推导式的编号
            patable.pat[patable.vnname[left]][patable.vtname[*iter]] = gmaper->first;
        }

        //如果first集中有empty，把后一个元素的first集加入可选集，一直重复；
        //如果含empty的是当前推导式右侧最后一个元素，把left的follow集也加进去
        while (emptyflag)
        {
            emptyflaglattar = 0;
            rightnum++;
            if(rightnum == gmaper->second.size()){
                for(iter = followlist[left].begin();iter != followlist[left].end();iter++){
                    patable.pat[patable.vnname[left]][patable.vtname[*iter]] = gmaper->first;
                }
                break;
            }
            right = gmaper->second[rightnum];
            for (iter = firstlist[right].begin();iter != firstlist[right].end();iter++)
            {
                if (*iter == "empty"){
                    emptyflaglattar = 1;
                    continue;
                }
                patable.pat[patable.vnname[left]][patable.vtname[*iter]] = gmaper->first;
                if(!emptyflaglattar && rightnum != gmaper->second.size()-1){
                    emptyflag = 0;
                }
                if(rightnum == gmaper->second.size()-1 && *iter =="empty"){
                    for(iter = followlist[left].begin();iter != followlist[left].end();iter++){
                        patable.pat[patable.vnname[left]][patable.vtname[*iter]] = gmaper->first;
                    }
                }
            }
        }
    }

}

void SyntaxAnalysis::init_stack(){
    stack.st.push_back("#");
    stack.st.push_back(firststr);
    stack.current = stack.st.size();
}

void SyntaxAnalysis::stack_pushin(string str){
    stack.st.push_back(str);
    stack.current++;
}

void SyntaxAnalysis::stack_popout(){
    string str;
    if (stack.st.size() == 0)
    {
        cout << "ERROR: stack is empty!" << endl;
        exit(0);
    }
    else
    {
        stack.st.pop_back();
        stack.current--;
    }
}

string SyntaxAnalysis::stack_gettop(){
    return stack.st[stack.current - 1];
}

string SyntaxAnalysis::stack_show(){
    stringstream out;
    int i;
    for (i = 0;i < stack.current;i++)
        out << "  " << stack.st[i];
    out << endl;
    return out.str();
}

void SyntaxAnalysis::init_tree(){
    //使用推导式 firststr-># firststr #   初始化根节点的孩子节点
    treenode = (ParseTreeNode*)malloc(sizeof(ParseTreeNode));
    strcpy(treenode->lexeme, "root");
    strcpy(treenode->type, "derivation");
    treenode->childnum = 3;
    treenode->father = NULL;
    treenode->brother = NULL;		//初始化根节点
    for (int i = 1;i <= treenode->childnum;i++)
    {
        treenode->sons[i] = (struct PtreeNode*)malloc(sizeof(struct PtreeNode));
        treenode->sons[i]->father = (struct PtreeNode *)malloc(sizeof(struct PtreeNode));
        treenode->sons[i]->brother = (struct PtreeNode *)malloc(sizeof(struct PtreeNode));
    }
    strcpy(treenode->sons[1]->lexeme, "#");
    strcpy(treenode->sons[1]->type, "#");
    treenode->sons[1]->brother = treenode->sons[2];
    treenode->sons[1]->father = treenode;
    nodenum++;
    treenode->sons[2]->nodenum = nodenum;
    placelistmap.insert({ nodenum,{} });
    strcpy(treenode->sons[2]->lexeme, firststr.c_str());
    strcpy(treenode->sons[2]->type, "derivation");
    treenode->sons[2]->brother = treenode->sons[3];
    treenode->sons[2]->father = treenode;
    strcpy(treenode->sons[3]->lexeme, "#");
    strcpy(treenode->sons[3]->type, "#");
    treenode->sons[3]->brother = NULL;
    treenode->sons[3]->father = treenode;
}

string SyntaxAnalysis::handle_error(vector<Token>::iterator tokeniter){
    stringstream error;
    error<<"[SYNTAX ERROR] [" << (*tokeniter).line << "," << (*tokeniter).pos<<"]"
         <<" unknown syntax error"<< endl;

    return error.str();
}

string SyntaxAnalysis::make_tree(vector<Token> &tokenlist){
    string stackinfo;

    stringstream succeed;
    string top = stack_gettop();
    struct PtreeNode *cur = treenode->sons[2];

    int num;    //预测分析表中，遇到的token对应的列号
    int gid;    //预测分析表中存储的产生式的编号

    for(vector<Token>::iterator tokeniter = tokenlist.begin();tokeniter != tokenlist.end();)
    {
        stackinfo += stack_show();

        if((*tokeniter).type == "id" || (*tokeniter).type == "num"){
            num = patable.vtname[(*tokeniter).type];
        }else{
            num = patable.vtname[(*tokeniter).lexeme];
        }

        //如果预测分析表中对应位置产生式为0，报错
        if (patable.pat[patable.vnname[top]][num] == 0)
        {
            syntaxError = handle_error(tokeniter);
            return stackinfo;
        }
        else    //预测分析表中对应位置存在产生式
        {
            gid = patable.pat[patable.vnname[top]][num];

            stack_popout();

            cur->childnum = 0;
            cur->gnum = gid;

            //将不为empty的产生式 压入栈中
            for (iter = grammarmap[gid].end() - 1;iter != grammarmap[gid].begin();iter--)
            {
                if (*iter != "empty")
                {
                    stack_pushin(*iter);
                }
            }


            //将该条产生式的所有元素 加入到当前节点的孩子节点 并填充相关信息以及兄弟父亲节点
            for (iter = grammarmap[gid].begin() + 1;iter != grammarmap[gid].end();iter++)
            {
                cur->childnum++;
                cur->sons[cur->childnum] = (ParseTreeNode *)malloc(sizeof(ParseTreeNode));

                if (cur->childnum > 1)
                    cur->sons[cur->childnum - 1]->brother = cur->sons[cur->childnum];

                cur->sons[cur->childnum]->father = cur;
                strcpy(cur->sons[cur->childnum]->lexeme, (*iter).c_str());

                if (patable.vnname.find(*iter) != patable.vnname.end())
                    strcpy(cur->sons[cur->childnum]->type, "derivation");
                else
                    strcpy(cur->sons[cur->childnum]->type, vttype.find(*iter)->second.c_str());

                cur->sons[cur->childnum]->info = (struct info *)malloc(sizeof(struct info));
                nodenum++;
                cur->sons[cur->childnum]->nodenum = nodenum;
            }

        }
        top = stack_gettop();
        char temp[5];
        strcpy(temp,cur->sons[1]->lexeme);
        if(strcmp(empty,temp)&&cur->brother){
            cur=cur->brother;
        }else{
            cur = cur->sons[1];
        }

        //如果当前栈顶是终结符并且是token的内容，则接受成功，tokeniter++,并改变cur当前节点
        while(patable.vtname.find(top) != patable.vtname.end()){
            if(top == "#"){
                succeed<<"[NO SYNTAX ERROR] ACCEPT SUCCEEDED" << endl;
                syntaxError = succeed.str();
                stackinfo += stack_show();
                return stackinfo;
            }
            if(top == (*tokeniter).lexeme || top == (*tokeniter).type){
                tokeniter++;
                if(cur->brother) cur = cur->brother;
                stack_popout();
                top = stack_gettop();
            }else{
                syntaxError = handle_error(tokeniter);
                return stackinfo;
            }
        }
    }

    if(syntaxError == ""){
        succeed<<"[NO SYNTAX ERROR] ACCEPT SUCCEEDED" << endl;
        syntaxError = succeed.str();
        if(stack_gettop()=="funcdefinition"){
            stack_popout();
            stackinfo += stack_show();
        }
        return stackinfo;
    }

    return stackinfo;
}

QString SyntaxAnalysis::firstlistToString(){
    //输出first集
    stringstream out;
    for (maper = firstlist.begin();maper != firstlist.end();maper++)
    {
        if (!check_exist(vt, maper->first))
        {
            out << maper->first << "的first集:    ";
            for (iter = maper->second.begin();iter != maper->second.end();iter++)
                out << *iter << "   ";
            out << endl;
        }
    }
    QString result = QString::fromStdString(out.str());
    return result;
}

QString SyntaxAnalysis::followlistToString(){
    //输出follow集
    stringstream out;
    for (maper = followlist.begin();maper != followlist.end();maper++)
    {
        if (!check_exist(vt, maper->first))
        {
            out << maper->first << "的follow集:   ";
            for (iter = maper->second.begin();iter != maper->second.end();iter++)
                out << *iter << "   ";
            out << endl;
        }
    }
    QString result = QString::fromStdString(out.str());
    return result;
}

QString SyntaxAnalysis::patableToString(){
    stringstream ss;
    vector<string>::iterator iter;

    ss << setw(10) << "";
    for (iter = vt.begin();iter != vt.end();iter++)
        if (*iter != "empty")
            ss <<"\t"<< left<<setw(5) << *iter;
    ss << endl;
    int i,j;
    for (iter = vn.begin(), i = 1;iter != vn.end();iter++, i++)
    {
        ss << setw(10) << left << *iter;
        for (j = 1;j <= patable.vtnum;j++)
            ss <<"\t"<< left <<setw(5)<< patable.pat[i][j];
        ss << endl;
    }

    QString out = QString::fromStdString(ss.str());
    return out;
}

QString SyntaxAnalysis::originToString(){
    stringstream ss;
    vector<string>::iterator iter;
    int i=1;

    for(iter = origin.begin();iter != origin.end();iter++){
        ss<<i<<" "<<*iter<<endl;
        i++;
    }
    QString out = QString::fromStdString(ss.str());
    return out;
}

QString SyntaxAnalysis::treeToString(){
    stringstream ss;

    return QString::fromStdString(ss.str());
}
