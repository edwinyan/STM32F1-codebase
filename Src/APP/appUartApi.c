#include "includes.h"
#include "appcommon.h"
#include "appUartApi.h"

static INT8U  UartSendBuf[512];
//static INT8U  UartRecvBuf[64];
static OS_EVENT* uart_send_sem=NULL;
FIFO_T Usart1_InFifo;

/*----------------------FIFO-------------------------*/
 bool Fifo_Read(INT8U *dat)
{
	bool ret = TRUE;
	pFIFO_T fifo = &Usart1_InFifo;
	

	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
	if ((fifo->r_idx == fifo->w_idx))
		ret = FALSE;//cout << "buffer empty\n";
	else{
		*dat = fifo->buf[fifo->r_idx];
		fifo->r_idx = (fifo->r_idx + 1) % FIFO_DEPTH;
	}
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	return ret;
}

 INT8U Fifo_ReadNBytes(INT8U *pBuf,INT8U num)
{
	INT8U read_cnt=0;
	INT32U cur_ticks=0;
	INT32U tar_ticks=0;
	
	tar_ticks=OSTimeGet()+num*UART_RECV_TO_TICKS;
	
	while(1)
	{
		INT8U read=0;

		cur_ticks = OSTimeGet();
		if(cur_ticks>tar_ticks)
		{
			//Uart_Printf("-W-:TO\r\n");
			break;
		}	
		if(Fifo_Read(&read) == FALSE) //If the fifo is empty
		{
			OSTimeDly(OS_TICKS_PER_SEC/1000);	//sleep 3ms
			continue;
		}
		
		pBuf[read_cnt++] = read; 
		if(read_cnt >= num) //Get enough data from fifo
			break;
	}

	return read_cnt;
}



void Fifo_Init(void)
{
	pFIFO_T fifo = &Usart1_InFifo;
	fifo->r_idx = 0;
	fifo->w_idx = 0;
		
	return;
}

bool Fifo_Write(INT8U dat)
{
	bool ret = TRUE;
	pFIFO_T fifo = &Usart1_InFifo;
	
	/* Save it to buffer */
	if (((fifo->w_idx + 1) % FIFO_DEPTH) == fifo->r_idx) {//Check if the fifo is full
		/* Adjust read index since buffer is full */
		/* Keep the latest one and drop the oldest one */
		fifo->r_idx = (fifo->r_idx + 1) % FIFO_DEPTH;
		Uart_Printf("-W-:F\r\n");
		ret = FALSE;//cout<< "buffer full\n";
	}
	
	fifo->buf[fifo->w_idx] = dat; //Write fifo
	fifo->w_idx = (fifo->w_idx + 1) % FIFO_DEPTH;//adjust w_idx

	return ret;
}
 







void Uart_Init(void)
{
      USART_InitTypeDef USART_InitStructure; //定义串口初始化结构体
      USART_ClockInitTypeDef  USART_ClockInitStructure;
      NVIC_InitTypeDef NVIC_InitStructure;

	Fifo_Init();
	// Enable the USART1 Interrupt //
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	


      /* USART1 configured as follow:
            - BaudRate = 115200 baud  
            - Word Length = 8 Bits
            - One Stop Bit
            - No parity
            - Hardware flow control disabled (RTS and CTS signals)
            - Receive and transmit enabled
            - USART Clock disabled
            - USART CPOL: Clock is active low
            - USART CPHA: Data is captured on the middle 
            - USART LastBit: The clock pulse of the last data bit is not 
    	output to 
                             the SCLK pin
      */
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	/* Configure the USART1 synchronous paramters */	//最后数据位的时钟脉冲不输出到SCLK引脚
	USART_ClockInit(USART1, &USART_ClockInitStructure);

	USART_InitStructure.USART_BaudRate = 115200; //波特率115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* Configure USART1 basic and asynchronous paramters */
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
  	/* Enable USART1 */
  	USART_Cmd(USART1, ENABLE);
	uart_send_sem = OSSemCreate(1);
	if(!uart_send_sem)
	{
		while(1);
	}

	
}


void Uart_Printf(INT8U *fmt, ...)
{
  	INT8U *pBuf;
	INT8U err;

	
	va_list ap;

//	return;
	OSSemPend(uart_send_sem, 0, &err);
	
	va_start(ap,fmt);
	vsprintf((char *)UartSendBuf,(const char *)fmt,ap);


	pBuf = UartSendBuf;
	while (*pBuf) {
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);          
    		USART_SendData(USART1, *pBuf );
		pBuf ++;
	}		
	va_end(ap);

	OSSemPost(uart_send_sem);
	
}

void Uart_PrintLen(INT8U *pBuf, INT16U len)
{
	INT8U err;

//	return;
	
	OSSemPend(uart_send_sem, 0, &err);
	while (len--) {
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);          
    		USART_SendData(USART1, *pBuf );
		pBuf ++;
	}		
	OSSemPost(uart_send_sem);
}


void Uart_Send(INT8U *pBuf, INT16U len)
{
	INT8U err;

	
	OSSemPend(uart_send_sem, 0, &err);
	while (len--) {
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);          
    		USART_SendData(USART1, *pBuf );
		pBuf ++;
	}		
	OSSemPost(uart_send_sem);
}







