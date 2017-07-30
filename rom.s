	.section  .rom,"xa"
	.global	_start
	.global rom_size
_start:
	.incbin "fe7.gba"
    
    #gba修改定义宏
    .include "asm/gba_def.inc"
    
    #fe7 函数定义
    .include "include/fe7func.inc"
#    .global	sub_80B8C80
#    .code 16
#    .thumb_func
#    .type	sub_80B8C80,%function
#    .size	sub_80B8C80,0x1C
