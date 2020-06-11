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


	// 메세지 처리 관련 함수

	void	SwitchMsg();

	void	MsgProc_NewAccount(CSerializeBuffer*);
	void	MsgProc_StageClear(CSerializeBuffer*);
	void	MsgProc_PlayerInfo(CSerializeBuffer*);



	// DB 관련 함수

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


// 해당 클래스는 단일 DB 쓰레드만을 지원하는 코드로, 멀티쓰레드로 돌릴 경우 문제 발생
