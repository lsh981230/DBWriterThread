#pragma once
#include <Windows.h>
class IQueryMsg
{
public:
	IQueryMsg(char* schemaName, char* tableName) : _schemaName(schemaName), _tableName(tableName) {}
	virtual ~IQueryMsg() {}

	virtual char* CreateQuery(int) = 0;

protected:

	char	_query[128];

	char*	_schemaName;
	char*	_tableName;
};

