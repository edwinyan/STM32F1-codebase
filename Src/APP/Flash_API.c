#include "includes.h"
#include "Flash_Api.h"


void Flash_Init(void)
{
	u32 WRPR_Value = 0xFFFFFFFF;
	u32 ProtectedPages = 0x0;

	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP|FLASH_FLAG_PGERR |FLASH_FLAG_WRPRTERR);
	
	//Check Write Protection Settings: Stored in Flash  WRPR Register, Loaded from Option bytes area: 0x1FFF_F800 - 0x1FFF_F80F
	WRPR_Value = FLASH_GetWriteProtectionOptionByte();

	//the Upper 64K bytes of the 128K bytes flash is used to save information.   Pages:  64 ~ 128
	ProtectedPages = WRPR_Value & FLASH_WRITE_PROTECT_MASK;
	
	if (ProtectedPages != FLASH_WRITE_PROTECT_MASK)
	{
		FLASH_EraseOptionBytes();
		/* Generate System Reset to load the new option byte values */
		NVIC_GenerateSystemReset();
	}


}


/*
	dwOffset:     BYTE address. Must be Half-Word aligned
	dwLen:	     BYTE lenght.   Must be Half-Word aligned
	dwPageAddr: 0-63. Internal embeded flash (64KB)		
*/

bool Flash_Page_Read(u32 dwPageAddr,u8* pReadBuffer,u32 dwOffset, u32 dwLen)
{
	u32 dwIndex=0;
	u16 *pwReadPtr = (u16 *)(FLASH_PAGE_SIZE*dwPageAddr+FLASH_BASE_ADDR);
	u16 wReaded = 0;
	
	if(dwPageAddr>=FLASH_PAGE_NUM)
		return FALSE;
	
	if((dwOffset+dwLen)>FLASH_PAGE_SIZE)
		return FALSE;
		
	pwReadPtr += (dwOffset/2); 
		
	for(dwIndex=0;dwIndex<(dwLen/2);dwIndex++)
	{
		wReaded = *pwReadPtr;
		pReadBuffer[2*dwIndex] = (wReaded)&0xFF;
		pReadBuffer[2*dwIndex+1] = (wReaded>>8)&0xFF;
		pwReadPtr++;
	}
	
	return TRUE;
	
}






/*			
	dwPageAddr: 0-63. Internal embeded flash (64KB)		
*/
bool Flash_Page_Erase(u32 dwPageAddr)
{

	if(dwPageAddr>=FLASH_PAGE_NUM)
		return FALSE;
	
	if(FLASH_COMPLETE==FLASH_ErasePage((FLASH_PAGE_SIZE*dwPageAddr)+FLASH_BASE_ADDR))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}



/*
	dwOffset:     BYTE address. Must be Half-Word aligned
	dwLen:	     BYTE lenght.   Must be Half-Word aligned
	dwPageAddr: 0-63. Internal embeded flash (64KB)		
			
*/
bool Flash_Page_Write(u32 dwPageAddr,u8* pWriteBuffer,u32 dwOffset, u32 dwLen)
{

	u32 dwIndex=0;
	u16 wWrite = 0;
	u16 *pwWritePtr = (u16 *)(FLASH_PAGE_SIZE*dwPageAddr+FLASH_BASE_ADDR);
	
	if(dwPageAddr>=FLASH_PAGE_NUM)
		return FALSE;

	if((dwOffset+dwLen)>FLASH_PAGE_SIZE)
		return FALSE;

	pwWritePtr += (dwOffset/2); 
	
	for(dwIndex=0;dwIndex<(dwLen/2);dwIndex++)
	{
		wWrite = pWriteBuffer[2*dwIndex+1];
		wWrite = wWrite<<8;
		wWrite |= pWriteBuffer[2*dwIndex];
		
		if(FLASH_COMPLETE!=FLASH_ProgramHalfWord((u32)pwWritePtr, wWrite))
		{
			return FALSE;
		}
		pwWritePtr++;
	}

	return TRUE;
}








