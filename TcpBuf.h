// FileName:TcpBuf.h
//
// Desc:
//
// Created by token.tong at 2017-08-02 11:50:03
#ifndef _TCP_BUF_H_
#define _TCP_BUF_H_
#include "Utils.h"
#include "sharelib.h"

class CLock;
class CTcpBuf
{
public:
	CTcpBuf();
	~CTcpBuf();

	void add( char* buf, int len );

	int getFreeSize();
	int getDataSize();
	void erase( int size );
	char* getData();

private:
	void expand( int len, bool lock = false );


private:
	CLock* _locker;
	char* _originStart;
	char* _dataStart;
	char* _dataEnd;
	char* _originEnd;
};

#endif //_TCP_BUF_H_
