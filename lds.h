/*
 * lds.h
 *
 *  Created on: 2016��3��6��
 *      Author: yami
 */

/**
 * @file	lds.h
 * @author	yami
 * @date	2016��3��6��
 * @brief
 * 
 */


#ifndef LDS_H_
#define LDS_H_

/*
	. = 0x8028E0C;
	.8028E0C :
	{
		*.o(.8028E0C)
	}
 */
#define HackFunc(address)  \
    . = 0x##address;\
    .##address ALIGN(1) : \
    {\
        *.o(.##address);\
        . = ALIGN(0x1);\
    }

#define HackData(address) \
            . = 0x##address;\
            .##address ALIGN(1) : \
            {\
                *.o(.##address);\
                . = ALIGN(0x1);\
            }

#define HackFuncAssert(address,size) \
        HackData(address)\
        ASSERT(SIZEOF(.##address)<=(size),"�޸ĵ����ݹ���������������Ǻ����޸ģ��������Լ������ɵĳ���")

#define HackDataAssert(address,size) \
        HackFunc(address)\
        ASSERT(SIZEOF(.##address)<=(size),"�޸ĵ����ݹ���������������Ǻ����޸ģ��������Լ������ɵĳ���")


#define HackAddress(address) \
    . = address;\
    .##address ALIGN(1) : \
    {\
        *.o(.##address);       \
        . = ALIGN(0x1);     \
    }

#define HackAddressAssert(address,size) \
        HackAddress(address)\
        ASSERT(SIZEOF(.##address)<=(size),"�޸ĵ����ݹ���������������Ǻ����޸ģ��������Լ������ɵĳ���")


#define HackPointer(address) HackData(address)






#endif /* LDS_H_ */
