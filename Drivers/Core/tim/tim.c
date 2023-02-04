#include "tim.h"

uint32_t Global_Timer_Tick_Ms = 0;

TIM_HandleTypeDef htim14;

/* TIM14 init function */
//ͨ�ö�ʱ��14�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��14!
void TIM14_Init(uint16_t arr,uint16_t psc)
{
	htim14.Instance = TIM14;							//ͨ�ö�ʱ��14
	htim14.Init.Prescaler = psc;						//��Ƶϵ��
	htim14.Init.CounterMode = TIM_COUNTERMODE_UP;		//���ϼ�����
	htim14.Init.Period = arr;							//�Զ�װ��ֵ
	htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;	//ʱ�ӷ�Ƶ����
	htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
	{
		Error_Handler();
	}
	
	HAL_TIM_Base_Start_IT(&htim14); //ʹ�ܶ�ʱ��14�����жϣ�TIM_IT_UPDATE
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{
	if(tim_baseHandle->Instance==TIM14)
	{
		__HAL_RCC_TIM14_CLK_ENABLE();
		HAL_NVIC_SetPriority(TIM14_IRQn,3,3);		//�����ж����ȼ�����ռ���ȼ�3�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM14_IRQn);				//����TIM14�ж�
	}
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{
	if(tim_baseHandle->Instance==TIM14)
	{
		__HAL_RCC_TIM14_CLK_DISABLE();
	}
}

//��ʱ��14�жϷ�����
void TIM14_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim14);
}

//�ص���������ʱ���жϷ���������
#include "main.h"
extern main_Task_Flag_t main_Task_Flag;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&htim14))
    {
        Global_Timer_Tick_Ms++;
		if ((main_Task_Flag.refresh == 0) && (Global_Timer_Tick_Ms != 0)
			&& (Global_Timer_Tick_Ms % 33 == 0)) {  // 30Hz
			main_Task_Flag.refresh = 1;
		}
		if ((main_Task_Flag.moveBullet == 0) && (Global_Timer_Tick_Ms != 0)
			&& (Global_Timer_Tick_Ms % 200 == 0)) {  // 5Hz
			main_Task_Flag.moveBullet = 1;
		}
    }
}
