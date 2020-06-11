#pragma once
class DBSave
{
public:
	DBSave();
	~DBSave();

	HANDLE	CreateDBThread();
	void	StopThread() { _bTurnOff = true; }

private:
	static UINT WINAPI DBSaveThread(LPVOID);


	// �޼��� ó�� ���� �Լ�

	void	SwitchMsg();

	void	MsgProc_NewAccount(CSerializeBuffer*);
	void	MsgProc_StageClear(CSerializeBuffer*);
	void	MsgProc_PlayerInfo(CSerializeBuffer*);



	// DB ���� �Լ�

	void DBConnect();
	void SendQuery(char* pQuery);
	void ConnectError(int errorNo);

private:

	LockFreeQueue<CSerializeBuffer*>	_msgQueue;
	
	MYSQL*	_dbLink;

	HANDLE	_hDBThread;
	HANDLE	_hMsgEnQ;

	bool	_bTurnOff;


};


// �ش� Ŭ������ ���� DB �����常�� �����ϴ� �ڵ��, ��Ƽ������� ���� ��� ���� �߻�
