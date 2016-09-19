#ifndef _parserJSON_H_
#define _parserJSON_H_
typedef enum{	
	RPT,
	REG,
	LOGIN,
	PONG
}Jason_Funtype;
char * makeJson(Jason_Funtype function);
void parserJson(char * pMsg);
#endif

