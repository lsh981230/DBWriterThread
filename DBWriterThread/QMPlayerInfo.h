#pragma once
#include "IQueryMsg.h"
class QMPlayerInfo :	public IQueryMsg
{
public:
	QMPlayerInfo();
	QMPlayerInfo(char* schemaName, char* tableName) {}
	virtual ~QMPlayerInfo();


	char*	CreateQuery(int value) override;


public:

		int	_level;
	__int64	_accountNo;
	__int64 _exp;

};

