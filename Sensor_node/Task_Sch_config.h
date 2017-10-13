#ifndef TASK_SCH_CONFIG_H
#define TASK_SCH_CONFIG_H

//--------------------Config Parameter--------------------------
#define MAX_TASK_NUM        (3)
#define task0               Task_Sensing
#define task1               Task_UpdateOrder
#define task2               Task_SelfAppeal
#define WDT_CNT_TIME        (4)             //秒単位設定
#define TASK1_TIME_DEBUG    (4)             //秒単位設定 誤差調整含む
#define TASK1_TIME_SHORT    (60)            //秒単位設定 誤差調整含む
#define TASK1_TIME_LONG     (3600)          //秒単位設定 誤差調整含む
#define TASK2_TIME          (12)            //秒単位設定 誤差調整含む
#define TASK3_TIME          (12)            //秒単位設定 誤差調整含む

#endif
