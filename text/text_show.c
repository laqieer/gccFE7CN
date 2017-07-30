/*
 * text_show.c
 *
 *  Created on: 2015年4月21日
 *      Author: yami
 */


/**
 * @file		text_show.c
 * @author		yami
 * @date		2015-04-21 16:32:49
 * @brief
 * 显示的源码
 */


#include "../types.h"
#include "../call_func.h"

#include "../include/fe7func.h"

extern	void*		fonts[];
extern	void*		fonts2[];
extern void * fontsPtr[];
extern void * fonts2Ptr[];


typedef void* (*func_call)();
//#define _8005A60 ((func_call)0x8005A61)
//#define _80C0798 ((func_call)0x80C0799)
//#define _8005A24	((func_call)0x8005A25)
#define _8005A60 sub_8005A60
#define _80C0798 sub_80C0798
#define _8005A24 sub_8005A24

void*		T_show_font(u8*buf,void*a0);
void		T_show2_font(u8*buf,void*a0);

void*		text_show(void*a0,void*a1);
void		text_show2(void*a0,void*a1);

//SECTION(".80056D8")
HackSym(0x080056D8)
Optimize(2)
void* sub_80056D8H(void*a0,void*a1){
	ROM_Call_func_2(a0,a1,text_show);
}

void*		text_show(void*a0,void*a1)
{
	struct{
		u8		u0_[0x4];
		u32		u4_;
		u8		u8_[0xE];
		u8		u16_;
	}*var1;
	var1	=	*(void**)0x2028D68;
	if(var1->u16_){
		return (void*)_8005A60(a0,a1);
	}
	else{
		u8*		buf;
		buf		=	a1;
		_80C0798(buf,a0,T_show_font);
		buf		+=	2;
		return buf;
	}
}



//SECTION(".80055DC")
HackSym(0x080055DC)
Optimize(2)
void* sub_80055DCH(void*a0,void*a1){
	ROM_Call_func_2(a0,a1,text_show2);
}




void		text_show2(void*a0,void*a1)
{
	struct{
		u8		u0_[0x4];
		u32		u4_;
		u8		u8_[0xE];
		u8		u16_;
	}*var1;
	var1	=	*(void**)0x2028D68;
	if(var1->u16_){
		_8005A24(a0,a1);
	}
	else{
		_80C0798(a1,a0,T_show2_font);
	}
}

#if FE7CN

typedef struct{
		void*						next;
		unsigned	char			codeB;
		unsigned	char			w;
		unsigned	char			h;
		unsigned	char			unk_;
		unsigned	char			data[0x40];
}const rom_FFT;

typedef struct{
	unsigned	char			data_w;
	unsigned	char			y;
	unsigned	char			font_w;
	unsigned	char			u_;
	unsigned	char			data[0x50];
}FE_FFT;

void*		T_show_font(u8*buf,void*a0){
	u8 codeA,codeB;
	struct{
		u8		u0_[4];
		u8		*u4_;
		void*	(*func)();
	}*var1 = *((void**)0x2028D68);
	void * font;
	FE_FFT ff;
    codeA = buf[0];
    codeB = buf[1];
	//由于ROM里面使用的是Shift-JIS编码,汉字特别少,
	//所以,我将判断使用GBK
	//Shift-JIS范围 codeA 0x81-0x9F,0xE0-0xEF
	//Shift-JIS范围 codeB 0x40-0x7E,0x80-0xfc

	//gb2312		codeA 0xA1-0xA9
	//gb2312		codeB 0xA1-0xFE
    if(codeA>=0xA1)
    {
    	rom_FFT *f = fontsPtr[(codeA<<8)|(codeB)];
    	if((u32)f>0x08000000){
    		//自生成的字模
    		int i;
    		ff.font_w = f->w;
    		ff.data_w = 0xC;
    		ff.y = 0xc;
    		for(i=0;i<=12;i++){
    			ff.data[i*3+0] = f->data[i*4+0];
    			ff.data[i*3+1] = f->data[i*4+1];
    			ff.data[i*3+2] = f->data[i*4+2];
    		}
    		font = &ff;
    	}
    	else{
    		if((u32)f)
    		{
				codeA = ((((u32)f)>>0x8) & 0xff);
				codeB = (((u32)f) & 0xff);
    		}
    		else{
				codeA = 0x83;
				codeB = 0x9B;
    		}
    		font = 84 * (codeB - 0x80 + ((codeA - 129) << 7)) + var1->u4_;
    	}
    }
    else{
		if (codeA < 0x81 || codeA > 0x98 || codeB < 0x80 )
		{
		  codeA = 0x83;
		  codeB = 0x9B;
		}
		//sub_80C0798(a1, 84 * (codeB - 0x80 + ((codeA - 129) << 7)) + *(_DWORD *)(v2028D68 + 4), *(_DWORD *)(v2028D68 + 8));
		font = 84 * (codeB - 0x80 + ((codeA - 129) << 7)) + var1->u4_;
    }
    var1->func(a0,font);
    return buf+2;
}

