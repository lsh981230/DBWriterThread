#include <iostream>
#include "QMAccountRegist.h"


QMAccountRegist::QMAccountRegist()
{
}


QMAccountRegist::~QMAccountRegist()
{
}

char * QMAccountRegist::CreateQuery(int value)
{
	ZeroMemory(_query, sizeof(_query));

	sprintf(_query, "INSERT into %s.%s (value) VALUES %d", _schemaName, _tableName, value);


	return _query;
}
