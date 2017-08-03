#include <iostream>
#include "MainThread.h"
using namespace std;

int main( int argc, char** argv )
{
	CMainThread mt;
	mt.start();
	sleep(60*60*24*30);
	return 0;
}
