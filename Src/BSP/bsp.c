/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2007; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*           e	    Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        BOARD SUPPORT PACKAGE
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   STM3210B-EVAL Evaluation Board
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : Brian Nagel
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_GLOBALS
#include <includes.h>
#include "appCommon.h"



/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
static volatile ErrorStatus HSEStartUpStatus = SUCCESS;


/*
*********************************************************************************************************
*                                     DISABLE ALL INTERRUPTS
*
* Description : This function disables all interrupts from the interrupt controller.
*
* Arguments   : None.
*
* Returns     : None.
*********************************************************************************************************
*/
void  BSP_IntDisAll (void)
{
  // CPU_IntDis();
}

/*
******************************************************************************************************************************
******************************************************************************************************************************
**                                         uC/OS-II Timer Functions
******************************************************************************************************************************
******************************************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       TICKER INITIALIZATION
*
* Description : This function is called to initialize uC/OS-II's tick source (typically a timer generating
*               interrupts every 1 to 100 mS).
*
* Arguments   : none
*
* Note(s)     : 1) The timer is setup for output compare mode BUT 'MUST' also 'freerun' so that the timer
*                  count goes from 0x00000000 to 0xFFFFFFFF to ALSO be able to read the free running count.
*                  The reason this is needed is because we use the free-running count in uC/OS-View.
*********************************************************************************************************
*/

void  SysTick_Config(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    INT32U         cnts;


    RCC_GetClocksFreq(&rcc_clocks);

    cnts = (INT32U)rcc_clocks.HCLK_Frequency/OS_TICKS_PER_SEC;

    SysTick_SetReload(cnts);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    SysTick_CounterCmd(SysTick_Counter_Enable);
    SysTick_ITConfig(ENABLE);
}



void GPIO_Config(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;



      /* Configure USART1 Tx (PA.09) as alternate function push-pull */
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
       /* Configure USART1 Rx (PA.10) as input floating */
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOA, &GPIO_InitStructure);


	/* Configure AIN0~3  (PA.00 PA.01 PA.02 PA.03)  */

	/* Configure ADC CH0-CH7(PA.00-PA07) as analog input  */
       GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	/* Configure TC_CS,TC_CLK,TC_MISO,TC_MOSI,TC_INT  (PA.04 PA.05 PA.06 PA.07 PB.00)  */
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOA, &GPIO_InitStructure);

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOA, &GPIO_InitStructure);

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);


	

	/* Configure DIN0~3  (PA.08 PA.11 PA.12 PA.13)  */
	/* Configure KEY0~7  (PC.00 PC.01 PC.02 PC.03 PC.04 PC.05 PB.01 PB.10)  */


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1| GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);




	/* Configure Buzzer&Status  (PC.09 PC.13 )  */
	/* Configure Buzzer Relay1~4  ( PC.08 PC.07 PC.06 PB.15)  */
	/* Configure PC  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_13;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //推挽输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);	


	/* Configure PWM1~4  (PB.14 PB.13 PB.12 PB.11)  */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //推挽输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	/* Configure TFT_RD,TFT_CS,TFT_WR,TFT_CD,LCD_E (PB.09 PB.08 PB.07 PB.06 PB.05)  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;		 //推挽输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	
	/* Configure TFT_D0~7 ( PB.04 PB.03 PD.02 PC.12 PC.11 PC.10 PA.15 PA.14 )  */
	/*            --------------D0---D1---D2---D3---D4---D5---D6---D7----*/
	// 改变指定管脚的映射 GPIO_Remap_SWJ_Disable SWJ 完全禁用（JTAG+SW-DP）
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	// 改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;		
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;		
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;		
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);	


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;		 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);	







	
#if 0
	/* Configure led0 & led1 (PA.00-PA01)  */
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2| GPIO_Pin_3;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		 //推挽输出
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);


      /* Configure TIM4_CH1 (PB.6)/TIM4_CH1 (PB.7)/TIM4_CH1 (PB.8)/TIM4_CH1 (PB.9) */
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);

#endif


      /* ADC1 configuration */
      ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
      ADC_InitStructure.ADC_ScanConvMode = ENABLE;
      ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
      ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
      ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
      ADC_InitStructure.ADC_NbrOfChannel = 1;
      ADC_Init(ADC1, &ADC_InitStructure);

#if 1		  
      ADC_InjectedSequencerLengthConfig(ADC1, 1);
      ADC_InjectedChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_7Cycles5);
#else
      ADC_InjectedSequencerLengthConfig(ADC1, 4);
      ADC_InjectedChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
      ADC_InjectedChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);
      ADC_InjectedChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5);
      ADC_InjectedChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5);

#endif
      ADC_AutoInjectedConvCmd(ADC1,ENABLE);

      //ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);

	  
      /* Enable ADC1 */
      ADC_Cmd(ADC1, ENABLE);
    
      /* Enable ADC1 reset calibaration register */   
      ADC_ResetCalibration(ADC1);
      /* Check the end of ADC1 reset calibration register */
      while(ADC_GetResetCalibrationStatus(ADC1));
    
      /* Start ADC1 calibaration */
      ADC_StartCalibration(ADC1);
      /* Check the end of ADC1 calibration */
      while(ADC_GetCalibrationStatus(ADC1));
      /* Enable ADC1 */
      
      /* Start ADC1 Software Conversion */ 
      ADC_SoftwareStartConvCmd(ADC1, ENABLE);


