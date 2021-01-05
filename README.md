# LL1 Parser

内置的文法定义：
1. 全局变量在main函数之前声明，自定义过程在main函数之后定义
2. 不可以在变量声明的同时赋值
3. 不支持嵌套过程的定义
4. 过程没有返回值
5. 支持if语句、while循环语句和for循环语句
6. 支持一维定长数组
7. 目前变量类型只有int

输入满足LL1规则的文法，程序可自动求first、follow集并生成预测分析表。

parser错误处理：待做

生成语法树：待做

语法制导翻译方案SDD：待设计
