#define addfunction(addr,size,type) u32 sub_##addr();  //addr size type
#pragma long_calls
#include "../fe7.func.list"
#pragma long_calls_off