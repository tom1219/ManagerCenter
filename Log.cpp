// FileName: Log.cpp
//
// Desc:
//
// Created by token.tong at 2017-07-27 17:19:29
#include "Log.h"

CLog _log;

CLog::CLog()
: _printer(NULL)
{
}

CLog::~CLog()
{
}

void CLog::print()
{
	if ( NULL != _printer )
	{
		_printer->logPrint();
	}
	for ( size_t i=0; i<_logs.size(); ++i )
	{
		cout<<_logs[i]<<endl;
	}
	_logs.clear();
}
