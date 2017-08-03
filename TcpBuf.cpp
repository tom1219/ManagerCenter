// FileName: TcpBuf.cpp
//
// Desc:
//
// Created by token.tong at 2017-08-02 11:50:03
#include "TcpBuf.h"
#include "Lock.h"

const int STEP_SIZE = 1024*1024;

CTcpBuf::CTcpBuf()
: _originStart(NULL)
, _dataStart(NULL)
, _dataEnd(NULL)
, _originEnd(NULL)
{
	_locker = new CLock();
}

CTcpBuf::~CTcpBuf()
{
	if ( NULL != _locker )
	{
		delete _locker;
		_locker = NULL;
	}
}

void CTcpBuf::add( char* buf, int len )
{
	_locker->lock();
	while ( getFreeSize() < len )
	{
		expand( len, false );
	}
	memcpy( _dataEnd, buf, len );
	_dataEnd += len;
	_locker->unlock();
}

int CTcpBuf::getFreeSize()
{
	return ( _originEnd - _dataEnd );
}
int CTcpBuf::getDataSize()
{
	return ( _dataEnd - _dataStart );
}
void CTcpBuf::erase( int size )
{
	_locker->lock();
	int curSize = getDataSize();
	int eraseSize = curSize>size?size:curSize;
	_dataStart += eraseSize;
	if ( 0 == getDataSize() )
	{
		_dataStart = _originStart;
		_dataEnd = _dataStart;
	}
	_locker->unlock();
}
char* CTcpBuf::getData()
{
	return _dataStart;
}

void CTcpBuf::expand( int len, bool lock )
{
	if ( lock )
	{
		_locker->lock();
	}

	int dataSize = getDataSize();
	int total = _originEnd - _originStart;
	int left = total - getDataSize();
	if ( left >= len )
	{
		memmove( _originStart, _dataStart, dataSize );
		_dataStart = _originStart;
		_dataEnd = _dataStart + dataSize;
	}
	else
	{
		char* buf = new char[total+STEP_SIZE];
		if ( dataSize > 0 )
		{
			memcpy( buf, _dataStart, dataSize );
		}
		delete [] _originStart;
		_originStart = buf;
		_dataStart = _originStart;
		_dataEnd = _dataStart + dataSize;
		_originEnd = _originStart + total + STEP_SIZE;
	}
}
