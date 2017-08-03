#include "Utils.h"
#include <vector>
#include <algorithm>
#include <stdio.h>
#if defined(KOS_LINUX) || defined(KOS_MACOS)
#ifdef _USE_ICONV
#include <iconv.h>
#endif
#include <execinfo.h>
#include <stdarg.h>
#endif
using namespace std;

vector<unsigned char> _encodeTable;
vector<unsigned char> _decodeTable(128);

bool Utils::init()
{
	for ( unsigned char i='A'; i<='Z'; ++i )
	{
		_encodeTable.push_back(i);
	}
	for ( unsigned char i='a'; i<='z'; ++i )
	{
		_encodeTable.push_back(i);
	}
	for ( unsigned char i='0'; i<='9'; ++i )
	{
		_encodeTable.push_back(i);
	}
	_encodeTable.push_back('+');
	_encodeTable.push_back('/');
	_encodeTable.push_back('=');

	for ( size_t i=0; i<_encodeTable.size(); ++i )
	{
		_decodeTable[_encodeTable[i]] = i;
	}

	return true;
}

bool Utils::base64Encode( const string& in, string& out )
{
	if ( in.empty() )
	{
		out.clear();
		return true;
	}

	int inputLen = in.size()/3 * 3;
	int left = in.size()%3;
	int i = 0;
	for ( i = 0; i < inputLen; i += 3 )
	{
		out += _encodeTable[in[i]>>2];
		out += _encodeTable[((in[i] & 0x03) << 4 ) | (in[i+1] >> 4 )];
		out += _encodeTable[((in[i+1] & 0xf) << 2 ) | ((in[i+2] & 0xc0) >> 6)];
		out += _encodeTable[in[i+2] & 0x3f];
	}

	switch( left )
	{
		case 1:
			out += _encodeTable[in[i]>>2];
			out += _encodeTable[(in[i] & 0x3) << 4];
			out += _encodeTable[_encodeTable.size()-1];
			out += _encodeTable[_encodeTable.size()-1];
			break;

		case 2:
			out += _encodeTable[in[i]>>2];
			out += _encodeTable[((in[i] & 0x3)<<4) | (in[i+1]>>4)];
			out += _encodeTable[((in[i+1] & 0xf) << 2)];
			out += _encodeTable[_encodeTable.size()-1];
			break;

		default:
			break;
	}

	return true;
}
bool Utils::base64Decode( const string& in, string& out )
{
	int decodeLen = (in.size()>>2)*3;
	for ( size_t i=in.size(); i>0; --i )
	{
		if ( in[i-1] == _encodeTable[_encodeTable.size()-1] )
		{
			--decodeLen;
		}
		else
		{
			break;
		}
	}

	int outLen = decodeLen/3 * 3;
	int left = decodeLen%3;
	int i = 0;
	int j = 0;
	for ( i = 0,j = 0; i < outLen; i += 3, j += 4 )
	{
		out += (_decodeTable[in[j]] << 2) | (_decodeTable[in[j+1]] >> 4);
		out += (_decodeTable[in[j+1]] << 4) | (_decodeTable[in[j+2]] >> 2);
		out += (_decodeTable[in[j+2]] << 6) | _decodeTable[in[j+3]];
	}

	switch( left )
	{
		case 1:
			out += (_decodeTable[in[j]] <<2) | (_decodeTable[in[j+1]] >>4 );
			break;

		case 2:
			out += (_decodeTable[in[j]] << 2) | (_decodeTable[in[j+1]] >> 4);
			out += (_decodeTable[in[j+1]] << 4) | (_decodeTable[in[j+2]] >> 2);
			break;

		default:
			break;
	}

	return true;
}

void Utils::upperCase( string& s )
{
	transform( s.begin(), s.end(), s.begin(), (int (*)(int))toupper );
}
void Utils::lowerCase( string& s )
{
	transform( s.begin(), s.end(), s.begin(), (int (*)(int))tolower );
}

