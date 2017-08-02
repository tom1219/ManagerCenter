#ifndef _K_PLATFORM_H_
#define _K_PLATFORM_H_

//target platform type
#define KOS_TARGET_MACOS 1
#define KOS_TARGET_WIN32 2
#define KOS_TARGET_LINUX 3
#define KOS_TARGET_ANDROID 4
#define KOS_TARGET_UNKNOWN 100

//target platform name
#define KOS_NAME_MACOS "macos"
#define KOS_NAME_WIN32 "win32"
#define KOS_NAME_LINUX "linux"
#define KOS_NAME_ANDROID "android"
#define KOS_NAME_UNKNOWN "unknown"

#if defined( __APPLE__ ) && defined( __MACH__ )
	#define KOS_MACOS 1
	#define KOS_TARGET KOS_TARGET_MACOS
	#define KOS_NAME KOS_NAME_MACOS
#elif defined( _WIN32 )
	#define KOS_WIN32 1
	#define KOS_TARGET KOS_TARGET_WIN32
	#define KOS_NAME KOS_NAME_WIN32
#elif defined( __linux__ ) || defined( __gnu_linux__ )
	#define KOS_LINUX 1
	#define KOS_TARGET KOS_TARGET_LINUX
	#define KOS_NAME KOS_NAME_LINUX
#elif defined( __ANDROID__ )
	#define KOS_ANDROID 1
	#define KOS_TARGET KOS_TARGET_ANDROID
	#define KOS_NAME KOS_NAME_ANDROID
#else
	#define KOS_UNKNOWN 1
	#define KOS_TARGET KOS_TARGET_UNKNOWN
	#define KOS_NAME KOS_NAME_UNKNOWN
#endif



#endif //_K_PLATFORM_H_
