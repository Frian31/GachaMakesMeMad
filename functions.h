#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#define FriendsNum 20 // 朋友总数

#define P 0.018 // 中奖概率
#define GetCount 3 // 每天每人可抽奖次数
#define Simulation_Days 30 // 抽奖活动持续时间（天）

#define FALSE 0 // 定义逻辑假
#define TRUE 1 // 定义逻辑真

#define ExperimentTimes 500 // 模拟实验循环次数

#define REPEAT_MODE 1 // 1：循环实验模式 0：单次实验模式

void ExperimentStatus(void);
void Init_allPlayers(void);
char getPrice(double p);
void logOutput(void);
void doExperiment(void);

//玩家结构体
struct player
{
    char ifGetPrice;
};

//每日统计日志结构体
struct logDaily
{
    int dayNumber;
    char ifYouGetPrice;
    int friendsGetPrice;
};

#endif /*_FUNCTIONS_H*/