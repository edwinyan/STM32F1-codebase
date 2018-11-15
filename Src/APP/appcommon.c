#include "includes.h"
#include "appcommon.h"
#include "appUartApi.h"

u8		wave_display_buf[200];
u8		wave_display_buf_last[200];
u8		Lcd_CFG_Idle_Cnts=0;
u8		Lcd_Reflash_Cnts=0;

u8 		DC_Power_SetMode=DCPowerManualSet;
u8 		DischargeWithBuzzer=1;
u8		Auto_Test=AutoCycleTestDisable;
u8		LCD_Clear_Enable=LcdReflashEnable;


//static 	OS_CPU_SR cpu_sr;
void memsetv(u8*a,u8 b,u16 c)
{
    u16 i;

		
    for(i = 0 ; i < c ; i++)
            *(a + i) = b;
    return;
}

void memcopy(u8* a, const u8* b, u16 c)
{
    while(c)
    {
        *a = *b;
        c--;
        a++;
        b++;
    }
    
}

void DelaySync(u32 nFactor)
{
	u32 i;
	for(i=0; i<nFactor; i++){
		;
	}	

}

void Delay1Us(void)
{
	u8 i;

	for(i=0; i<8; i++){
		;
	}	

}

void Delay5Us(void)
{
	u8 i;

	for(i=0; i<48; i++){
		;
	}	

}

void DelayUs(u32 nFactor)
{
	u32 i;
	for(i=0; i<nFactor; i++){
		Delay1Us();
		IWDG_ReloadCounter();
	}	

}

void DelayMs(u16 nFactor)
{
	u16 i;
	u8 j;
	for(i=0; i<nFactor; i++){
		for(j=0; j<200; j++){
		Delay5Us();
		}	
		IWDG_ReloadCounter();

	}	

}



