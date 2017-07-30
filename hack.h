/*
 * hack.h
 *
 *  Created on: 2015年3月10日
 *      Author: yimi
 */

#ifndef HACK_H_
#define HACK_H_

#define HACK_FATE
#define ROM_HACK


#define HACK_ROM_NAME				"Fire Emblem 7"
#define HACK_ROM_HACKNAME			""
#define HACK_ROM_HACKAUTHOR		"yami"
#define HACK_ROM_HACKVERSION		"0.0.1"
#define HACK_ROM_HACKDATE			"2016-12-04 22:00"
#define HACK_ROM_URL				"https://github.com/yami-hack/"
#define	HACK_ROM_EXT				"游戏测试用"

typedef struct{
	unsigned	char	hackDate[0x12];			//2015-10-04 22
	unsigned	char	hackAuthor[0xe];		//yami
	unsigned	char	romname[0x20];			//Fire Emblem 8
	unsigned	char	hackname[0x20];			//soul of fate
	unsigned	char	version[0x10];			//0.0.1
	unsigned	char	url[0x30];				//网址
	unsigned	char	extra[0x40];
}hackinfo;




#endif /* HACK_H_ */
