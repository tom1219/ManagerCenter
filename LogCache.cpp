#include "LogCache.h"

LogCache::LogCache() 
{
}
LogCache::~LogCache()
{
}
LogCache& LogCache::operator<<( const char* s )
{
	if ( NULL != s )
	{
		_data += s;
	}
	return *this;
}
LogCache& LogCache::operator<<( const string& s )
{
	_data += s;
	return *this;
}
LogCache& LogCache::operator<<( int n )
{
	char szTemp[20] = {0};
	sprintf( szTemp, "%d", n );
	_data += szTemp;
	return *this;
}
LogCache& LogCache::operator<<( long n )
{
	char szTemp[100] = {0};
	sprintf( szTemp, "%ld", n );
	_data += szTemp;
	return *this;
}
LogCache& LogCache::operator<<( char c )
{
	char szTemp[5] = {0};
	sprintf( szTemp, "%c", c );
	_data += szTemp;
	return *this;
}
LogCache& LogCache::operator<<( short s )
{
	char szTemp[20] = {0};
	sprintf( szTemp, "%d", s );
	_data += szTemp;
	return *this;
}
LogCache& LogCache::operator<<( BYTE b )
{
	char szTemp[20] = {0};
	sprintf( szTemp, "%d", b );
	_data += szTemp;
	return *this;
}
LogCache& LogCache::operator<<( WORD w )
{
	char szTemp[20] = {0};
	sprintf( szTemp, "%d", w );
	_data += szTemp;
	return *this;
}
LogCache& LogCache::operator<<( DWORD dw )
{
	char szTemp[20] = {0};
	sprintf( szTemp, "%u", dw );
	_data += szTemp;
	return *this;
}
LogCache& LogCache::operator<<( ULONG ul )
{
	char szTemp[100] = {0};
	sprintf( szTemp, "%lu", ul );
	_data += szTemp;
	return *this;
}
LogCache& LogCache::operator<<( float f )
{
	char szTemp[100] = {0};
	sprintf( szTemp, "%f", f );
	_data += szTemp;
	return *this;
}
LogCache& LogCache::operator<<( double db )
{
	char szTemp[100] = {0};
	sprintf( szTemp, "%lf", db );
	_data += szTemp;
	return *this;
}
LogCache& LogCache::operator<<( void* p )
{
	char szTemp[100] = {0};
	sprintf( szTemp, "%p", p );
	_data += szTemp;
	return *this;
}
LogCache& LogCache::operator<<( const EndLine& e )
{
	_data += "\n";
}
void LogCache::clear()
{
	_data.clear();
}
