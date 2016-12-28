#ifndef __BASE64_H
#define __BASE64_H	 
#include "sys.h"


u8 base64_encode(u8* dest,u8* src, u8 src_len);
u8 base64_decode(u8* dest,u8* src, u8 src_len);
u16 Get_Crc16(u8 *puchMsg,u16 usDataLen);


extern u8 Led1_Flag;
#endif
