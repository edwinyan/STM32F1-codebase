#ifndef APP_UART_API_H_
#define  APP_UART_API_H_

#define UART_RECV_TO_TICKS			10		//for each byte

#define UART_CMD_SYNCWORD_L		0xAA
#define UART_CMD_SYNCWORD_H		0x55

#define FIFO_DEPTH					512



typedef struct FIFO_S{
  INT8U buf[FIFO_DEPTH];       /* Circular buffer */
  INT32U w_idx;            	    /* Index of write */
  INT32U r_idx;                       /* Index of read */
 }FIFO_T, *pFIFO_T;

void Fifo_Init(void);
bool Fifo_Write(INT8U dat);
bool Fifo_Read(INT8U *dat);
 INT8U Fifo_ReadNBytes(INT8U *pBuf,INT8U num);

void Uart_Init(void);
void Uart_Printf(INT8U *fmt, ...);
void Uart_PrintLen(INT8U *pBuf, INT16U len);
void Uart_Send(INT8U *pBuf, INT16U len);

#endif
