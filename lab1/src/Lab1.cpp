#include "Lab1.h"

Lab1::Lab1()
{
    //ctor
}

void Lab1::generate(int numRows) {
    int output[numRows][numRows+1];

    //检查不合理输入
    if(numRows<=0) {
        cout << "请输入大于0的整数" << endl;
        return ;
    }

    //初始化为0
    for (int i=0; i<numRows; i++) {
        for(int j=0; j<numRows+1; j++) {
            output[i][j] = 0;
        }
    }
    output[0][1] = 1;//第一行为1

    //计算赋值，第一列空出来以便计算
    for (int i=1; i<numRows; i++) {
        for(int j=1; j<i+2; j++) {
            output[i][j] = output[i-1][j-1]+output[i-1][j];//根据帕斯卡三角形规则计算
        }
    }

    //输出
    cout << "[" << endl;
    for (int i=0; i<numRows; i++) {
        cout << "[";
        for(int j=1; j<i+1; j++) {
            cout << output[i][j] << ",";
        }
        cout << output[i][i+1] << "]," << endl;//每一行的最后一个
    }
    cout << "]" << endl;
}
