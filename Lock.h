// FileName:Lock.h
//
// Desc:
//
// Created by token.tong at 2017-08-02 11:50:21
#ifndef _LOCK_H_
#define _LOCK_H_
#include "Utils.h"
#include "sharelib.h"

class CLock
{
public:
	CLock();
	~CLock();

	void lock();
	void unlock();

private:
#if defined(KOS_LINUX) || defined(KOS_MACOS)
	pthread_mutex_t* _locker;
#elif defined(KOS_WIN32)
	CRITICAL_SECION* _locker;
#endif
};

#endif //_LOCK_H_
