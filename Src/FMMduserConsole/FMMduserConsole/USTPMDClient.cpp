///@system	 �����������ϵͳ
///@company  �Ϻ������ڻ���Ϣ�������޹�˾
///@file	 CUstpMs
///@brief	 ���ܷ���ϵͳ������
///@history 
///20130502: ���һ� ����
//////////////////////////////////////////////////////////////////////

#include "USTPMDClient.h"

//��ʼ������ϵͳ
bool CUstpMs::InitInstance(char *  number, char * inifile)
{
	char tmp[200];
	strcpy(m_number, number);
	//	CConfig *pConfig = 	new CConfig(INI_FILE_NAME);	
	TIniFile tf;
	//�鿴�Ƿ���Դ������ļ�
	if (!tf.Open(inifile))
	{
		printf("���ܴ������ļ�\n");
		exit(-1000);
	}

	// ����һ��CFfexFtdcMduserApiʵ��
	pUserApi = CUstpFtdcMduserApi::CreateFtdcMduserApi();
	// ����һ���¼������ʵ��
	sh = new CUSTPMDHandler(pUserApi, m_number);
	// ע��һ�¼������ʵ��
	pUserApi->RegisterSpi(sh);
	// ע����Ҫ�������������
	/// USTP_TERT_RESTART:�ӱ������տ�ʼ�ش�
	/// USTP_TERT_RESUME:���ϴ��յ�������
	/// USTP_TERT_QUICK:�ȴ��͵�ǰ�������,�ٴ��͵�¼���г����������

	//��ȡ�����ļ�����
	int topicid = tf.ReadInt(m_number, "Topic", 100);
	//��������ķ�ʽ
	int tert = tf.ReadInt(m_number, "TERT", 0);

	switch (tert)
	{
	case 0:
	{
			  pUserApi->SubscribeMarketDataTopic(topicid, USTP_TERT_RESTART);
			  break;
	}
	case 1:
	{
			  pUserApi->SubscribeMarketDataTopic(topicid, USTP_TERT_RESUME);
			  break;
	}
	case 2:
	{
			  pUserApi->SubscribeMarketDataTopic(topicid, USTP_TERT_QUICK);
			  break;
	}
	default:
	{
			   printf("���� TERT ֵ����! \n");
			   exit(-1);
	}
	}

	// �������鷢���������ĵ�ַ

	tf.ReadString(m_number, "MDFrontAdd", "", tmp, sizeof(tmp)-1);
	mytrim(tmp);
	pUserApi->RegisterFront(tmp);
	// ʹ�ͻ��˿�ʼ�����鷢����������������
	int a = 0;
	int b = 0;
	printf(pUserApi->GetVersion(a, b));
	//	pUserApi->SetHeartbeatTimeout(300);
	pUserApi->Init();
	// �ȴ��������
	//	pUserApi->Join();
	// �ͷ�useapiʵ��
	//	pUserApi->Release();

	return true;
}

void CUstpMs::ExitInstance()
{
	pUserApi->Release();
	delete sh;
}
