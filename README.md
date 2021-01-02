# LL1 Compiler

一个语法制导编译器前端

## 编译器前端
是指从源程序到中间代码这一部分
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201229141510512.JPG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L09uZWlyb19xaW55dWU=,size_16,color_FFFFFF,t_70)

之后开始涉及适应硬件的部分。当然，要做IDE的话还要涉及运行时环境。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201229141813551.JPG)
本科课程设计主要是前端。



## 词法分析
在项目中是lexcial_analysis中的内容。（对关键词的识别没有采用自动机的形式。）
### 预处理部分：
用状态机消去多行注释，并且在遇见很多空格、tab以及换行符的地方只保留一个空格或者换行。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210101144919293.JPG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L09uZWlyb19xaW55dWU=,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210101145141402.JPG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L09uZWlyb19xaW55dWU=,size_16,color_FFFFFF,t_70)

### tokenizer：
从源文件到词法单元(token)。

产生1.词法报错信息（汇报出错位置在第几行第几列）；2.分好类的token（放在vector中）

## 文法设计

输入LL1文法和终结符集，自动计算first集、follow集以及预测分析表。

## 注释分析树

