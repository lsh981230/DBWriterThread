#pragma once
class DBSave
{
public:
	DBSave(char* schemaName);
	~DBSave();

	HANDLE	CreateDBThread();
	void	StopThread() { _bTurnOff = true; }

	void	EnqueueMsg(IQueryMsg* pMsg);
	MYSQL*	DBConnect();

private:
	static UINT WINAPI DBSaveThread(LPVOID);


	// �޼��� ó�� ���� �Լ�

	void	SwitchMsg();




	// DB ���� �Լ�

	void SendQuery(char* pQuery);
	bool ConnectError(int errorNo);

private:

	LockFreeQueue<IQueryMsg*>	_msgQueue;
	

	HANDLE	_hMsgEnQ;

	char*	_schemaName;
	bool	_bTurnOff;

	HANDLE	_hDBThread;

public:
	MYSQL*	_dbLink;
};

