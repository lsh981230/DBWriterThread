#pragma once

#pragma comment(lib, "mysqlclient.lib")

#include <Windows.h>
#include <iostream>

#include <process.h>

// MYSQL 관련 헤더
#include "mysql.h"
#include "errmsg.h"


// 라이브러리 관련 헤더
#include "CLog.h"
#include "CCrashDump.h"



// 락프리 관련 헤더
#include "LockFreeFreeList.h"
#include "LockFreeQueue.h"


#include "MessageHeader.h"

#include "IQueryMsg.h"

#include "QMAccountRegist.h"
#include "QMPlayerInfo.h"
#include "QMStageClear.h"

#include "DBSave.h"