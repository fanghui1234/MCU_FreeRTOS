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
	//SysTick_Config(SystemCoreClock/configTICK_RATE_HZ);	//��������Ӳ�������ж�
	USART1_Init(115200);
	printf("starting...\r\n");
	/* ����app_task1���� */
	xTaskCreate((TaskFunction_t )app_task1,  		/* ������ں��� */
			  (const char*    )"app_task1",			/* �������� */
			  (uint16_t       )512,  				/* ����ջ��С */
			  (void*          )NULL,				/* ������ں������� */
			  (UBaseType_t    )2, 					/* ��������ȼ� */
			  (TaskHandle_t*  )&app_task1_handle);	/* ������ƿ�ָ�� */ 
	
	/* ����app_task2���� */		  
	xTaskCreate((TaskFunction_t )app_task2,  		/* ������ں��� */
			  (const char*    )"app_task2",			/* �������� */
			  (uint16_t       )512,  				/* ����ջ��С */
			  (void*          )NULL,				/* ������ں������� */
			  (UBaseType_t    )2, 					/* ��������ȼ� */
			  (TaskHandle_t*  )&app_task2_handle);	/* ������ƿ�ָ�� */ 
	/* ����������� */
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