void Utils::getMailTime( string& s )
{
	time_t t = time(NULL);
	tm tm;
	localtime_r( &t, &tm );

	vector<string> week;
	week.push_back( "Sun" );
	week.push_back( "Mon" );
	week.push_back( "Tue" );
	week.push_back( "Wed" );
	week.push_back( "Thu" );
	week.push_back( "Fri" );
	week.push_back( "Sat" );

	vector<string> month;
	month.push_back( "Jan" );
	month.push_back( "Feb" );
	month.push_back( "Mar" );
	month.push_back( "Apr" );
	month.push_back( "May" );
	month.push_back( "Jun" );
	month.push_back( "Jul" );
	month.push_back( "Aug" );
	month.push_back( "Sep" );
	month.push_back( "Oct" );
	month.push_back( "Nov" );
	month.push_back( "Dec" );

	char szTemp[1024] = {0};
	sprintf( szTemp, "%s, %02d %s %04d %02d:%02d:%02d %s%02ld",
			week[tm.tm_wday].data(),
			tm.tm_mday,
			month[tm.tm_mon].data(),
			tm.tm_year+1900,
			tm.tm_hour,
			tm.tm_min,
			tm.tm_sec,
			tm.tm_gmtoff>=0?"+":"-",
			tm.tm_gmtoff/3600 );
	s = szTemp;
}

vector< string > Utils::split( const string& data, const string& s )
{
	vector< string > v;
	size_t n = 0;
	size_t m = 0;
	n = data.find( s, m );
	while( string::npos != n )
	{
		string tmp = data.substr( m, n-m );
		m = n + s.size();
		n = data.find( s, m );
		v.push_back( tmp );
	}

	if ( m < data.size() )
	{
		v.push_back( data.substr( m, data.size()-m ) );
	}

	return v;
}

string Utils::replace( const string& data, const string& Old, const string& New )
{
	string ret;
	size_t n = 0;
	size_t m = 0;
	n = data.find( Old, m );
	while( string::npos != n )
	{
		string tmp = data.substr( m, n-m );
		ret += tmp;
		ret += New;
		m = n + Old.size();
		n = data.find( Old, m );
	}

	if ( m < data.size() )
	{
		ret += data.substr( m, data.size()-m );
	}

	return ret;
}
void Utils::trimAll( string& tmp )
{
	tmp = replace( tmp, "-", "_" );
	tmp = replace( tmp, ":", "_" );
	tmp = replace( tmp, " ", "_" );
	tmp = replace( tmp, "	", "_" );
	tmp = replace( tmp, "\\", "_" );
	tmp = replace( tmp, "*", "_" );
	tmp = replace( tmp, "?", "_" );
	tmp = replace( tmp, "\"", "_" );
	tmp = replace( tmp, "<", "_" );
	tmp = replace( tmp, ">", "_" );
	tmp = replace( tmp, "|", "_" );
	tmp = replace( tmp, "/", "_" );
	tmp = replace( tmp, ";", "_" );
	tmp = replace( tmp, "&", "_" );
	tmp = replace( tmp, "%", "_" );
	tmp = replace( tmp, "\r", "_" );
	tmp = replace( tmp, "\n", "_" );
}
string& Utils::trimHead( string& tmp, const char* ext )
{
	string extTrim;
	if ( NULL != ext )
	{
		extTrim = ext;
	}
	for ( ; !tmp.empty(); )
	{
		char c = tmp[0];
		if ( ' ' == c || '	' == c || '\r' == c || '\n' == c )
		{
			tmp.erase( 0, 1 );
		}
		else
		{
			bool found = false;
			for ( size_t i=0; i<extTrim.size(); ++i )
			{
				if ( c == extTrim[i] )
				{
					found = true;
					break;
				}
			}
			if ( found )
			{
				tmp.erase( 0, 1 );
			}
			else
			{
				break;
			}
		}
	}

	return tmp;
}
string& Utils::trimTail( string& tmp, const char* ext )
{
	string extTrim;
	if ( NULL != ext )
	{
		extTrim = ext;
	}
	for ( ; !tmp.empty(); )
	{
		char c = tmp[tmp.size()-1];
		if ( ' ' == c || '	' == c || '\r' == c || '\n' == c )
		{
			tmp.erase( tmp.size()-1, 1 );
		}
		else
		{
			bool found = false;
			for ( size_t i=0; i<extTrim.size(); ++i )
			{
				if ( c == extTrim[i] )
				{
					found = true;
					break;
				}
			}
			if ( found )
			{
				tmp.erase( tmp.size()-1, 1 );
			}
			else
			{
				break;
			}
		}
	}

	return tmp;
}

