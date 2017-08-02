#ifndef _SHARE_LIB_H_
#define _SHARE_LIB_H_
#include <string>
#include "tinyxml2.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;

typedef tinyxml2::XMLElement XML_NODE;

class ShareLib
{
public:
	static string getString( tinyxml2::XMLElement* node, const char* name, const char* Default = "" )
	{
		const char* p = node->Attribute( name );
		if ( NULL == p )
		{
			return string(Default);
		}
		return string(p);
	}

	static int getInt( tinyxml2::XMLElement* node, const char* name, int Default = 0 )
	{
		const char* p = node->Attribute( name );
		if ( NULL == p )
		{
			return Default;
		}
		return atoi(p);
	}

	static bool getBool( tinyxml2::XMLElement* node, const char* name, bool _default = false )
	{
		const char* p = node->Attribute( name );
		if ( NULL == p )
		{
			return _default;
		}

		return 0 == strcmp( "true", p );
	}
};


#endif //_SHARE_LIB_H_
