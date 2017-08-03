// FileName: Lock.cpp
//
// Desc:
//
// Created by token.tong at 2017-08-02 11:50:21
#include "Lock.h"

CLock::CLock()
: _locker(NULL)
{
#if defined(KOS_LINUX) || defined(KOS_MACOS)
	_locker = new pthread_mutex_t;
	pthread_mutex_init( _locker, NULL );
#elif defined(KOS_WIN32)
	_locker = new CRITICAL_SECION;
	::InitializeCriticalSection( _locker );
#endif
}

CLock::~CLock()
{
#if defined(KOS_LINUX) || defined(KOS_MACOS)
	pthread_mutex_destroy( _locker );
#elif defined(KOS_WIN32)
	::DeleteCriticalSection( _locker );
#endif
	delete _locker;
	_locker = NULL;
}

void CLock::lock()
{
#if defined(KOS_LINUX) || defined(KOS_MACOS)
	pthread_mutex_lock( _locker );
#elif defined(KOS_WIN32)
	::EnterCriticalSection( _locker );
#endif
}
void CLock::unlock()
{
#if defined(KOS_LINUX) || defined(KOS_MACOS)
	pthread_mutex_unlock( _locker );
#elif defined(KOS_WIN32)
	::LeaveCriticalSection( _locker );
#endif
}
