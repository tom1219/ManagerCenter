#ifndef _UTILS_H_
#define _UTILS_H_
#include "kplatform.h"
#include <string>
#include <map>
#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>
#include <list>


#if defined( KOS_LINUX ) || defined( KOS_MACOS )
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <dirent.h>
#include <assert.h>
typedef char CHAR;
typedef unsigned char BYTE;
typedef short SHORT;
typedef unsigned short WORD;
typedef int INT;
typedef int INT32;
typedef unsigned int DWORD;
typedef unsigned int UINT;
typedef unsigned int UINT32;
typedef long LONG;
typedef long INT64;
typedef unsigned long ULONG;
typedef unsigned long UINT64;
typedef float FLOAT;
typedef void VOID;

typedef int SOCK_T;
#define SOCK_ERROR -1
#define INVALID_SOCK -1

//#define _USE_ICONV

typedef pthread_t THREAD_HANDLE;

#elif defined( KOS_WIN32 )
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#include <direct.h>

typedef SOCKET SOCK_T;
#define SOCK_ERROR SOCKET_ERROR
#define INVALID_SOCK INVALID_SOCKET

typedef HANDLE THREAD_HANDLE;
#endif
using namespace std;

typedef double DOUBLE;
typedef void* POINTER;

const int LEN_CHAR = sizeof(CHAR);
const int LEN_BYTE = sizeof(BYTE);
const int LEN_SHORT = sizeof(SHORT);
const int LEN_WORD = sizeof(WORD);
const int LEN_INT = sizeof(INT);
const int LEN_INT32 = sizeof(INT32);
const int LEN_UINT = sizeof(UINT);
const int LEN_UINT32 = sizeof(UINT32);
const int LEN_DWORD = sizeof(DWORD);
const int LEN_LONG = sizeof(LONG);
const int LEN_INT64 = sizeof(INT64);
const int LEN_ULONG = sizeof(ULONG);
const int LEN_UINT64 = sizeof(UINT64);
const int LEN_FLOAT = sizeof(FLOAT);
const int LEN_DOUBLE = sizeof(DOUBLE);
const int LEN_POINTER = sizeof(POINTER);


#define ASSERT0( __cond__ )\
{\
	bool _cond_ = __cond__;\
	if ( !_cond_ ) _log.print();\
	assert( _cond_ );\
	if ( !_cond_ ) return ;\
}

#define ASSERT1( __cond__, __ret__ )\
{\
	bool _cond_ = __cond__;\
	if ( !_cond_ ) _log.print();\
	assert( _cond_ );\
	if ( !_cond_ ) return __ret__;\
}

#define ASSERTB( __cond__ )\
{\
	bool _cond_ = __cond__;\
	if ( !_cond_ ) _log.print();\
	assert( _cond_ );\
	if ( !_cond_ ) break;\
}

#define BREAK_IF( __cond__ )\
{\
	bool _cond_ = __cond__;\
	if ( !_cond_ ) break;\
}

class Utils
{
public:
	static bool init();
	static bool base64Encode( const string& in, string& out );
	static bool base64Decode( const string& in, string& out );
	static void upperCase( string& s );
	static void lowerCase( string& s );
	static void getMailTime( string& t );
	static vector< string > split( const string& data, const string& s );
	static string replace( const string& data, const string& Old, const string& New );
	static void trimAll( string& tmp );
	static string& trimHead( string& tmp, const char* ext = NULL );
	static string& trimTail( string& tmp, const char* ext = NULL );
	static string getDateTimeString();
	static void mkDir(const string& dir);
	static bool gbk2utf8( const string& inGbk, string& outUtf8 );
	static bool utf82gbk( const string& inUtf8, string& outGbk );
	static const string& ucFirst( string& s );
	static string int2str( int n );
	static long getTickCount();
	static bool getFileList( const string& dir, vector<string>& fileList, const string& suffix );
	static void md5( const string& in, string& out );
	static void backTrace();
	static bool isEmpty( char c );
	static bool isVarStart( char c );
	static bool isVar( char c );
	static bool isValidVar( const string& var );
	static void log( const char* pszLog, ... );
	static bool isNumStart( const string& var );

	template< typename T >
	void swap( T& a, T& b )
	{
		T t = a;
		a = b;
		b = t;
	}

};


#endif //_UTILS_H_
