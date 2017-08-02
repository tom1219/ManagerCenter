// File: ByteReader.h
// Author: token
// Date: 2016/06/27
#include <string>
#include <memory.h>
using namespace std;

#define GETDATA( __type__ )\
    __type__ GET_##__type__()\
    {\
        if ( !enough( LEN_##__type__ ) )\
            return 0;\
        __type__ v = 0;\
        memcpy( &v, _cur, LEN_##__type__ );\
        _cur += LEN_##__type__;\
        return v;\
    }

class ByteReader
{
public:
    ByteReader( char* data, INT64 size )
    : _data(data)
    , _start(data)
    , _end(data+size)
    , _cur(_start)
    {
    }
    
    GETDATA( CHAR );
    GETDATA( BYTE );
    GETDATA( SHORT );
    GETDATA( WORD );
    GETDATA( INT32 );
    GETDATA( DWORD );
    GETDATA( UINT32 );
    GETDATA( INT64 );
    GETDATA( UINT64 );
    
    bool enough( INT64 size )
    {
        return ( _end - _cur ) >= size;
    }
    
    bool getData( string& data, INT64 size )
    {
        if ( !enough( size ) )
        {
            return false;
        }
        
        data.append( _cur, size );
        _cur += size;
        return true;
    }
    
    INT64 getLeft( string& data )
    {
        if ( !enough(1) )
        {
            return 0;
        }
        
        data.append( _cur, _end-_cur );
        _cur = _end;
        return data.size();
    }
    
private:
    char* _data;
    char* _start;
    char* _end;
    char* _cur;
};
