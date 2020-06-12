#include "HeaderStorage.h"

#include "DBSave.h"

#include "QMAccountRegist.h"
#include "QMPlayerInfo.h"
#include "QMStageClear.h"



void main()
{
	DBSave* pSaveDB = new DBSave((char*)"test_server");


	// DB 저장 쓰레드 생성

	HANDLE hDBSaveThread = pSaveDB->CreateDBThread();

	for (;;)
	{
		// DB 저장 요청
		int randValue = rand() % 3;

		switch (randValue)
		{
		case 0:
		{
			QMAccountRegist* temp = new QMAccountRegist("test_server",);
			pSaveDB->EnqueueMsg(temp);
			break;
		}

		case 1:
		{
			QMPlayerInfo* temp = new QMPlayerInfo();
			pSaveDB->EnqueueMsg(temp);
			break;
		}

		case 2:
		{
			QMStageClear* temp = new QMStageClear();
			pSaveDB->EnqueueMsg(temp);
			break;
		}
		}
	}

	// DB 저장 쓰레드의 종료를 기다림

	pSaveDB->StopThread();
	WaitForSingleObject(hDBSaveThread, INFINITE);
	
}