#if 0
      /* ADC2 configuration */
      ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
      ADC_InitStructure.ADC_ScanConvMode = ENABLE;
      ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
      ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
      ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
      ADC_InitStructure.ADC_NbrOfChannel = 1;
      ADC_Init(ADC2, &ADC_InitStructure);
    	  
      ADC_InjectedSequencerLengthConfig(ADC2, 4);
      ADC_InjectedChannelConfig(ADC2, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5);
      ADC_InjectedChannelConfig(ADC2, ADC_Channel_5, 2, ADC_SampleTime_239Cycles5);
      ADC_InjectedChannelConfig(ADC2, ADC_Channel_6, 3, ADC_SampleTime_239Cycles5);
      ADC_InjectedChannelConfig(ADC2, ADC_Channel_7, 4, ADC_SampleTime_239Cycles5);
      ADC_AutoInjectedConvCmd(ADC2,ENABLE);
     ADC_ITConfig(ADC2, ADC_IT_JEOC, ENABLE);
      
      /* Enable ADC2 */
      ADC_Cmd(ADC2, ENABLE);
    
      /* Enable ADC2 reset calibaration register */   
      ADC_ResetCalibration(ADC2);
      /* Check the end of ADC2 reset calibration register */
      while(ADC_GetResetCalibrationStatus(ADC2));
    
      /* Start ADC2 calibaration */
      ADC_StartCalibration(ADC2);
      /* Check the end of ADC2 calibration */
      while(ADC_GetCalibrationStatus(ADC2));
      /* Enable ADC2 */
      
      /* Start ADC2 Software Conversion */ 
      ADC_SoftwareStartConvCmd(ADC2, ENABLE);

#endif

	


	
	

	
		
}

void InterruptConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;//定义NVIC初始化结构体变量
#if 0
	NVIC_InitStructure.NVIC_IRQChannel=ADC1_2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
	
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//配置优先级组为1位
	  //配置RTC中断
	 NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQChannel;//中断通道为RTC全局中断
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//1位优先级
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//0位子优先级
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断通道使能
	 NVIC_Init(&NVIC_InitStructure);//初始化NVIC结构体

}




void  Timer_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	  /* Time base configuration */
	  TIM_TimeBaseStructure.TIM_Period = 1999;//用以修改PWM调整范围占总范围多少
	  TIM_TimeBaseStructure.TIM_Prescaler = 500; //reset the carrier frequency 调整PWM 载波频率
	  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	  TIM_ARRPreloadConfig(TIM4, ENABLE);

	  /* TIM4 enable counter */
	  TIM_Cmd(TIM4, ENABLE);

}


void IWdg_Config(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_256);		// 40Khz/256 :  6.4ms 每个clock
	IWDG_SetReload(250);					       //500个clock	
	IWDG_ReloadCounter();
	IWDG_Enable();
	
}

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
******************************************************************************************************************************
******************************************************************************************************************************
**                                         Global Functions
******************************************************************************************************************************
******************************************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         BSP INITIALIZATION
*
* Description : This function should be called by your application code before you make use of any of the
*               functions found in this module.
*
* Arguments   : none
*********************************************************************************************************
*/

void  BSP_Init(void)
{

  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();//复位RCC外部设备寄存器到默认值

  /* Enable HSE *///打开外部高速晶振
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();//等待外部高速时钟准备好

  if(HSEStartUpStatus == SUCCESS)//外部高速时钟已经准别好
    {
     /* Enable Prefetch Buffer *///使能FLASH预取缓冲区
     FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

     /* Flash 2 wait state *///FLASH延时2个周期
     FLASH_SetLatency(FLASH_Latency_2);
    
     /* HCLK = SYSCLK *///配置AHB(HCLK)时钟等于==SYSCLK
     RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
     /* PCLK2 = HCLK *///配置APB2(PCLK2)钟==AHB时钟
     RCC_PCLK2Config(RCC_HCLK_Div1); 
 
     /* PCLK1 = HCLK/2 *///配置APB1(PCLK1)钟==AHB1/2时钟
     RCC_PCLK1Config(RCC_HCLK_Div2);
 
     /* PLLCLK = 8MHz * 9 = 72 MHz */
     RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

     /* ADCCLK = PCLK2/8 = 18Mhz */
     RCC_ADCCLKConfig(RCC_PCLK2_Div4);

     /* Enable PLL */ 
     RCC_PLLCmd(ENABLE);
    
     /* Wait till PLL is ready *///等待PLL时钟就绪
     while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
       {
       }
 
     /* Select PLL as system clock source *///配置系统时钟 = PLL时钟
     RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
 
     /* Wait till PLL is used as system clock source *///检查PLL时钟是否作为系统时钟
	 
     while(RCC_GetSYSCLKSource() != 0x08)
      {
      }
    }


    /* TIM4 clock enable */
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC 
         | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG 
         | RCC_APB2Periph_AFIO|RCC_APB2Periph_USART1|RCC_APB2Periph_ADC1|RCC_APB2Periph_ADC2|RCC_APB2Periph_TIM1, ENABLE);

 	
   GPIO_Config();
   SysTick_Config();                                             /* Initialize the uC/OS-II tick interrupt                   */
   Uart_Init();
   InterruptConfig();
//   Timer_Config();


}


