


SECTIONS
{
	
	. = 0x08000000;
	.rom (COPY): 
	{
		KEEP (*.o(.rom))
	}
	
	.text : 
	{
		*(.text);
	} 
	
	.rodata : 
	{
		/*
		KEEP (*(EXCLUDE_FILE (data_*.o) .rodata))
		KEEP (*(.rodata))
		*/
		*(.rodata)
		. = ALIGN(4);
	} 
	
	.data : 
	{
		KEEP (*(.data))
		. = ALIGN(4);
	}
	
	. = ALIGN(0x10);	/*对齐*/
	.hackinfo : 
	{
		KEEP (*(.hackinfo2))
	}
	
	/*
	.ewram : 
	{
		. = 0x3FFFF;
	} >ewram
	
	.iwram : 
	{
		. = 0x7FFF;
	} >iwram
	
	
	.ioram : 
	{
		INCLUDE "gbaio.ld"
		. = 0x400;
	} >ioram

	
	.palram : 
	{
		. = 0x400;
	} >palram
	

	.vram : 
	{
		. = 0x17fff;
	} >vram
	

	.oam : 
	{
		. = 0x400;
	} >OAMram
	*/
	
INCLUDE hack_data.ld
}
