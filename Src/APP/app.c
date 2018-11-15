/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2006; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/


#include <includes.h>
//#include "appinfor.h"
#include "appcommon.h"


static OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];
//App_Info_St app_info;

static  void  AppTaskStart (void *p_arg)
{
	(void)p_arg;

   	BSP_Init();                                                 /* Initialize BSP functions                                 */
//	appInfor_LoadCheck(&app_info);
#if (OS_TASK_STAT_EN > 0)
    	OSStatInit();                                               /* Determine CPU capacity                                   */
#endif
//	Relay_01_ON;	// for 掉电重启提示状态输出
//	appRCHTask_Init();
//	appLCD_Display_Init();
//	appUserIF_Init();
//	appTouchTask_Init();
	
	IWdg_Config();

//	Relay_01_OFF; // for 掉电重启提示状态输出

	
  	while(DEF_TRUE)
	{
		OSTimeDly(OS_TICKS_PER_SEC/2);	
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		OSTimeDly(OS_TICKS_PER_SEC/2);	
 		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		IWDG_ReloadCounter();
//		Lcd_CFG_Idle_Cnts++; //add by rex 2011.10.04
//		Lcd_Reflash_Cnts++;
	}
}



int  main (void)
{

	INT8U err;
	/* Set the Vector Table base location at 0x08000000 */ 
  	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   

    OSInit();                          /* Initialize "uC/OS-II, The Real-Time Kernel"              */

   	/* Create the start task */
	OSTaskCreateExt(AppTaskStart,
			(void *)0,
			(OS_STK *)&AppTaskStartStk[APP_TASK_START_STK_SIZE-1],
			APP_TASK_START_PRIO,
			APP_TASK_START_PRIO,
			(OS_STK *)&AppTaskStartStk[0],
			APP_TASK_START_STK_SIZE,
			(void *)0,
			OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);
#if (OS_TASK_NAME_SIZE > 13)
       OSTaskNameSet(APP_TASK_START_PRIO, "Start Task", &err);
#endif

    OSStart();        /* Start multitasking (i.e. give control to uC/OS-II)       */

}


