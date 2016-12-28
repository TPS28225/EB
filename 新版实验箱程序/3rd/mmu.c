#include "mmu.h"
#include "core.h"


__align(8) unsigned char heap[HEAP_SIZE];// __attribute__((at(HEAP_START)));
__align(8) char   swapBuffer[SWAP_BUFF_SIZE];// __attribute__((at(SWAP_BUFF_START)));
__align(8) unsigned char heapIndex[HEAP_INDEX_SIZE];// __attribute__((at(HEAP_INDEX_START)));



void   mmuInit()
{
	memset((void *)(heap), 0, HEAP_SIZE);
	memset((void *)(heapIndex), 0, HEAP_INDEX_SIZE);
}
int count(u8 * indexBuff, int num)
{
	int i, total = 0;
	
	for(i=0;i<num;i++)
	{
		total = total + indexBuff[i];
	}
	
	return total;
}
void * zh_malloc(int size)
{
	int  sizeNeed, blockNeed;
	int  firstBlock, middleBlock, lastBlock;
	
	int  currentCheckIndex = 0;

	
	blockNeed = ((size-1)/ALIGN_NUM) + 1;
	sizeNeed  = blockNeed * ALIGN_NUM; 
 
	while(currentCheckIndex <= (HEAP_INDEX_SIZE-blockNeed))
	{
		if(heapIndex[currentCheckIndex] == 0)
		{
			if(count(&heapIndex[currentCheckIndex], blockNeed) == 0)
			{
				memset(&heapIndex[currentCheckIndex], 1, blockNeed);
				return (void *)(&heap[currentCheckIndex * ALIGN_NUM]);
			}
			else
			{
				currentCheckIndex++;
			}
		}
		else
		{
			currentCheckIndex++;
		}
	}
	return NULL; 
}

void * zh_free(void * buffer, int size)
{
	int  sizeNeed, blockNeed;
	int  firstBlock;
	
	int  currentCheckIndex = 0;

	
	blockNeed = ((size-1)/ALIGN_NUM) + 1;
	
	firstBlock = ((u32)buffer - (u32)heap) / ALIGN_NUM;
	
	memset(&heapIndex[firstBlock], 0, blockNeed);

	return;

	
}