// �Ƚ������֧�֣� > <   >=   <=  ==
//�߼������֧�֣�&& ||
//������֧�֣���ֵ�ͻ����ַ���
//�������Ƶı��ʽ��TRUE����FALSE : ((3<2) || (1 > 0)) && ("abc" == "a"))
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
        //string��begin��ָ��һԪ�ص�ͷ��������end��ָ���һԪ�ص�β����
        //*begin�����壬*end�����塣
    protected:
    private:
        bool DelSpace(string strexpress);
        bool BasicUnit(string strexpress);
        bool ISlegal(string strexpress);
        bool MainUnit(string strexpress);
        bool ASSUnit(string strexpress);
};

#endif // EVAL_H
