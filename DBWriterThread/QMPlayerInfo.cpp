#include <iostream>
#include "QMPlayerInfo.h"


QMPlayerInfo::QMPlayerInfo()
{
}


QMPlayerInfo::~QMPlayerInfo()
{
}

char * QMPlayerInfo::CreateQuery(int value)
{
	ZeroMemory(_query, sizeof(_query));

	sprintf(_query, "INSERT into %s.%s (value) VALUES %d", _schemaName, _tableName, value);


	return _query;
}
