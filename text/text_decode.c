/*
 * text_decode.c
 *
 *  Created on: 2015年4月21日
 *      Author: yami
 */


/**
 * @file		text_decode.c
 * @author		yami
 * @date		2015-04-21 15:43:32
 * @brief
 * 程序的解码
 */

#include "../types.h"

#include "../include/fe7func.h"

extern  u8*	const texts[];
extern const u32 texts_size;


extern		void	_80C0798();



typedef void* (*func_call)();
//#define _80C0798	((func_call)0x80C0798+1)
#define _80C0798 sub_80C0798

void		text_decodeEx(u32 a0,void*a1);

//SECTION(".8013318")
HackSym(0x08013318)
Optimize(2)
void*		text_decode(u32 a0){
	u32		*_txt;
	_txt	=	(u32*)0x202B5B0;
	if(a0==*_txt){
		//表示上一个编号的文本
		return (void*)0x202A5B0;		//字符串首地址
	}
	else{
		u8*		buf;
		buf		=	(void*)0x202A5B0;
		//text_decodeEx(a0,buf);
		_80C0798(a0,buf,text_decodeEx);
		*_txt	=	a0;
		return (void*)0x202A5B0;
	}
}

void		*call_func(void*a0,void*a1,void*a2);
void		text_decodeEx(u32 a0,void*a1){
	u8*		src;
	u8*		dst;
	src		=	texts[a0<texts_size?a0:0];
	dst		=	a1;
    //如果texts不存在该文本指针，则获得ROM里面的指针
    if(!src)
    {
        u32 *pptr = (u32*)0x80006DC;
        void ** text_ptr = (void**)(*pptr + 4);
        src = (u8*)text_ptr[a0];
    }
    
	if((u32)src&0x80000000){
		src = (u8*)((u32)src-0x80000000);
		while((*dst++=*src++)){

		};			//直接复制过去,如遇到0则停止
	}
	else{
        call_func(src,a1,(void*)(0x08004241));	//回调函数,并且是Thumb函数
	}
}

void		*call_func(void*a0,void*a1,void*a2){
	void*	(*func)();
	func	=	a2;
	return func(a0,a1);
}
