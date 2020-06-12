#pragma once
class DBSave
{
public:
	DBSave(char* schemaName);
	~DBSave();

	HANDLE	CreateDBThread();
	void	StopThread() { _bTurnOff = true; }

	void	EnqueueMsg(IQueryMsg* pMsg);

private:
	static UINT WINAPI DBSaveThread(LPVOID);


	// 메세지 처리 관련 함수

	void	SwitchMsg();




	// DB 관련 함수

	void DBConnect();
	void SendQuery(char* pQuery);
	bool ConnectError(int errorNo);

private:

	LockFreeQueue<IQueryMsg*>	_msgQueue;
	
	MYSQL*	_dbLink;

	HANDLE	_hDBThread;
	HANDLE	_hMsgEnQ;

	char*	_schemaName;
	bool	_bTurnOff;

};

