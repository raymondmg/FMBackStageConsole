///@brief	 �����н��������飬���沢�ṩ�ͻ��˵Ľ���
///@history 
//////////////////////////////////////////////////////////////////////

#include "profile.h"
#include "USTPMDClient.h"

char *INI_FILE_NAME = "mduserdemo.ini";

int main()
{
	TIniFile tf;
	char tmp[256];
	//�������ļ�����
	if (!tf.Open(INI_FILE_NAME))
	{
		printf("���ܴ������ļ�\n");
		exit(-1000);
	}
	//��������
	int marketnum = tf.ReadInt("COMMON", "MARKETDATANUM", 1);
	int i = 0;
	for (; i<marketnum; i++)
	{
		//��ȡ��ָ���г�����������Ϣ
		sprintf(tmp, "MARKETDATA%d", i + 1);
		CUstpMs ustpMs;
		//��ʼ������ϵͳ
		ustpMs.InitInstance(tmp, INI_FILE_NAME);
	}
	while (true)
	{
		SLEEP_SECONDS(5000);
	}
	return 0;
}