void		T_show2_font(u8*buf,void*a0){
	struct{
		u8		u0_[4];
		u8		*u4_;
		void*	(*func)();
	}*var1 = *((void**)0x2028D68);
	FE_FFT ff;
	u8 codeA,codeB;
	void* font;
	while(1){
		if((codeA=*buf)<=1)
			break;
		buf++;
		if(codeA>0x1f){
			codeB = *buf++;
			if(codeA>=0xA1)
			{
				rom_FFT *f = fonts2Ptr[(codeA<<8)|(codeB)];
				//使用rom里面的字模
				if(((u32)f)>0x08000000){
		    		int i;
		    		ff.font_w = f->w;
		    		ff.data_w = 0xC;
		    		ff.y = 0xc;
		    		for(i=0;i<=12;i++){
		    			ff.data[i*3+0] = f->data[i*4+0];
		    			ff.data[i*3+1] = f->data[i*4+1];
		    			ff.data[i*3+2] = f->data[i*4+2];
		    		}
		    		font = &ff;
				}
				else{
					if(((u32)f)){
						//获得ROM里面的数据
						codeA = ((((u32)f)>>0x8) & 0xff);
						codeB = (((u32)f) & 0xff);
					}
					else{
						 codeA = 131;
						 codeB = 154;
					}
					font = 84 * (codeB - 128 + ((codeA - 0x81) << 7)) + var1->u4_;
				}
			}
			else
			{
				if (codeA < 0x81 ||codeA > 0x98 ||codeB < 0x80 )
				{
				  codeA = 131;
				  codeB = 154;
				}
				font = 84 * (codeB - 128 + ((codeA - 0x81) << 7)) + var1->u4_;
			}
	        var1->func(a0,font);
		}
	}
}


#else


void*		T_show_font(u8*buf,void*a0){
	struct{
		u8		u0_[4];
		u8		*u4_;
		void*	(*func)();
	}*var1;

	void**	font_base;
	u8		codeA;
	u8		codeB;
	struct{
		void*		next;
		u8			code;
		u8			w;
	}*font;

	var1		=	*((void**)0x2028D68);


	codeA	=	buf[0];
	codeB	=	buf[1];
	do{
		//由于ROM里面使用的是Shift-JIS编码,汉字特别少,
		//所以,我将判断使用GBK
		//Shift-JIS范围 codeA 0x81-0x9F,0xE0-0xEF
		//Shift-JIS范围 codeB 0x40-0x7E,0x80-0xfc

		//gb2312		codeA 0xA1-0xA9
		//gb2312		codeB 0xA1-0xFE
		if(codeA<=0x9F){
			font_base	=	(void*)(var1->u4_ - 0x100);
			font		=	font_base[codeB];		//这是编码2
			do{
				if(!font){
show_err:
					codeA		=	0x81;
					codeB		=	0xA7;
					var1		=	*((void**)0x2028D68);
					break;
				}
				if(font->code==codeA){
					return var1->func(a0,font);
				}
				else{
					font	=	font->next;
				}
			}while(1);
		}
		else{
#if 201612042303L
			font = fontsPtr[(codeA<<8)|codeB];
			if(font){
				return var1->func(a0,font);
			}
			else{
				goto show_err;
			}
#else
			//大于0x9F为gb编码
			font		=	fonts[codeA];
			while(font){
				if(font->code==codeB){
					return var1->func(a0,font);
				}
				else{
					font	=	font->next;
				}
			}
			goto	show_err;
#endif
		}
	}while(1);

}

void		T_show2_font(u8*buf,void*a0){
	struct{
		u8		u0_[4];
		u8		*u4_;
		void*	(*func)();
	}*var1;
	struct{
		void*		next;
		u8			code;
		u8			w;
	}*font;
	void**		font_base;
	u8*			src;

	src		=	buf;

	if(*src>1){
		u8	codeA,codeB;
		do{
		codeA		=	*src++;
			if(codeA>0x1F){
				//由于ROM里面使用的是Shift-JIS编码,汉字特别少,
				//所以,我将判断使用GBK
				//Shift-JIS范围 codeA 0x81-0x9F,0xE0-0xEF
				//Shift-JIS范围 codeB 0x40-0x7E,0x80-0xfc

				//gb2312		codeA 0xA1-0xA9
				//gb2312		codeB 0xA1-0xFE
				codeB	=	*src++;
				var1		=	*((void**)0x2028D68);
				if(codeA<=0xA1){
show_:
					font_base	=	(void**)(var1->u4_ - 0x100);
					font		=	font_base[codeB];
					while(font){
						if(font->code==codeA){
							var1->func(a0,font);
							break;
						}
						else{
							font	=	font->next;
							if(!font){
show_err:
								codeB	=	0xA7;
								codeA	=	0x81;
								goto show_;
							}
						}
					}
				}
				else{
					//GBK编码
#if 201612042303L
					//直接获得字模指针
					font		=	fonts2Ptr[(codeA<<8)|codeB];
					if(font){
						var1->func(a0,font);
					}
					else{
						goto show_err;
					}
#else
					font		=	fonts2[codeA];

					while(font){
						if(font->code==codeB){
							var1->func(a0,font);
							break;
						}
						else{
							font	=	font->next;
							if(!font){
								goto show_err;
							}
						}
					}
#endif
				}
			}
		}while(*src>1);
	}
}
#endif

