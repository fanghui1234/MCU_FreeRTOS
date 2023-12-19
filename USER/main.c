#include "stm32f4xx.h"
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include <stdio.h>
#include "usart.h"

TaskHandle_t app_task1_handle = NULL;
TaskHandle_t app_task2_handle = NULL;
void app_task1(void* pvParameters);
void app_task2(void* pvParameters);

int main(void)
{
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	//SysTick_Config(SystemCoreClock/configTICK_RATE_HZ);	//开启导致硬件错误中断
	USART1_Init(115200);
	printf("starting...\r\n");
	/* 创建app_task1任务 */
	xTaskCreate((TaskFunction_t )app_task1,  		/* 任务入口函数 */
			  (const char*    )"app_task1",			/* 任务名字 */
			  (uint16_t       )512,  				/* 任务栈大小 */
			  (void*          )NULL,				/* 任务入口函数参数 */
			  (UBaseType_t    )2, 					/* 任务的优先级 */
			  (TaskHandle_t*  )&app_task1_handle);	/* 任务控制块指针 */ 
	
	/* 创建app_task2任务 */		  
	xTaskCreate((TaskFunction_t )app_task2,  		/* 任务入口函数 */
			  (const char*    )"app_task2",			/* 任务名字 */
			  (uint16_t       )512,  				/* 任务栈大小 */
			  (void*          )NULL,				/* 任务入口函数参数 */
			  (UBaseType_t    )2, 					/* 任务的优先级 */
			  (TaskHandle_t*  )&app_task2_handle);	/* 任务控制块指针 */ 
	/* 开启任务调度 */
	vTaskStartScheduler(); 
}

void app_task1(void* pvParameters)
{
	int cnt = 0;
	for(;;)
	{
		printf("app_task1 is running %d...\r\n", cnt);
		vTaskDelay(1000);
		cnt++;
	}
}

void app_task2(void* pvParameters)
{
	int cnt = 0;
	for(;;)
	{
		printf("app_task2 is running %d...\r\n", cnt);
		vTaskDelay(1000);
		cnt++;
	}
}

