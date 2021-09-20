#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TimerHandle_t pt_handle;
void *const pt_timerid;

void temperature_task(void *data)
{
while(1)
{
printf("temperature task started\n");
//--------
printf("temperature task ended\n");
vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}

void pressure_task(void *data)
{
while(1)
{
printf("pressure task started\n");
//--------
printf("pressure task ended\n");
vTaskDelay(2000 / portTICK_PERIOD_MS);
}
}

void CAN_task(void *data)
{
while(1)
{
printf("uart task started\n");
pt_handle = xTimerCreate("pt_timer", pdMS_TO_TICKS(10000), pdFLASE, &pt_timerid, callback_handler_function)
xTimerStart(pt_handle, 0);
printf("uart task ended\n");
vTaskDelay(5000 / portTICK_PERIOD_MS);
}
}

void callback_handler_function(TimerHandle_t xTimer)
{
printf("Timer is out \n");
}


void app_main(void)
{
    
    xTaskCreate(temperature_task, "temp_tsk", 2048, NULL, 3, NULL);
    xTaskCreate(pressure_task, "press_tsk", 2048, NULL, 3, NULL);
    xTaskCreate(CAN_task, "uart_tsk", 2048, NULL, 3, NULL);
    
}
