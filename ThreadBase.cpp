// FileName: ThreadBase.cpp
//
// Desc:
//
// Created by token.tong at 2017-08-02 10:22:57
#include "ThreadBase.h"

CThreadBase::CThreadBase()
: _stop(false)
, _stopped(false)
{
}

CThreadBase::~CThreadBase()
{
}

bool CThreadBase::start()
{
	_stop = false;
	_stopped = false;
#if defined(KOS_LINUX) || defined(KOS_MACOS)
	pthread_create( &_handle, NULL, threadProcEntry, this );
#elif defined(KOS_WIN32)
	_handle = (THREAD_HANDLE)_beginthreadex( NULL, 0, threadProcEntry, this, 0, NULL );
#else
	return false;
#endif
	return true;
}
void CThreadBase::stop( bool wait )
{
	if ( _stopped )
	{
		return ;
	}
	_stop = true;
	if ( wait )
	{
		waitForStop();
	}
}
void CThreadBase::waitForStop()
{
#if defined(KOS_LINUX) || defined(KOS_MACOS)
	pthread_join(_handle, NULL);
#elif defined(KOS_WIN32)
	WaitForSingleObject( _handle, INFINITE );
#endif
	_stopped = true;
}

#if defined(KOS_LINUX) || defined(KOS_MACOS)
void* CThreadBase::threadProcEntry( void* p )
{
	CThreadBase* pThis = (CThreadBase*)p;
	pThis->threadProc();
	return NULL;
}
#elif defined(KOS_WIN32)
unsigned int __stdcall CThreadBase::threadProcEntry( PVOID p )
{
	CThreadBase* pThis = (CThreadBase*)p;
	pThis->threadProc();
	return 0;
}
#endif
