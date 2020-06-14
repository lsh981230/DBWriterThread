#include "HeaderStorage.h"




DBSave::DBSave(char * schemaName) : _schemaName(schemaName)
{
	_bTurnOff = false;
	_hMsgEnQ = CreateEventA(NULL, false, false, nullptr);
}



DBSave::~DBSave()
{
	printf("A");
}






HANDLE DBSave::CreateDBThread()
{

	_hDBThread = (HANDLE)_beginthreadex(NULL, 0, DBSaveThread, this, 0, nullptr);

	return _hDBThread;
}




void DBSave::EnqueueMsg(IQueryMsg * pMsg)
{
	_msgQueue.Enqueue(pMsg);
	SetEvent(_hMsgEnQ);
}








UINT __stdcall DBSave::DBSaveThread(LPVOID arg)
{
	DBSave* pThis = (DBSave*)arg;



	for (;;)
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


	// DB와 연결종료
	mysql_close(pThis->_dbLink);

	return 0;
}







void DBSave::SwitchMsg()
{

	//--------------------------------------------------------
	// 1. MsgQueue에서 Dequeue
	//--------------------------------------------------------

	IQueryMsg* pMsg = nullptr;
	if (!_msgQueue.Dequeue(&pMsg))
	{
		CLog::Log(L"DB", CLog::LEVEL_ERROR, L"Dequeue Failed");
		CCrashDump::Crash();
	}



	//--------------------------------------------------------
	// 2. Query 생성
	//--------------------------------------------------------

	
	char* pQuery = pMsg->CreateQuery();



	//--------------------------------------------------------
	// 3. Query 전송
	//--------------------------------------------------------

	SendQuery(pQuery);

}



void DBSave::DBConnect()
{
	MYSQL conn;


	// 초기화
	_dbLink = mysql_init(&conn);


	// DB 연결
	_dbLink = mysql_real_connect(&conn, "127.0.0.1", "root", "root", "test_server", 3306, (char *)NULL, 0);
	if (_dbLink == NULL)
	{
		fprintf(stderr, "ERROR : %s", mysql_error(&conn));
		CLog::Log(L"DB", CLog::LEVEL_ERROR, L"Mysql connection error : %s", mysql_error(&conn));
		CCrashDump::Crash();
	}
}




void DBSave::SendQuery(char * pQuery)
{
	int queryRes = mysql_query(_dbLink, pQuery);

	if (queryRes != 0)
	{
		if (ConnectError(mysql_errno(_dbLink)))
		{
			mysql_query(_dbLink, pQuery);
		}

		else
		{
			CLog::Log(L"DB", CLog::LEVEL_ERROR, L"Failed to Reconnect");
			CCrashDump::Crash();
		}

	}
}


bool DBSave::ConnectError(int errorNo)
{
	CLog::Log(L"DB", CLog::LEVEL_WARNING, L"MYSQL Connection has closed, Error No : %d", errorNo);

	// Try Reconnect
	if (errorNo == CR_SOCKET_CREATE_ERROR
		|| errorNo == CR_CONNECTION_ERROR
		|| errorNo == CR_CONN_HOST_ERROR
		|| errorNo == CR_SERVER_GONE_ERROR
		|| errorNo == CR_SERVER_HANDSHAKE_ERR
		|| errorNo == CR_SERVER_LOST
		|| errorNo == CR_INVALID_CONN_HANDLE)
	{

		for (int i = 0; i < 20; i++)
		{
			if (mysql_ping(_dbLink) == 0)
			{
				return true;
			}
		}


	}

	return false;
}
