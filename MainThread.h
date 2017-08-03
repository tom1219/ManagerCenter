// FileName:MainThread.h
//
// Desc:
//
// Created by token.tong at 2017-08-02 10:41:10
#ifndef _MAIN_THREAD_H_
#define _MAIN_THREAD_H_
#include "Utils.h"
#include "sharelib.h"
#include "ThreadBase.h"

class LogCache;
class CMainThread : public CThreadBase
{
public:
	CMainThread();
	~CMainThread();

	bool start();

protected:
	void threadProc();

private:
	int _ep;
	SOCK_T _sock;
	LogCache* _logCache;
};

#endif //_MAIN_THREAD_H_
