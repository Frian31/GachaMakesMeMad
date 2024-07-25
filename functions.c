#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"functions.h"

//创建玩家
struct player you; // 这是你
struct player your_friend[FriendsNum]; // 这是你的朋友
struct logDaily Log[Simulation_Days]; // 这是日志
/*
计算不满指数的方式：
在你未能中大奖的情况下，每天每个抽中大奖的朋友都为你加(1 * 嫉妒系数)分
嫉妒系数 = 1 / 朋友总数
*/
float ComplainRatio = (1.0/(float)FriendsNum); // 嫉妒系数
float ComplainScore = 0; // 不满指数
//输出实验初始数据
void ExperimentStatus(void)
{
    printf("FriendsNum = %d\n", FriendsNum);
    printf("ComplainRatio = %f\n", ComplainRatio);
    printf("P = %f\n", P);
    printf("GetCount = %d\n", GetCount);
    printf("Simulation_Days = %d\n", Simulation_Days);
}
// 初始化所有玩家数据
void Init_allPlayers(void)
{
    int i;
    you.ifGetPrice = 0;

    for(i = 0; i < FriendsNum; i ++)
    {
        your_friend[i].ifGetPrice = 0;
    }

}
// 输入概率P，本函数有P的概率返回真。
char getPrice(double p)
{
    // 生成一个0到1之间的浮点数  
    double randomValue = (double)rand() / (double)(RAND_MAX + 1);  
  
    // 如果这个数小于或等于P，则返回真（这里用1表示真）  
    if (randomValue <= p) {  
        return TRUE; // 真  
    } else {  
        return FALSE; // 假  
    }  
}
// 输出日志
void logOutput(void)
{
    int i;
    printf("============================\n");
    printf("your complain score:%f\n", ComplainScore);
    printf("days\tifyougetprice\tfriendsgetprice\n");
    for(i = 0; i < Simulation_Days; i ++)
    {
        printf("%d\t%d\t%d\n", Log[i].dayNumber, Log[i].ifYouGetPrice, Log[i].friendsGetPrice);
    }
    printf("\n============================\n");
}
// 执行一次实验
void doExperiment(void)
{
    int day; // 模拟进行到的天数
    int i;
    int j;
    for(day = 1; day <= Simulation_Days; day ++)
    {
        Log[day-1].friendsGetPrice = 0;

        //如果你没有获得目标奖励，抽取奖励
        if(you.ifGetPrice == FALSE)
        {
            for(j = 0; j < GetCount; j ++)
                you.ifGetPrice = getPrice(P);
        }
        //对你的朋友而言也一样
        for(i = 0; i < FriendsNum; i ++)
        {
            if(your_friend[i].ifGetPrice == FALSE)
            {
                for(j = 0; j < GetCount; j ++)
                    your_friend[i].ifGetPrice = getPrice(P);
            }
        }
        //统计环节
        Log[day-1].friendsGetPrice = 0;
        for(i = 0; i < FriendsNum; i ++)
        {
            if(your_friend[i].ifGetPrice == TRUE)
            {
                Log[day-1].friendsGetPrice ++;
            }
        }
        Log[day-1].dayNumber = day;
        Log[day-1].ifYouGetPrice = you.ifGetPrice;

        if(you.ifGetPrice == FALSE)
        {
            //积累不满值
            ComplainScore += (Log[day-1].friendsGetPrice * ComplainRatio);
        }
    }
    #if REPEAT_MODE
    printf("your complain score:%f\n", ComplainScore);
    #endif
}
