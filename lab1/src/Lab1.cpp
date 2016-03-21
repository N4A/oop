#include "Lab1.h"

Lab1::Lab1()
{
    //ctor
}

void Lab1::generate(int numRows) {
    int output[numRows][numRows+1];

    //��鲻��������
    if(numRows<=0) {
        cout << "���������0������" << endl;
        return ;
    }

    //��ʼ��Ϊ0
    for (int i=0; i<numRows; i++) {
        for(int j=0; j<numRows+1; j++) {
            output[i][j] = 0;
        }
    }
    output[0][1] = 1;//��һ��Ϊ1

    //���㸳ֵ����һ�пճ����Ա����
    for (int i=1; i<numRows; i++) {
        for(int j=1; j<i+2; j++) {
            output[i][j] = output[i-1][j-1]+output[i-1][j];//������˹�������ι������
        }
    }

    //���
    cout << "[" << endl;
    for (int i=0; i<numRows; i++) {
        cout << "[";
        for(int j=1; j<i+1; j++) {
            cout << output[i][j] << ",";
        }
        cout << output[i][i+1] << "]," << endl;//ÿһ�е����һ��
    }
    cout << "]" << endl;
}
