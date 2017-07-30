/*
 * lds.h
 *
 *  Created on: 2016年3月6日
 *      Author: yami
 */

/**
 * @file	lds.h
 * @author	yami
 * @date	2016年3月6日
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
        ASSERT(SIZEOF(.##address)<=(size),"修改的数据过大，请修正。如果是函数修改，请跳到自己新生成的程序。")

#define HackDataAssert(address,size) \
        HackFunc(address)\
        ASSERT(SIZEOF(.##address)<=(size),"修改的数据过大，请修正。如果是函数修改，请跳到自己新生成的程序。")


#define HackAddress(address) \
    . = address;\
    .##address ALIGN(1) : \
    {\
        *.o(.##address);       \
        . = ALIGN(0x1);     \
    }

#define HackAddressAssert(address,size) \
        HackAddress(address)\
        ASSERT(SIZEOF(.##address)<=(size),"修改的数据过大，请修正。如果是函数修改，请跳到自己新生成的程序。")


#define HackPointer(address) HackData(address)






#endif /* LDS_H_ */
