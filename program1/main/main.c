#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t msgmq;


void t1_task(void *data)
{
while(1)
{
printf("t1 task started\n");
//--------
printf("t1 task ended\n");
vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}

void t2_task(void *data)
{
while(1)
{
printf("t2 task started\n");
//--------
printf("t2 task ended\n");
vTaskDelay(2000 / portTICK_PERIOD_MS);
}
}

void t3_task(void *data)
{
while(1)
{
printf("t3 task started\n");
//--------
printf("t3 task ended\n");
vTaskDelay(5000 / portTICK_PERIOD_MS);
}
}

void t4_task(void *data)
{
int msg=0;
while(1)
{
printf("t4 task started\n");
msg++;
xQueueSend(msgmq,&msg,0);
printf("t4 task ended\n");
vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}

void t5_task(void *data)
{
int buff;
while(1)
{
printf("t5 task started\n");
xQueueReceive(msgmq,&buff,0);
printf("t4 Buff=%d\n",buff);
printf("t5 task ended\n");
vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}

void app_main(void)
{
    int i = 0;
    msgmq = xQueueCreate(5, sizeof(int));
    xTaskCreate(t1_task, "t1_tsk", 2048, NULL, 3, NULL);
    xTaskCreate(t2_task, "t2_tsk", 2048, NULL, 3, NULL);
    xTaskCreate(t3_task, "t3_tsk", 2048, NULL, 3, NULL);
    xTaskCreate(t4_task, "t4_tsk", 2048, NULL, 3, NULL);
    xTaskCreate(t5_task, "t5_tsk", 2048, NULL, 3, NULL);
    while (1) {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
