#include "sock.h"

SOCK_T Sock::connect( const string& host, WORD port )
{
	SOCK_T sock = INVALID_SOCK;
	do
	{
		hostent* h = gethostbyname( host.data() );
		if ( NULL == h )
		{
			break;
		}

		sockaddr_in addr;
		memset( &addr, 0, sizeof(addr) );
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		memcpy( &(addr.sin_addr), h->h_addr_list[0], h->h_length );

		SOCK_T sock = ::socket( AF_INET, SOCK_STREAM, 0 );
		if ( INVALID_SOCK == sock )
		{
			break;
		}

		if ( SOCK_ERROR == ::connect( sock, (sockaddr*)&addr, sizeof(addr) ) )
		{
			break;
		}

		return sock;
	} while(false);

	if ( INVALID_SOCK != sock )
	{
		close(sock);
	}

	return INVALID_SOCK;
}
SOCK_T Sock::create( const string& host, WORD port )
{
	SOCK_T sock = INVALID_SOCK;
	do
	{
		sockaddr_in addr;
		memset( &addr, 0, sizeof(addr) );
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);

		if ( !host.empty() )
		{
			hostent* h = gethostbyname( host.data() );
			if ( NULL == h )
			{
				break;
			}

			memcpy( &(addr.sin_addr), h->h_addr_list[0], h->h_length );
		}
		else
		{
			addr.sin_addr.s_addr = 0;
		}

		SOCK_T sock = ::socket( AF_INET, SOCK_STREAM, 0 );
		if ( INVALID_SOCK == sock )
		{
			break;
		}

		if ( SOCK_ERROR == ::bind( sock, (sockaddr*)&addr, sizeof(addr) ) )
		{
			break;
		}

		if ( SOCK_ERROR == ::listen( sock, SOMAXCONN ) )
		{
			break;
		}

		return sock;
	} while(false);

	if ( INVALID_SOCK != sock )
	{
		close( sock );
	}

	return INVALID_SOCK;
}

SOCK_T Sock::accept( SOCK_T sock )
{
	return ::accept( sock, NULL, NULL );
}

int Sock::send( SOCK_T sock, const BYTE* data, size_t len )
{
	return ::send( sock, (char*)data, len, 0 );
}
int Sock::recv( SOCK_T sock, string& data )
{
	char szRecv[1024] = {0};
	int ret = ::recv( sock, szRecv, sizeof(szRecv), 0 );
	if ( ret > 0 )
	{
		data.append( (char*)szRecv, ret );
	}

	return ret;
}

void Sock::close( SOCK_T sock )
{
#ifdef WIN32
	::closesocket( sock );
#else
	::close( sock );
#endif
}
