include gcc-gba.mk
include define.mk


OUT_FILE:= fe7.elf


LDS :=	hack_data.ld
LDFLAGS		+=	-Thack.ld -nostdlib -Map $(OUT_FILE:.elf=.map) 
ASINCLUDE	:=	-I ./s\
				-I ./asm\
				-I ./sound/s


#SRC_DIR := $(CURDIR)
SRC_DIR := ./
DIRS 	:=	$(filter-out %tools,$(shell gnufind $(SRC_DIR) -maxdepth 4 -type d))
CFILES		:=	$(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))
SFILES		:=  $(foreach dir,$(DIRS),$(wildcard $(dir)/*.s))
DEPENDS		:=	$(CFILES:.c=.d)
OBJFILES	:=	$(CFILES:.c=.o) $(SFILES:.s=.o)


all:$(OUT_FILE)

clean:
	-rm $(OBJFILES)
	-rm hack_data.ld
	-rm $(OUT_FILE)
	-rm $(OUT_FILE:.elf=.map) 
	-rm $(DEPENDS)
	

-include $(DEPENDS)
%.o:%.c
	$(CC) $(CFLAGS) -c -MMD -MF"$*.d" $(CURDIR)/$< -o $@


$(OUT_FILE):$(LDS) $(OBJFILES)
	$(LD)  $(LDFLAGS)  $(OBJFILES) -o $@
	$(OBJCOPY) --set-section-flags .rom="r,c,a" $(OUT_FILE)
	
#=========================================================
rom.s:fe7.gba

%.o:%.s
	$(CC) $(CFLAGS) $(ASINCLUDE) -c $< -o $@


#=========================================================
	
#=========================================================
#有关链接脚本的生成

HACK_DATA_HEAD := $(foreach dir,$(DIRS),$(wildcard $(dir)/*.lds.h))

$(LDS):$(LDS:.ld=.h)
	$(CC) -E -P $< -o $@

$(LDS:.ld=.h):$(HACK_DATA_HEAD)
	echo //这个是模块自动创建的链接脚本 > $@
	echo \#include \"lds.h\" >> $@
	for h in $(^);do echo \#include \"$$h\" >> $@;done

#=========================================================