/*

 */

#ifndef  _UCOSII_PORTS_UCOSII_CFG_H_
#define  _UCOSII_PORTS_UCOSII_CFG_H_

//用户可用的最低优先级
#define		OS_USER_PRIO_LOWEST		(OS_LOWEST_PRIO-4)

//用户可用的最高优先级
#define		OS_USER_PRIO_HIGHEST	4

//获取优先级
#define		OS_USER_PRIO_GET(N)		(OS_USER_PRIO_HIGHEST+N)



#endif
