#pragma once

#pragma comment(lib, "mysqlclient.lib")

#include <Windows.h>
#include <iostream>

#include <process.h>

// MYSQL ���� ���
#include "mysql.h"
#include "errmsg.h"


// ���̺귯�� ���� ���
#include "CLog.h"
#include "CCrashDump.h"



// ������ ���� ���
#include "LockFreeFreeList.h"
#include "LockFreeQueue.h"


#include "MessageHeader.h"

#include "IQueryMsg.h"

#include "QMAccountRegist.h"
#include "QMPlayerInfo.h"
#include "QMStageClear.h"

#include "DBSave.h"