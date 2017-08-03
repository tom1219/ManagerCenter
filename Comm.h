// FileName:Comm.h
//
// Desc:
//
// Created by token.tong at 2017-08-02 13:55:58
#ifndef _COMM_H_
#define _COMM_H_
#include "Utils.h"
#include "sharelib.h"

class CTcpBuf;
struct epoll_event;
class CComm
{
public:
	CComm( SOCK_T sock );
	~CComm();

	epoll_event* getEvent() { return _event; }
	SOCK_T getSock() const { return _sock; }
	bool isStop() const { return _stop; }
	void setStop( bool stop ) { _stop = stop; }

	bool send();
	bool recv();

	void pushSend( char* buf, int len );
	bool popRecv( string& data );

private:
	void init();

private:
	SOCK_T _sock;
	CTcpBuf* _sendBuf;
	CTcpBuf* _recvBuf;
	epoll_event* _event;
	bool _stop;
};

#endif //_COMM_H_
