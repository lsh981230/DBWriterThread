#pragma once
#include "IQueryMsg.h"
class QMAccountRegist :
	public IQueryMsg
{
public:
	QMAccountRegist();
	QMAccountRegist(char* schemaName, char* tableName) {}
	virtual ~QMAccountRegist();

	char* CreateQuery(int value) override;


public:

	char	_ID[20];
	char	_password[20];
};

