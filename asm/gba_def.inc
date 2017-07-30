    .macro FUNC fname,address,siz=1,thumb=1
    .if \thumb
        .global \fname
        .code 16
        .thumb_func 
        .type  \fname,%function
        .size  \fname,\siz
        .set   \fname,\address + 1
    .else
        .global \fname
        .code 32
        .type  \fname,%function
        .size  \fname,\siz
        .set   \fname,\address
    .endif
    .endm
    
    .macro HFUNC address,siz=1,thumb=1
        FUNC sub_\address,0x\address,\siz,\thumb
    .endm
    
    .ifdef DD
    .if DD
    HFUNC 80B8C80
    .endif
    .endif
    