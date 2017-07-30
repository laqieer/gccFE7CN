/*
 * texts.c
 *
 *  Created on: 2015年4月21日
 *      Author: yami
 */



/**
 * @file		texts.c
 * @author		yami
 * @date		2015-04-21 16:01:17
 * @brief
 * 有关文本的修改
 * 要GBK保存
 */



#include "../types.h"


const u32			texts[] = {
//使用新的方法，texts[index] == 0 ，则使用ROM内部的指针
//#include "fe7jp.h"
//#include "fe7text.h"
		[0x01B4] =  (u32)"测试"+0x80000000,
		[0x0471] =  (u32)"伤药"+0x80000000,
		[0x04E6]	=	 (u32)"琳"+0x80000000,
};

const u32 texts_size = sizeof(texts)>>2;
