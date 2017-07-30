/*
 * types.h
 *
 *  Created on: 2015年3月9日
 *      Author: yimi
 */

#ifndef TYPES_H_
#define TYPES_H_

#include "hack.h"

#define PACKED __attribute__ ((packed))

#define SECTION(name) 	__attribute__ ((section(name)))
#define SECTION_NAME(name)  SECTION( #name )
#define NORETURN		__attribute__((noreturn))
#define WEAK			__attribute__((weak))
#define ALIAS(name)     __attribute__((alias(name)))
#define HackSym(address)    SECTION_NAME(.##address)
#define Optimize(l)	__attribute__((optimize(l)))
#define HackOpt			Optimize(2) //局部优化ROM Hack函数(优化跳转指令)，从而实现debug c code

#define HACK_SYM(section_name)  __attribute__((unused,section(section_name)))

#define sub(a)		((func)(0x##a + 1))


#define ALIGNED(v) __attribute__ ((aligned (v)))

typedef unsigned char 	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;

typedef signed char 	s8;
typedef signed short	s16;
typedef signed int		s32;


#endif /* TYPES_H_ */