string Utils::getDateTimeString()
{
	char szTime[100] = { 0 };
#ifdef WIN32
	SYSTEMTIME st;
	memset(&st, 0, sizeof(st));
	::GetLocalTime(&st);
	sprintf(szTime, "%04d_%02d_%02d_%02d_%02d_%02d",
		st.wYear,
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond );
#else
	time_t ts = time(NULL);
	tm t;
	localtime_r( &ts, &t );
	sprintf( szTime, "%04d_%02d_%02d_%02d_%02d_%02d",
			t.tm_year+1900,
			t.tm_mon+1,
			t.tm_mday,
			t.tm_hour,
			t.tm_min,
			t.tm_sec );
#endif

	return string( szTime );
}

void Utils::mkDir(const string& dir)
{
#ifdef WIN32
	_mkdir(dir.data());
#else
	mkdir(dir.data(), 0777);
#endif
}

bool Utils::gbk2utf8( const string& inGbk, string& outUtf8 )
{
#ifdef WIN32
	int len = MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)inGbk.data(), -1, NULL, 0);
	wchar_t * wszUtf8 = new wchar_t[len + 1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)inGbk.data(), -1, wszUtf8, len);

	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL, NULL);
	outUtf8 = szUtf8;
	delete[] szUtf8;
	delete[] wszUtf8;
	return true;
#else
#ifdef _USE_ICONV
	iconv_t h = iconv_open( "utf-8", "gbk" );
	if ( 0 == h )
	{
		return false;
	}

	char* sIn = (char*)inGbk.data();
	size_t inLen = inGbk.size();
	char* sOut = new char[inLen];
	memset( sOut, 0, inLen+1 );
	size_t outLen = inLen;
	int ret = iconv( h, &sIn, &inLen, &sOut, &outLen );
	int err = errno;
	iconv_close(h);
	outUtf8 = sOut;
	delete [] sOut;
	return ( -1 != ret );
#endif
#endif
	return false;
}
bool Utils::utf82gbk( const string& inUtf8, string& outGbk )
{
#ifdef WIN32
	wchar_t * lpUnicodeStr = NULL;
	int nRetLen = ::MultiByteToWideChar( CP_UTF8, 0, (char *)inUtf8.data(), -1, NULL, NULL );
    lpUnicodeStr = new WCHAR[nRetLen + 1];
	memset( lpUnicodeStr, 0, (nRetLen+1)*sizeof(WCHAR) );
	nRetLen = ::MultiByteToWideChar( CP_UTF8, 0, (char *)inUtf8.data(), -1, lpUnicodeStr, nRetLen );
	if(!nRetLen)
	{
		delete [] lpUnicodeStr;
		return false;
	}

	nRetLen = ::WideCharToMultiByte( CP_ACP, 0, lpUnicodeStr, -1, NULL, NULL, NULL, NULL );
	unsigned char* lpGBKStr = unsigned char[nRetLen+1];
	memset( lpGBKStr, 0, nRetLen+1 );
	nRetLen = ::WideCharToMultiByte( CP_ACP, 0, lpUnicodeStr, -1, (char *)lpGBKStr, nRetLen, NULL, NULL );
	delete []lpUnicodeStr;
	outGbk = (char*)lpGBKStr;
	delete [] lpGBKStr;
	return true;
#else
#ifdef _USE_ICONV
	iconv_t h = iconv_open( "gbk", "utf-8" );
	if ( 0 == h )
	{
		return false;
	}

	char* sIn = (char*)inUtf8.data();
	size_t inLen = inUtf8.size();
	char* sOut = new char[(inLen+1)*3];
	memset( sOut, 0, (inLen+1)*3 );
	size_t outLen = inLen;
	int ret = iconv( h, &sIn, &inLen, &sOut, &outLen );
	int err = errno;
	iconv_close(h);
	outGbk = sOut;
	delete [] sOut;
	return ( -1 != ret );
#endif
#endif
	return false;
}

