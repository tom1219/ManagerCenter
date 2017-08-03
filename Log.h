// FileName:Log.h
//
// Desc:
//
// Created by token.tong at 2017-07-27 17:19:29
#ifndef _LOG_H_
#define _LOG_H_
#include "Utils.h"
#include "sharelib.h"

class CLogPrinter
{
public:
	virtual void logPrint() = 0;
};

class CLog
{
public:
	CLog();
	~CLog();

	void add( const string& s ) { _logs.push_back(s); }
	void print();
	void reset() { _logs.clear(); }
	void setPrinter( CLogPrinter* printer ) { _printer = printer; }
private:
	vector<string> _logs;
	CLogPrinter* _printer;
};

extern CLog _log;

#define LOG_ADD( __log__ ) _log.add( __log__ )
#define LOG_RESET() _log.reset()
#define LOG_SET_PRINTER( __printer__ ) _log.setPrinter( __printer__ )

#endif //_LOG_H_
