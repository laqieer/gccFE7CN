/*
 * call_func.h
 *
 *  Created on: 2015年3月10日
 *      Author: yimi
 */

#ifndef CALL_FUNC_H_
#define CALL_FUNC_H_

#include "types.h"

typedef u32 (*func)();

typedef u8 (*func_u8)();


u32 call_func_3(void*,void*,void*,void*);
u32 call_func_2(void*,void*,void*);
u32	call_func_1(void*,void*);
u32	call_func_0(void*);


//STATIC INLINE u32 call_func_3(void*a0,void*a1,void*a2,void*a3){
//	return (u32)((func)(a3))(a0,a1,a2);
//}
//STATIC INLINE u32 call_func_2(void*a0,void*a1,void*a2){
//	return (u32)((func)(a2))(a0,a1);
//}
//STATIC INLINE u32	call_func_1(void*a0,void*a1){
//	return (u32)((func)(a1))(a0);
//}
//STATIC INLINE u32	call_func_0(void*a0){
//	return (u32)((func)(a0))();
//}


//
/*
内部ROM的跳转
loc_80D65BC(void*f);
sub_80D65C0(void*a0,func f);
sub_80D65C4(void*a0,void*a1,func f);
sub_80D65C8(void*a0,void*a1,void*a2,func f);
sub_80D65CC(void*a0,void*a1,void*a2,void*a3,func f);
sub_80D65D0(void*a0,void*a1,void*a2,void*a3,void*a4,func f);
*/

#define call_func_3(a1,a2,a3,a4)	call_func_3((void*)(a1),(void*)(a2),(void*)(a3),(void*)(a4))
#define call_func_2(a1,a2,a3)		call_func_2((void*)(a1),(void*)(a2),(void*)(a3))
#define call_func_1(a1,a2)			call_func_1((void*)(a1),(void*)(a2))
#define call_func_0(a1)			call_func_0((void*)(a1))


//inline static u32 sub_80D65D0_inline(void*a0,void*a1,void*a2,void*a3,void*f){
//	asm volatile(
//			"mov r4,%[ff]\n\t"
//			"b sub_80D65D0\n\t"
//			:[ff]"+r"(f)
//			);
//}
//
//inline static u32 sub_80D65CC_inline(void*a0,void*a1,void*a2,void*f){
//	asm volatile(
//			"mov r3,%[ff]\n\t"
//			"b sub_80D65CC\n\t"
//			:[ff]"+r"(f)
//			);
//}
//
//inline static u32 sub_80D65C8_inline(void*a0,void*a1,void*f){
//	asm volatile(
//			"mov r2,%[ff]\n\t"
//			"b sub_80D65C8\n\t"
//			:[ff]"+r"(f)
//			);
//}
//




#define	ROM_Call_func_4(a0,a1,a2,a3,f)		sub_80D65D0((void*)a0,(void*a1),(void*)a2,(void*)a3,(void*)f);
//#define	ROM_Call_func_3(a0,a1,a2,f)		sub_80D65CC((void*)a0,(void*a1),(void*)a2,(void*)f);
//#define	ROM_Call_func_2(a0,a1,f)			sub_80D65C8((void*)a0,(void*a1),(void*)f);
//#define	ROM_Call_func_1(a0,f)				sub_80D65C0((void*)a0,(void*)f);

//#define	ROM_Call_func_4(a0,a1,a2,a3,f)		sub_80D65D0_inline((void*)a0,(void*a1),(void*)a2,(void*)a3,(void*)f);
//#define	ROM_Call_func_3(a0,a1,a2,f)		sub_80D65CC_inline((void*)a0,(void*a1),(void*)a2,(void*)f);
//#define	ROM_Call_func_2(a0,a1,f)			sub_80D65C8_inline((void*)a0,(void*a1),(void*)f);
//#define	ROM_Call_func_1(a0,f)				sub_80D65C0_inline((void*)a0,(void*)f);


#define ROM_Call_func_goto(a0,f)		/*sub_80D65C0_inline((void*)a0,(void*)f);*/ \
		({void*l=f;goto *l;0;})
		//({__label__ l=f;goto l;0;})

//#define ROM_Call_func_1(a0,f)				ROM_Call_func_1_goto(a0,f)


/*
#define ROM_Call_func_asm(a0,f)		\
		({func _f = (func)(f);u32 _ret;asm(					\
				"bx %[ff]\n\t"			\
				""						\
				:[ret]"=r"(_ret)		\
				:[ff]"r"(_f)			\
		);_ret;})
*/

#define ROM_Call_func_asm(a0,f) \
		({		\
					asm  volatile("ldr r3,=%0": :"X"(f));		\
					asm  volatile("bx r3\n\t"	\
					);					\
			0;})


#ifndef __clang__
//__GNUC__
//#define	ROM_Call_func_4(a0,a1,a2,a3,f)					ROM_Call_func_1_goto(a0,f)
#define	ROM_Call_func_3(a0,a1,a2,f)					ROM_Call_func_goto(a0,f)
#define	ROM_Call_func_2(a0,a1,f)						ROM_Call_func_goto(a0,f)
#define	ROM_Call_func_1(a0,f)							ROM_Call_func_goto(a0,f)

#else
__attribute__((noreturn))
inline   unsigned int ROM_Call_call_inline(void*a0,void*a1,void*a2,void*f){
	register unsigned int (*ff)() asm  volatile("r3") = f;
	asm volatile("bx %[_f]"
			:
			:[_f]"r"(ff)
			);
}


//__CLANG__
#define	ROM_Call_func_3(a0,a1,a2,f)					ROM_Call_call_inline(a0,0,0,f)
#define	ROM_Call_func_2(a0,a1,f)						ROM_Call_call_inline(a0,0,0,f)
#define	ROM_Call_func_1(a0,f)							ROM_Call_call_inline(a0,0,0,f)
#endif


#define ASM_Call(f)		{func __f= (func)(f);\
		asm  volatile("bx %[ff]\n\t"	\
				:[ff]"+r"(__f)			\
					);					\
			}
#define ROM_Call_func_0(f) 	ASM_Call(f)


#endif /* CALL_FUNC_H_ */
