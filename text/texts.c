/*
 * texts.c
 *
 *  Created on: 2015��4��21��
 *      Author: yami
 */



/**
 * @file		texts.c
 * @author		yami
 * @date		2015-04-21 16:01:17
 * @brief
 * �й��ı����޸�
 * ҪGBK����
 */



#include "../types.h"


const u32			texts[] = {
//ʹ���µķ�����texts[index] == 0 ����ʹ��ROM�ڲ���ָ��
//#include "fe7jp.h"
//#include "fe7text.h"
		[0x01B4] =  (u32)"����"+0x80000000,
		[0x0471] =  (u32)"��ҩ"+0x80000000,
		[0x04E6]	=	 (u32)"��"+0x80000000,
};

const u32 texts_size = sizeof(texts)>>2;
