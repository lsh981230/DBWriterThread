#include "HeaderStorage.h"
#include "DBSave.h"


DBSave::DBSave()
{
	_bTurnOff = false;
}


DBSave::~DBSave()
{
}






HANDLE DBSave::CreateDBThread()
{
	_hDBThread = (HANDLE)_beginthreadex(NULL, 0, DBSaveThread, this, 0, nullptr);

	return _hDBThread;
}








UINT __stdcall DBSave::DBSaveThread(LPVOID arg)
{
	DBSave* pThis = (DBSave*)arg;



	for(;;)
	{
		WaitForSingleObject(pThis->_hMsgEnQ, INFINITE);



		while (pThis->_msgQueue.GetQueueSize() > 0)
		{

			// Message 처리			
			pThis->SwitchMsg();
		}



		// 종료 조건
		if (pThis->_msgQueue.GetQueueSize() <= 0 && pThis->_bTurnOff)
			break;
	}


	return 0;
}







void DBSave::SwitchMsg()
{
	//--------------------------------------------------------
	// 1. MsgQueue에서 Dequeue
	//--------------------------------------------------------

	CSerializeBuffer* pMsg = nullptr;
	if (!_msgQueue.Dequeue(&pMsg))
	{
		CLog::Log(L"DB", CLog::LEVEL_ERROR, L"Dequeue Failed");
		CCrashDump::Crash();
	}



	//--------------------------------------------------------
	// 2. 직렬화버퍼에서 헤더부분만 Dequeue
	//--------------------------------------------------------

	st_DBQUERY_HEADER header;
	pMsg->GetData((char*)&header, sizeof(st_DBQUERY_HEADER));

	

	//--------------------------------------------------------
	// 3. Type에 따라 분리
	//--------------------------------------------------------

	switch (header.Type)
	{
	case df_DBQUERY_MSG_NEW_ACCOUNT:
	{
		MsgProc_NewAccount(pMsg);
		break;
	}

	case df_DBQUERY_MSG_STAGE_CLEAR:
	{
		MsgProc_StageClear(pMsg);
		break;
	}

	case df_DBQUERY_MSG_PLAYER:
	{
		MsgProc_PlayerInfo(pMsg);
		break;
	}

	default:
		CLog::Log(L"DB", CLog::LEVEL_ERROR, L"Defalut Type of Header, SwitchMsg()");
		CCrashDump::Crash();
	}


}





void DBSave::MsgProc_NewAccount(CSerializeBuffer * pMsg)
{
	char query[] = "UPDATE test_server.account SET value = value + 1";

	SendQuery(query);
}

void DBSave::MsgProc_StageClear(CSerializeBuffer * pMsg)
{
	char query[] = "UPDATE test_server.stage SET value = value + 1";

	SendQuery(query);
}

void DBSave::MsgProc_PlayerInfo(CSerializeBuffer * pMsg)
{
	char query[] = "UPDATE test_server.player SET value = value + 1";

	SendQuery(query);
}




void DBSave::DBConnect()
{
	MYSQL conn;


	// 초기화
	mysql_init(&conn);


	// DB 연결
	_dbLink = mysql_real_connect(&conn, "127.0.0.1", "root", "root", "test_server", 3306, (char *)NULL, 0);
	if (_dbLink == NULL)
	{	
		CLog::Log(L"DB", CLog::LEVEL_ERROR, L"Mysql connection error : %s", mysql_error(&conn));
		CCrashDump::Crash();
	}
}




void DBSave::SendQuery(char * pQuery)
{
	int queryRes = mysql_query(_dbLink, pQuery);
	if (queryRes != 0)
	{

	}

}