const string& Utils::ucFirst( string& s )
{
	if ( s[0] >= 'a' && s[0] <= 'z' )
	{
		s[0] -= ('a'-'A');
	}
	return s;
}
string Utils::int2str( int n )
{
	char szTemp[20] = {0};
	sprintf( szTemp, "%d", n );
	string s = szTemp;
	return s;
}
long Utils::getTickCount()
{
	timeval tv;
	gettimeofday( &tv, NULL );
	long t = tv.tv_sec*1000 + tv.tv_usec/1000;
	return t;
}
bool Utils::getFileList( const string& dir, vector<string>& fileList, const string& suffix )
{
#if defined( KOS_LINUX ) || defined( KOS_MACOS )
	DIR* d = ::opendir( dir.data() );
	if ( NULL == d )
	{
		return false;
	}
	dirent* ret = NULL;
	vector<string> nextDirs;
	for( ; NULL != (ret=readdir(d)); )
	{
		string name = ret->d_name;
		if ( "." == name || ".." == name )
		{
			continue;
		}

		switch( ret->d_type )
		{
		case 4:
			{
				string nextDir = dir;
				nextDir += "/";
				nextDir += ret->d_name;
				nextDirs.push_back( nextDir );
			}
			break;

		case 8:
		case 10:
			{
				string fileName = ret->d_name;
				bool put = true;
				if ( !suffix.empty() )
				{
					size_t pos = fileName.find( suffix );
					if ( string::npos == pos )
					{
						put = false;
					}
					else
					{
						string r = fileName.substr( pos, fileName.size() - pos );
						if ( r != suffix )
						{
							put = false;
						}
					}
				}
				if ( put )
				{
					string file = dir;
					file += "/";
					file += fileName;
					fileList.push_back( file );
				}

			}
			break;
			
		default:
			break;
		}
	}
	closedir(d);

	for ( size_t i=0; i<nextDirs.size(); ++i )
	{
		getFileList( nextDirs[i], fileList, suffix );
	}

	return true;
#elif defined( KOS_WIN32 )
#endif

	return false;
}
extern void doMd5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest);
void Utils::md5( const string& in, string& out )
{
	uint8_t digest[16];
	doMd5( (uint8_t*)in.data(), in.size(), digest );
	for ( int i=0; i<16; ++i )
	{
		char szTemp[10] = {0};
		sprintf( szTemp, "%02x", digest[i] );
		out += szTemp;
	}
}
void Utils::backTrace()
{
#if defined(KOS_LINUX) || defined(KOS_MACOS)
	void *bt[20]; 
	char **strings; 
	size_t sz;

	sz = backtrace(bt, 20); 
	strings = backtrace_symbols(bt, sz); 
	for( int i = 0; i < sz; ++i ) 
	{
		cout<<strings[i]<<endl;
	}
#endif
}
bool Utils::isEmpty( char c )
{
	return ( ' ' == c || '\t' == c || '\r' == c || '\n' == c );
}

bool Utils::isVarStart( char c )
{
	return ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || '_' == c || '$' == c );
}
bool Utils::isVar( char c )
{
	return ( Utils::isVarStart(c) || ( c >= '0' && c <= '9' ) );
}
bool Utils::isValidVar( const string& var )
{
	for ( size_t i=0; i<var.size(); ++i )
	{
		if ( !Utils::isVar( var[i] ) )
		{
			return false;
		}
	}
	return true;
}
void Utils::log( const char* pszLog, ... )
{
	va_list varg;
	va_start( varg, pszLog );
	FILE* fp = fopen( "log.log", "a+" );
	fprintf( fp, pszLog, varg );
	fprintf( fp, "\n" );
	fclose(fp);
	va_end(varg);
}
bool Utils::isNumStart( const string& var )
{
	if ( var.empty() )
	{
		return false;
	}

	if ( var[0] >= '0' && var[0] <= '9' )
	{
		return true;
	}
	else if ( '-' == var[0] && var.size() > 1 && var[1] >= '0' && var[1] <= '9' )
	{
		return true;
	}

	return false;
}
