///@brief	 接受中金所的行情，保存并提供客户端的介入
///@history 
//////////////////////////////////////////////////////////////////////

#include "profile.h"
#include "USTPMDClient.h"

char *INI_FILE_NAME = "mduserdemo.ini";

int main()
{
	TIniFile tf;
	char tmp[256];	
	//打开配置文件内容
	if (!tf.Open(INI_FILE_NAME))
	{
		printf("不能打开配置文件\n");
		exit(-1000);
	}
	int marketnum = tf.ReadInt("COMMON","MARKETDATANUM",1);
	int i = 0;
	for(;i<marketnum;i++)
	{
		sprintf(tmp,"MARKETDATA%d",i+1);
		CUstpMs ustpMs;
		ustpMs.InitInstance(tmp,INI_FILE_NAME);
	}
	while(true)
	{
		SLEEP_SECONDS(5000);
	}
	return 0;
}