bool  set_power(u16 val)
{
	bool ret = TRUE;
//	INT8U send_buf[13];// 0 sync 3 编号 4电压 3电流 1校验
//	INT8U read_buf[13];
//	INT8U check_num=0xAA;
	
	return ret;

#if 0
      //changed by rex 2012.02.27
	#if 0
	return ret;
	return;
	
	#endif
	//changed by rex 2012.02.19  直接发送电源数据三次，不检测是否设定OK

	send_buf[0] = 0x7d; //sync
	send_buf[1] = '0'; //DC power Supply code nums
	send_buf[2] = '0'; //DC power Supply code nums
	send_buf[3] = '1'; //DC power Supply code nums
	send_buf[4] = ((val%10000)/1000 + 0x30) ; //Voltage Set	
	send_buf[5] = ((val%1000)/100 + 0x30); //Voltage Set	
	send_buf[6] = ((val%100)/10 + 0x30); //Voltage Set	
	send_buf[7] = (val%10 + 0x30); //Voltage Set	
	send_buf[8] = '4'; //Current Set
	send_buf[9] = '5'; //Current Set
	send_buf[10] = '0';  //Current Set
	check_num=send_buf[1] + 
			     send_buf[2] +
			     send_buf[3] +
			     send_buf[4] +
			     send_buf[5] +
			     send_buf[6] +
			     send_buf[7] +
			     send_buf[8] +
			     send_buf[9] +
			     send_buf[10];
	send_buf[11] = check_num; //check num
	send_buf[12] = 0x7d; //sync

	memsetv(read_buf, 0, sizeof(read_buf));
	
	//set and check power,
	OS_ENTER_CRITICAL();
	Fifo_Init();
	OS_EXIT_CRITICAL();

	OS_ENTER_CRITICAL();	
	Uart_PrintLen(send_buf, 13);
	OS_EXIT_CRITICAL();

	
	OSTimeDly(OS_TICKS_PER_SEC/10);	
	
	OS_ENTER_CRITICAL();	
	Uart_PrintLen(send_buf, 13);
	OS_EXIT_CRITICAL();

	OSTimeDly(OS_TICKS_PER_SEC/10);
	
	OS_ENTER_CRITICAL();	
	Uart_PrintLen(send_buf, 13);
	OS_EXIT_CRITICAL();

	#if 0
	Fifo_ReadNBytes(read_buf,13);

	if(   send_buf[0] == read_buf[0] &&
	      send_buf[1] == read_buf[1] &&
	      send_buf[2] == read_buf[2] &&
	      send_buf[3] == read_buf[3] &&
	      send_buf[4] == read_buf[4] &&
	      send_buf[5] == read_buf[5] &&
	      send_buf[6] == read_buf[6] &&
	      send_buf[7] == read_buf[7] &&
	      send_buf[8] == read_buf[8] &&
	      send_buf[9] == read_buf[9] &&
	      send_buf[10] == read_buf[10] &&
	      send_buf[11] == read_buf[11] &&
	      send_buf[12] == read_buf[12] )
	{
		ret=TRUE;
		Uart_Printf("-I-: DC Power Set OK  \r\n");
	}
	else
	{
		ret=FALSE;
		
	}

	if((ret==FALSE) && (DC_Power_SetMode==DCPowerManualSet))

	{
		ret=TRUE;
		Uart_Printf("-I-: DC Power Set fail! But in Manual mode  \r\n");
	}
	else
	{

		Uart_Printf("-E-: DC Power Set FAILED  \r\n");
	}
	
	//Uart_PrintLen(read_buf, 13);

	#endif

	
	return 1;
#endif

#if 0
	#if 1
	return ret;
	return;
	
	#endif

	send_buf[0] = 0x7d; //sync
	send_buf[1] = '0'; //DC power Supply code nums
	send_buf[2] = '0'; //DC power Supply code nums
	send_buf[3] = '1'; //DC power Supply code nums
	send_buf[4] = ((val%10000)/1000 + 0x30) ; //Voltage Set	
	send_buf[5] = ((val%1000)/100 + 0x30); //Voltage Set	
	send_buf[6] = ((val%100)/10 + 0x30); //Voltage Set	
	send_buf[7] = (val%10 + 0x30); //Voltage Set	
	send_buf[8] = '4'; //Current Set
	send_buf[9] = '5'; //Current Set
	send_buf[10] = '0';  //Current Set
	check_num=send_buf[1] + 
			     send_buf[2] +
			     send_buf[3] +
			     send_buf[4] +
			     send_buf[5] +
			     send_buf[6] +
			     send_buf[7] +
			     send_buf[8] +
			     send_buf[9] +
			     send_buf[10];
	send_buf[11] = check_num; //check num
	send_buf[12] = 0x7d; //sync

	memsetv(read_buf, 0, sizeof(read_buf));
	
	//set and check power,
	OS_ENTER_CRITICAL();
	Fifo_Init();
	OS_EXIT_CRITICAL();
	
	Uart_PrintLen(send_buf, 13);
	
	OSTimeDly(OS_TICKS_PER_SEC/10);	
	Fifo_ReadNBytes(read_buf,13);

	if(   send_buf[0] == read_buf[0] &&
	      send_buf[1] == read_buf[1] &&
	      send_buf[2] == read_buf[2] &&
	      send_buf[3] == read_buf[3] &&
	      send_buf[4] == read_buf[4] &&
	      send_buf[5] == read_buf[5] &&
	      send_buf[6] == read_buf[6] &&
	      send_buf[7] == read_buf[7] &&
	      send_buf[8] == read_buf[8] &&
	      send_buf[9] == read_buf[9] &&
	      send_buf[10] == read_buf[10] &&
	      send_buf[11] == read_buf[11] &&
	      send_buf[12] == read_buf[12] )
	{
		ret=TRUE;
		Uart_Printf("-I-: DC Power Set OK  \r\n");
	}
	else
	{
		ret=FALSE;
		
	}

	if((ret==FALSE) && (DC_Power_SetMode==DCPowerManualSet))

	{
		ret=TRUE;
		Uart_Printf("-I-: DC Power Set fail! But in Manual mode  \r\n");
	}
	else
	{

		Uart_Printf("-E-: DC Power Set FAILED  \r\n");
	}
	
	//Uart_PrintLen(read_buf, 13);

	
	return ret;
#endif

}

