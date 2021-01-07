# LL1 Compiler

目前顶多算个parser半成品。ui还能看。

lexcial analysis完成并且没有报错，再进行syntax analysis。
syntax analyzer用make_tree检查静态语法、生成注释分析树、填充符号表。但是没有设计SSD，所以没有语义分析。没有定义符号表，所以这部分也没有。就是生成普通的语法树也没有完成。

## 内置的文法概述：
1. 全局变量在main函数之前声明，自定义过程在main函数之后定义
2. 不可以在变量声明的同时赋值
3. 不支持嵌套过程的定义
4. 过程没有返回值
5. 支持if语句、while循环语句和for循环语句
6. 支持一维定长数组
7. 目前变量类型只有int

## 所有功能：

输入满足LL1规则的文法，程序可自动求first、follow集并生成预测分析表。

静态语法检查报错：只做了一点点（预测分析表中大于100的值）

生成语法树：和语法分析同步进行，没有写完，被注释掉了

符号表：打算在语法分析对象创建时新建，语法分析时填充，还没有定义，估计不会做了

语法制导翻译方案SDD：待设计，估计不会做了

我好菜，考试嘛考的稀烂(｡ ́︿ ̀｡)

也许某天会有哪个有缘人帮我写符号表和SDD吗(¬_¬)

啊，我在想peach。
