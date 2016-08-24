#include "parser.h"
#include "stdlib.h"
#include "string.h"
#include "main.h"

void revParser(char *msg,int len)
{	
	if(strncmp(msg,"LED",3)==0)
	{
		ledParser(msg+4);
	}
	else if(strncmp(msg,"Beep",3)==0)
	{
	}
	else if(strncmp(msg,"RESET",5)==0)
	{
		__set_FAULTMASK(1); 
		NVIC_SystemReset();
	}
}

void ledParser(char *msg)
{	
	int tempNumber;
	
	if(strncmp(msg,"ON",2)==0)
	{
		ledConfig.ledState = 1;
	}
	else if(strncmp(msg,"OFF",3)==0)
	{
		ledConfig.ledState = 2;
	}
	else if(strncmp(msg,"AUTO",4)==0)
	{
		ledConfig.ledState = 3;
	}
	else if(strncmp(msg,"MANL",4)==0)
	{
		tempNumber = getNumber(msg+5);
		if(tempNumber<0 || tempNumber>1000)
		{
			return;
		}
		else
		{
			ledConfig.ledState = 4;
			ledConfig.ledPersent = tempNumber;
			ledConfig.ledTime = ledConfig.ledPersent;			
		}
	}
}
int getNumber(char * msg)
{
	char temp[5];
	
	strncpy(temp,msg,4);
	temp[4]='\0';
	return atoi(temp);
}
