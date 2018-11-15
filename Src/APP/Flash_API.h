
#ifndef __FLASH_APP__
#define __FLASH_APP__


#define FLASH_PAGE_SIZE   				((u16)0x400)

#define FLASH_BASE_ADDR				(0x08000000 + (64*FLASH_PAGE_SIZE))

#define FLASH_WRITE_PROTECT_MASK		0xFFFF0000


#define FLASH_PAGE_NUM					64


void Flash_Init(void);
bool Flash_Page_Read(u32 dwPageAddr,u8* pReadBuffer,u32 dwOffset, u32 dwLen);
bool Flash_Page_Erase(u32 dwPageAddr);
bool Flash_Page_Write(u32 dwPageAddr,u8* pWriteBuffer,u32 dwOffset, u32 dwLen);

#endif






