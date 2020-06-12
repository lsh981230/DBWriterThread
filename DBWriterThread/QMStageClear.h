#pragma once
#include "IQueryMsg.h"
class QMStageClear :
	public IQueryMsg
{
public:
	QMStageClear();
	QMStageClear(char* schemaName, char* tableName) {}
	virtual ~QMStageClear();


	char* CreateQuery(int value) override;
public:

	__int64	iAccountNo;
	int	iStageID;
};

