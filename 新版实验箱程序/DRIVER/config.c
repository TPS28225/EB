#include "config.h"
#include "main.h"
#include "base64.h"

void getUniqueID(char* deviceId)
{
	u8 data[24],i=0;
	
	data[0] = *(vu8*)(0x1fff7a10); 
	data[1] = *(vu8*)(0x1fff7a11); 
	data[2] = *(vu8*)(0x1fff7a12); 
	data[3] = *(vu8*)(0x1fff7a13); 
	data[4] = *(vu8*)(0x1fff7a14); 
	data[5] = *(vu8*)(0x1fff7a15); 
	data[6] = *(vu8*)(0x1fff7a16); 
	data[7] = *(vu8*)(0x1fff7a17); 
	data[8] = *(vu8*)(0x1fff7a18); 
	data[9] = *(vu8*)(0x1fff7a19); 
	data[10] = *(vu8*)(0x1fff7a1A); 
	data[11] = *(vu8*)(0x1fff7a1B); 
	
	for(i=0;i<12;i++)
	{
		data[i+12] = data[i];
	}
	base64_encode((u8*)deviceId, data, 24);
}

