#include "HeaderStorage.h"




void main()
{
	CLog::Init();
	DBSave* pSaveDB = new DBSave((char*)"test_server");

	// DB 연결

	MYSQL temp = *(pSaveDB->DBConnect());



	// DB 저장 쓰레드 생성

	HANDLE hDBSaveThread = pSaveDB->CreateDBThread();

	for (;;)
	{
		// DB 저장 요청
		int randValue = rand() % 3;

		void* pData = malloc(sizeof(QMAccountRegist));		// 가장 큰 사이즈의 클래스(그냥 상수로 사이즈 입력해도 상관없음)

		ZeroMemory(pData, sizeof(QMAccountRegist));

		*pSaveDB->_dbLink = temp;

		switch (randValue)
		{
		case 0:
		{
			pData = new (pData)QMAccountRegist((char*)"test_server", (char*)"account");
			pSaveDB->EnqueueMsg((QMAccountRegist*)pData);
			break;
		}

		case 1:
		{
			pData = new (pData)QMPlayerInfo((char*)"test_server", (char*)"player");
			pSaveDB->EnqueueMsg((QMPlayerInfo*)pData);
			break;
		}

		case 2:
		{
			pData = new (pData)QMStageClear((char*)"test_server", (char*)"stage");
			pSaveDB->EnqueueMsg((QMStageClear*)pData);
			*pSaveDB->_dbLink = temp;
			break;
		}
		}

		Sleep(1000000);
	}

	// DB 저장 쓰레드의 종료를 기다림

	pSaveDB->StopThread();
	WaitForSingleObject(hDBSaveThread, INFINITE);
	
}