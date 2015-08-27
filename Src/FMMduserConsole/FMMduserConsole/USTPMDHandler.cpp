///@system	 �������ϵͳ
///@file	 USTPMDHandler.h
///@brief	 apiʵ��
//////////////////////////////////////////////////////////////////////

#include "USTPMDHandler.h"

extern char *INI_FILE_NAME;

CUSTPMDHandler::CUSTPMDHandler(CUstpFtdcMduserApi *pUserApi, char *  number) : m_pUserApi(pUserApi)
{
	strcpy(m_number, number);
	//�ж��Ƿ���Դ������ļ�
	if (!tf.Open(INI_FILE_NAME))
	{
		printf("���ܴ������ļ�<config.ini>\n");
		exit(-1000);
	}
	tf.ReadString(m_number, "OutPutFile", "output.csv", tmp, sizeof(tmp)-1);
	m_pFileOutput = fopen(tmp, "wt");
	tf.ReadString(m_number, "OutPutFile", "output.csv", tmp, sizeof(tmp)-1);
	m_pFileOutput = fopen(tmp, "wt");
}

CUSTPMDHandler::~CUSTPMDHandler()
{
	fclose(m_pFileOutput);
}

// ���ͻ��������鷢��������������ͨ�����ӣ��ͻ�����Ҫ���е�¼
void CUSTPMDHandler::OnFrontConnected()
{
	printf("����������������Ŷ��");

	CUstpFtdcReqUserLoginField reqUserLogin;
	strcpy(reqUserLogin.TradingDay, m_pUserApi->GetTradingDay());
	tf.ReadString(m_number, "BrokerID", "", tmp, sizeof(tmp)-1);
	strcpy(reqUserLogin.BrokerID, tmp);
	tf.ReadString(m_number, "UserID", "", tmp, sizeof(tmp)-1);
	strcpy(reqUserLogin.UserID, tmp);
	tf.ReadString(m_number, "PassWD", "", tmp, sizeof(tmp)-1);
	strcpy(reqUserLogin.Password, tmp);
	strcpy(reqUserLogin.UserProductInfo, "mduserdemo v1.0");
	m_pUserApi->ReqUserLogin(&reqUserLogin, 0);
}

// ���ͻ��������鷢��������ͨ�����ӶϿ�ʱ���÷���������
void CUSTPMDHandler::OnFrontDisconnected()
{
	// ��������������API���Զ��������ӣ��ͻ��˿ɲ�������
	printf("OnFrontDisconnected.\n");
}

void CUSTPMDHandler::OnRspQryTopic(CUstpFtdcDisseminationField *pDissemination, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	printf("OnRspQryTopic: %d ,%d\n", pDissemination->SequenceSeries, pDissemination->SequenceNo);
}

// ���ͻ��˷�����¼����֮�󣬸÷����ᱻ���ã�֪ͨ�ͻ��˵�¼�Ƿ�ɹ�
void CUSTPMDHandler::OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	printf("OnRspUserLogin:\n");
	printf("UserID:[%s] \n", pRspUserLogin->UserID);
	printf("ParticipantID:[%s] \n", pRspUserLogin->BrokerID);
	printf("DataCenterID:[%d] \n", pRspUserLogin->DataCenterID);
	printf("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
	printf("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);

	if (pRspInfo->ErrorID != 0)
	{
		// �˵�ʧ�ܣ��ͻ�������д�����
		printf("Failed to login, errorcode=%d errormsg=%s requestid=%d chain=%d", pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast);
	}

	//���ĺ�Լ��Ϣ
	// 	char* contracts[3]={"","",""};
	// 	contracts[0]="*";
	// 	contracts[1]="IF1212";
	// 	contracts[2]="IF1303";
	//	m_pUserApi->SubMarketData(contracts, 3);
	//��ȡ�����ĵĺ�Լ����
	int subnum = tf.ReadInt(m_number, "SubInsNum", 0);
	char** contracts = new char*[subnum];
	int i = 0;
	char instmp[128];
	for (; i<subnum; i++)
	{
		sprintf(instmp, "SubIns%d", i + 1);
		tf.ReadString(m_number, instmp, "", tmp, sizeof(tmp)-1);
		contracts[i] = new char[strlen(tmp) + 1];
		strncpy(contracts[i], tmp, strlen(tmp) + 1);
		//��ӡ��ȡ���Ķ��ĺ�Լ
		printf("���ĺ�Լ��:%s", contracts[i]);
	}
	//����������Ͷ�������
	m_pUserApi->SubMarketData(contracts, subnum);

	// 	char* uncontracts[3]={"","",""};
	// 	uncontracts[0]="IF1211";
	// 	uncontracts[1]="IF1212";
	// 	uncontracts[2]="IF1303";
	//	m_pUserApi->UnSubMarketData(uncontracts, 3);

	int unsubnum = tf.ReadInt(m_number, "UnSubInsNum", 0);
	char** uncontracts = new char*[unsubnum];
	i = 0;
	for (; i<unsubnum; i++)
	{
		sprintf(instmp, "UnSubIns%d", i + 1);
		tf.ReadString(m_number, instmp, "", tmp, sizeof(tmp)-1);
		uncontracts[i] = new char[strlen(tmp) + 1];
		strncpy(uncontracts[i], tmp, strlen(tmp) + 1);
	}
	m_pUserApi->UnSubMarketData(uncontracts, unsubnum);
}

///�û��˳�Ӧ��
void CUSTPMDHandler::OnRspUserLogout(CUstpFtdcRspUserLogoutField *pRspUserLogout, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	printf("OnRspUserLogout:\n");
	printf("UserID:[%s] \n", pRspUserLogout->UserID);
	printf("ParticipantID:[%s] \n", pRspUserLogout->BrokerID);
	printf("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
	printf("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);
}

// �������֪ͨ�����������������֪ͨ�ͻ���
void CUSTPMDHandler::OnRtnDepthMarketData(CUstpFtdcDepthMarketDataField *pMarketData)
{
	// �ͻ��˰��账���ص�����

	//������Ҫ������д��csv�ļ���
	fprintf(m_pFileOutput, "%s,%s,%d,%d,%d,%d", pMarketData->InstrumentID, pMarketData->UpdateTime, pMarketData->UpdateMillisec,pMarketData->Turnover,pMarketData->Volume,pMarketData->OpenInterest);
	if (pMarketData->AskPrice1 == DBL_MAX)
		fprintf(m_pFileOutput, "%s,", "");
	else
		fprintf(m_pFileOutput, "%f,", pMarketData->AskPrice1);

	if (pMarketData->BidPrice1 == DBL_MAX)
		fprintf(m_pFileOutput, "%s \n", "");
	else
		fprintf(m_pFileOutput, "%f \n", pMarketData->BidPrice1);
	fflush(m_pFileOutput);
}

// ����û�����ĳ���֪ͨ
void CUSTPMDHandler::OnRspError(CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	printf("OnRspError:\n");
	printf("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
	printf("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);
	// �ͻ�������д�����
}

///���ĺ�Լ�������Ϣ
void CUSTPMDHandler::OnRspSubMarketData(CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//printf("Sub ���ض��ĺ�Լ��%s \n", pSpecificInstrument->InstrumentID);
}

///δ���ĺ�Լ�������Ϣ
void CUSTPMDHandler::OnRspUnSubMarketData(CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	//printf("UnSub ���ض��ĺ�Լ��%s \n", pSpecificInstrument->InstrumentID);
}
