#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include "functions.h"

int seedOffset = 0; // 通过此变量自增+时间，随时提供新的种子，防止程序过快导致时间种子不变
extern float ComplainScore; // 不满指数

int main()
{
    Init_allPlayers(); // 初始化玩家获奖状态
    ExperimentStatus(); // 输出当前实验模拟数据
    printf("\n");

    #if REPEAT_MODE
    for(int i = 0; i < ExperimentTimes; i ++)
    {
        srand((unsigned)time(NULL) + seedOffset++); // 随机种子
        doExperiment();
        ComplainScore = 0.0; // 清空累计的不满指数
        Init_allPlayers(); // 初始化玩家获奖状态
    }
    #endif

    #if !REPEAT_MODE
    srand((unsigned)time(NULL) + seedOffset++); // 随机种子
    doExperiment();
    logOutput();
    printf("your complain score:%f\n", ComplainScore);
    #endif 
    // getchar();
    return 0;
}