RPT：
   传感器名称   数据范围    代表含义 
1.    LED         0~100     数值越大,灯亮度越高,0代表关,100代表最大亮度,在RPT中表示LED当前状态
2.    BEEP        0~4       0代表关,1代表报警,234分别表示不同的歌曲(目前支持三首,可以扩展),蜂鸣器可以播放歌曲,在RPT中表示蜂鸣器当前状态
3.  soundSensor   0/1       0代表没有声音/1代表有声音(声音传感器)
4.    lux        0~65535    当前的光照强度,光照强度越大,数值越大(光照传感器,单位lx)            
5.    temp       -273~+∞    表示温度值,单位为摄氏度
6.    humi        0~100     表示湿度值,单位为百分比
7.   motor      -100~100    绝对值表示电机转速百分比,负数代表反转,正数代表正转,在RPT中表示电机当前状态
8.  distance      0~400     表示当前距离,单位为CM,超过400误差较大(超声波测距模块)
9.	ir_state      0-4-5     0,空闲/4,学习中/5,学习完成
    ir_code                 学习到的红外码(只有状态为学习完成的时候才有效)
10.	 human         0/1      0表示无人,1表示有人(人体感应传感器)
11.	 door          0/1      0表示正常,1表示门开(门磁传感器)
12.   key          0/1      0表示按键未按下,1表示按键按下(按键)
13. rfid_id     四个字节    卡片ID
	Card_Operation	0/1/2 	1表示对卡的写入操作（每次写入命令执行后，该位清零）2表示刷卡
	Card_OperationEnable 0/1 1表示将对卡进行一次写值操作，之后该值清零； 
	rfid_data    0-1000     卡片当前余额
	rfid_enable    0/1      卡片当前授权状态
	rfid_ack      字符串    保留  
14.  zigbee       字符串    嵌入式收到该字符串后,不做任何处理通过以太网上报
15.  pm25         >0        当前空气中PM2.5的值                  
16.  hcho         >0        当前空气中甲醛含量
17  ev1527_state  0-4-5     0,空闲/4,学习中/5,学习完成(射频)
    ev1527_code             学习到的红外码(只有状态为学习完成的时候才有效)
	
CMD：
   传感器名称   数据范围    代表含义 
0.    test       1-10       对应当前实验项目,
1.    LED         0~100     数值越大,灯亮度越高,0代表关,100代表最大亮度,在CMD中表示LED要实现的亮度
2.    BEEP        0~4       0代表关,1代表报警,234分别表示不同的歌曲(目前支持三首,可以扩展),蜂鸣器可以播放歌曲,在CMD中表示蜂鸣器要执行的动作
3.   motor      -100~100    绝对值表示电机转速百分比,负数代表反转,正数代表正转,在CMD中表示电机要执行的动作
4.	ir_state    0-1-2-3     0,空闲/1,发送/2,学习/3,取消学习   
    ir_code                 待发送的红外码(只有状态为发送的时候才有用)
5.  rfid_id     四个字节    卡片ID
	rfid_data    0-1000     卡片要写入的余额
	rfid_enable   0/1       卡片要授权状态
	rfid_ack     字符串     保留   
6.  bluetooth     字符串     嵌入式收到该字符串后,不做任何处理通过串口(蓝牙模块)发送出去
7.   zigbee      字符串     嵌入式收到该字符串后,不做任何处理通过串口(zigbee模块)发送出去
8    oled         0-6       用于嵌入式显示图片用,0不做操作/1-6分别对应显示相应序列号的图片
9.	ev1527_state  0-1-2-3     0,空闲/1,发送/2,学习/3,取消学习   
	ev1527_code               待发送的红外码(只有状态为发送的时候才有用)	
	
CMD:服务器向嵌入式发送命令包
{
	"devId":"WgBJAAtRNTMzODQwWgBJAAtRNTMzODQw",
	"type":"cmd",
	"data":{
		"test":1,
		"led":{
			"led1":100,
			"led2":100,
			"led3":100,
			"led4":100,
			"led5":100,
			"led6":100,
			"led7":100,
			"led8":100
		},
		"beep":2,
		"motor":-100,
		"ir":{
			"state":1,  // 0,空闲/1,发送/2,学习/3,取消学习
			"code":"A:9000,B:200,C:500,D:100;ABBCDCDBCDBCDBCDCBBBDCBCBBCBCBDC",
		}
		"rfid":{
			"id":"FF03DC6B",
			"data":10,   //(待写入数据)
			"enable":0,  //授权目标:0未授权/1已授权   门禁实验用
			"Card_State_Operation":1,
			"ack":" "    //保留		 
		}
		"blutooth":"AT+MD",
		"zigbee":"Micheal:Nice to meet you,too.",
		"oled":2,
		"ev1527":{
			"state":2,  // 0,空闲/1,发送/2,学习/3,取消学习
			"code":"aabbcc",
		}		
	}
}

RPT:嵌入式向服务器上报当前状态
{
	"devId":"WgBJAAtRNTMzODQwWgBJAAtRNTMzODQw",
	"type":"rpt",
	"data":{
		"test":1,
		"led":{
			"led1":100,
			"led2":100,
			"led3":100,
			"led4":100,
			"led5":100,
			"led6":100,
			"led7":100,
			"led8":100
		},
		"beep":2,
		"soundSensor":1,
		"lux":257,
		"temp":32,
		"humi":30,
		"motor":-100,
		"distance":382,
		"ir":{
			"state":5,  // 0,空闲/4,学习中/5,学习完成
			"code":"A:9000,B:200,C:500,D:100;ABBCDCDBCDBCDBCDCBBBDCBCBBCBCBDC",
		},
		"human":1,
		"door":1,
		"key":{
			"key1":0,
			"key2":0,
			"key3":0,
			"key4":1
		}
		"rfid":{
			"id":"FF03DC6B",
			"data":10,   //(读到的数据)
			"enable":0,  //授权状态:0未授权/1已授权   门禁实验用
			"ack":""     //保留		 
		}
		"zigbee":"Jack:Nice to meet you!",
		"ev1527":{
			"state":5,  // 0,空闲/4,学习中/5,学习完成
			"code":"aabbcc",
		}		
	}
}