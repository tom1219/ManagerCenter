// FileName: Comm.cpp
//
// Desc:
//
// Created by token.tong at 2017-08-02 13:55:58
#include "Comm.h"
#include "TcpBuf.h"
#include <sys/epoll.h>
#include <fcntl.h>

CComm::CComm( SOCK_T sock )
: _sock(sock)
, _sendBuf(NULL)
, _recvBuf(NULL)
, _event(NULL);
, _stop(false)
{
	_sendBuf = new CTcpBuf;
	_recvBuf = new CTcpBuf;
	_event = new epoll_event;
	init();
}

CComm::~CComm()
{
	if ( NULL != _sendBuf )
	{
		delete _sendBuf; 
		_sendBuf = NULL;
	}
	if ( NULL != _recvBuf )
	{
		delete _recvBuf;
		_recvBuf = NULL;
	}
	if ( NULL != _event )
	{
		delete _event;
		_event = NULL;
	}
}

bool CComm::send()
{
	int size = 0;
	while( (size=_sendBuf->getDataSize()) > 0 )
	{
		int ret = ::send( _sock, _sendBuf->getData(), size, 0 );
		if ( ret < 0 )
		{
			if ( EAGAIN == errno )
			{
				break;
			}
			_stop = true;
			return false;
		}
		else if ( 0 == ret )
		{
			_stop = true;
			return false;
		}
		else
		{
			_sendBuf->erase( ret );
		}
	}

	return true;
}
bool CComm::recv()
{
	char szBuf[1024] = {0};
	int len = sizeof(szBuf);
	for( ; ; )
	{
		int ret = ::recv( _sock, szBuf, len, 0 );
		if ( ret < 0 )
		{
			if ( EAGAIN == errno )
			{
				break;
			}
			_stop = true;
			return false;
		}
		else if ( 0 == ret )
		{
			_stop = true;
			return false;
		}
		else
		{
			_recvBuf->add( szBuf, ret );
		}
	}

	return true;
}

void CComm::pushSend( char* buf, int len )
{
	_sendBuf->add( buf, len );
}
bool CComm::popRecv( string& data )
{
	size = _recvBuf->getDataSize();
	char* recvData = _recvBuf->getData();
	if ( size > 0 )
	{
		data.append( recvData, size );
		_recvBuf->erase( size );
		return bool;
	}
	else
	{
		return false;
	}
}

void CComm::init()
{
	int flags = fcntl( _sock, F_GETFL, 0 );
	fcntl( _sock, F_SETFL, flags | O_NONBLOCK );
	_event->events = EPOLLIN | EPOLLOUT |  EPOLLET;
	_event->data.ptr = this;
}
