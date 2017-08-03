// FileName:ThreadBase.h
//
// Desc:
//
// Created by token.tong at 2017-08-02 10:22:57
#ifndef _THREAD_BASE_H_
#define _THREAD_BASE_H_
#include "Utils.h"
#include "sharelib.h"

class CThreadBase
{
public:
	CThreadBase();
	virtual ~CThreadBase();

	virtual bool start();
	virtual void stop( bool wait = true );

	bool isStop() const { return _stop; }
	bool isStopped() const { return _stopped; }

protected:
	virtual void threadProc() {}
	virtual void waitForStop();

private:
#if defined(KOS_LINUX) || defined(KOS_MACOS)
	static void* threadProcEntry( void* p );
#elif defined(KOS_WIN32)
	static unsigned int __stdcall threadProcEntry( PVOID p );
#endif

private:
	THREAD_HANDLE _handle;
	bool _stop;
protected:
	bool _stopped;
};

#endif //_THREAD_BASE_H_
