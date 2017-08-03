// FileName: MainThread.cpp
//
// Desc:
//
// Created by token.tong at 2017-08-02 10:41:10
#include "MainThread.h"
#include "LogCache.h"
#include <sys/epoll.h>
#include <fcntl.h>
#include "sock.h"

const int MAX_EPOLL = 10240;
const int MAX_FD = 1000;
const int PORT = 5656;

CMainThread::CMainThread()
: _ep(0)
{
}

CMainThread::~CMainThread()
{
}

bool CMainThread::start()
{
	_logCache = new CLogCache();
	_ep = epoll_create( MAX_EPOLL );
	_sock = Sock::create( "", PORT );
	ASSERT1( INVALID_SOCK != _sock, false );
	int flags = fcntl( _sock, F_GETFL, 0 );
	fcntl( _sock, F_SETFL, flags | O_NONBLOCK );
	epoll_event* event = new epoll_event;
	event->events = EPOLLIN | EPOLLOUT |  EPOLLET;
	event->data.ptr = this;
	epoll_ctl( _ep, EPOLL_CTL_ADD, _sock, event );
	return CThreadBase::start();
}

void CMainThread::threadProc()
{
	LogCache& log = *_logCache;
	epoll_event arrEvent[MAX_FD];
	do
	{
		log.clear();
		int ret = epoll_wait( _ep, arrEvent, MAX_FD, 0 );
		for ( int i=0; i<ret; ++i )
		{
			int events = arrEvent[i].events;

			CComm* comm = (CComm*)arrEvent[i].data.ptr;
			if ( events & EPOLLIN )
			{
				comm->recv();
			}

			if ( events & EPOLLOUT )
			{
				comm->send();
			}

			if ( events & EPOLLERR )
			{
				comm->setStop(true);
			}

			if ( comm->isStop() )
			{
				epoll_ctl( _ep, EPOLL_CTL_DEL, comm->getSock(), &(arrEvent[i]) );
			}
		}
	} while( !_stop );
}
