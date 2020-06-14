#pragma once
class DBSave
{
public:
	DBSave(char* schemaName);
	~DBSave();

	HANDLE	CreateDBThread();
	void	StopThread() { _bTurnOff = true; }

	void	EnqueueMsg(IQueryMsg* pMsg);
	void	DBConnect();

private:
	static UINT WINAPI DBSaveThread(LPVOID);


	// 메세지 처리 관련 함수

	void	SwitchMsg();




	// DB 관련 함수

	void SendQuery(char* pQuery);
	bool ConnectError(int errorNo);

private:

	LockFreeQueue<IQueryMsg*>	_msgQueue;
	

	HANDLE	_hMsgEnQ;

	char*	_schemaName;
	bool	_bTurnOff;

	HANDLE	_hDBThread;
	MYSQL*	_dbLink;
};

