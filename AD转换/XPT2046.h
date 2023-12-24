#include <REGX52.H>

#ifndef __XPT2046_H__
#define __XPT2046_H__





#define XPT2046_VBAT	0xAC
#define XPT2046_AUX		0xEC
#define XPT2046_XP		0x9C	//0xBC
#define XPT2046_YP		0xDC

#define XPT2046_VBAT_12	0xA4
#define XPT2046_AUX_12	0xE4
#define XPT2046_XP_12	0x94
#define XPT2046_YP_12	0xD4

unsigned int XPT2046_readAD(unsigned char command);





#endif