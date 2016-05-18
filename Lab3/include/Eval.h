// 比较运算符支持： > <   >=   <=  ==
//逻辑运算符支持：&& ||
//运算数支持：数值型还有字符串
//计算类似的表达式是TRUE还是FALSE : ((3<2) || (1 > 0)) && ("abc" == "a"))
//
#ifndef EVAL_H
#define EVAL_H
#include <string>
#include <iostream>

using namespace std;

class Eval
{
    public:
        Eval();
        virtual ~Eval();
        bool Func(string strexpress);
        //
        //string的begin是指第一元素的头部，但是end是指最后一元素的尾部。
        //*begin有意义，*end无意义。
    protected:
    private:
        bool DelSpace(string strexpress);
        bool BasicUnit(string strexpress);
        bool ISlegal(string strexpress);
        bool MainUnit(string strexpress);
        bool ASSUnit(string strexpress);
};

#endif // EVAL_H
