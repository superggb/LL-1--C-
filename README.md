# LL-1--C-
编译原理实验 LL(1)语法预测分析器
代码范例文法如下：
E->TR
R->+TR
R->$
T->FY
Y->*FY
Y->$
F->(E)
F->i
输入测试语句在main函数结尾str字符串中。