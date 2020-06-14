#include "HeaderStorage.h"


QMStageClear::QMStageClear()
{
}

QMStageClear::QMStageClear(char * schemaName, char * tableName)
{
	_value = 0;
	_schemaName = schemaName;
	_tableName = tableName;
}


QMStageClear::~QMStageClear()
{
}


char * QMStageClear::CreateQuery()
{
	ZeroMemory(_query, sizeof(_query));

	sprintf_s(_query, "INSERT into %s.%s (value) VALUES (%d)", _schemaName, _tableName, ++_value);


	return _query;
}
