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

/*
*********************************************************************************************************
*
*                                      APPLICATION CONFIGURATION
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   STM3210B-EVAL Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : Brian Nagel
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  uC_PROBE_OS_PLUGIN              DEF_DISABLED            /* DEF_ENABLED = Present, DEF_DISABLED = Not Present        */
#define  uC_PROBE_COM_MODULE             DEF_DISABLED

/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/
#define   RCH_TASK_PRIO		   				3	//��״̬����AD���ݲɼ�
#define   USER_IF_TASK_PRIO		   			4	//�û����������������: ��UartͨѶ��
#define   TOUCH_TASK_PRIO			   		5   //�����û��������룬���Ƶײ����ģ��: PWM��AD��
#define   LCD_TASK_PRIO			 			8


#define   APP_TASK_START_PRIO                   	(OS_LOWEST_PRIO - 3)	//��ʼ��������
#define   OS_TASK_TMR_PRIO              			(OS_LOWEST_PRIO - 2)






#define ADC_ENABLE							1






#define  APP_TASK_START_STK_SIZE             128

#endif
