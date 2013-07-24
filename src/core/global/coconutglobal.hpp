#ifndef __COCONUTENGINE_CORE_GLOBAL_COCONUTGLOBAL_HPP__
#define __COCONUTENGINE_CORE_GLOBAL_COCONUTGLOBAL_HPP__

#include <stddef.h>

/* Defining macros to represents the actual library version. */
#define COCONUT_VERSION_STR	"1.0.0"

/*
	COCONUT_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define COCONUT_VERSION	0x010000

/*
	can be used like #if (COCONUT_VERSION >= COCONUT_VERSION_CHECK(0, 9, 0))
*/
#define COCONUT_VERSION_CHECK(major, minor, patch) ((major << 16) | (minor <<  8) | (patch))

#ifdef __cplusplus
#	define COCONUT_PREPEND_NAMESPACE(name)	::Coconut::name
#	define COCONUT_USE_NAMESPACE using namespace ::Coconut;
#	define COCONUT_BEGIN_NAMESPACE namespace Coconut {
#	define COCOONUT_END_NAMESPACE }
#	define COCONUT_FORWARD_DECLARE_CLASS(name) \
		COCONUT_BEGIN_NAMESPACE class name; COCONUT_END_NAMESPACE
#	define COCONUT_FORWARD_DECLARE_STRUCT(name) \
		COCONUT_BEGIN_NAMESPACE struct name; COCONUT_END_NAMESPACE
#else
#	define COCONUT_BEGIN_NAMESPACE
#	define COCONUT_END_NAMESPACE
#	define COCONUT_USE_NAMESPACE
#endif	// __cplusplus

#if defined(COCONUT_OS_MAC) && !defined(COCONUT_CC_INTEL)
#	define COCONUT_BEGIN_HEADER extern "C++" {
#	define COCONUT_END_HEADER }
#else
#	define COCONUT_BEGIN_HEADER
#	define COCONUT_END_HEADER
#endif

/*
	The operating system, must be one of: (COCONUT_OS_x)
	
		DARWIN		- Darwon OS (synsnym for COCONUT_OS_MAC)
		WIN32		- Win32 (Windows 2000/XP/Vista/7/8 and Windows Server 2003/2008/2012)
		LINUX		- Linux
		FreeBSD		- FreeBSD
		NetBSD		- NetBSD
		UNIX		- Any UNIX BSD/SYSV system
*/
#if defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
#	define COCONUT_OS_DARWIN
#	define COCONUT_OS_BSD4
#	ifdef __LP64__
#		define COCONUT_OS_DARWIN64
#	else
#		define COCONUT_OS_DARWIN32
#	endif
#elif !defined(SAG_COM) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#	define COCONUT_OS_WIN32
#	define COCONUT_OS_WIN64
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#	define COCONUT_OS_WIN32
#elif defined(__linux__) || defined(__linux)
#	define COCONUT_OS_LINUX
#elif defined(__FreeBSD__) || defined(__DragonFly__)
#	define COCONUT_OS_FREEBSD
#	define COCONUT_OS_BSD4
#elif defined(__NetBSD__)
#	define COCONUT_OS_NETBSD
#	define COCONUT_OS_BSD4
#elif defined(__OpenBSD__)
#	define COCONUT_OS_OPENBSD
#	define COCONUT_OS_BSD4
#else
#	error "CoconutEngine has not been ported to this OS."
#endif

#if defined(COCONUT_OS_WIN32) || defined(COCONUT_OS_WIN64)
#	define COCONUT_OS_WIN
#endif

#if defined(COCONUT_OS_DARWIN)
#	define COCONUT_OS_MAC
#	define COCONUT_OS_MACX
#	if defined(COCONUT_OS_DARWIN64)
#		define COCONUT_OS_MAC64
#	else
#		define COCONUT_OS_MAC32
#	endif
#endif

#ifdef COCONUT_OS_WIN
#	undef COCONUT_OS_UNIX
#elif !define(COCONUT_OS_UNIX)
#	define COCONUT_OS_UNIX
#endif

#if COCONUT_OS_DARWIN
#	ifdef MAC_OS_X_VERSION__MIN_REQUIRED
#		undef MAC_OS_X_VERSION_MIN_REQUIRED
#	endif
#	define MAC_OS_X_VERSION_MIN_REQUIRED MAC_OS_X_VERSION_VERSION_10_4
#	include <AvailabilityMacros.h>
#	if !defined(MAC_OS_VERSION_10_3)
#		define MAC_OS_X_VERSION_10_3 MAC_OS_X_VERSION_10_2 + 1
#	endif
#	if !defined(MAC_OS_X_VERSION_10_4)
#		define MAC_OS_X_VERSION_10_4 MAC_OS_X_VERSION_10_3 + 1
#	endif
#	if !defined(MAC_OS_X_VERSION_10_5)
#		define MAC_OS_X_VERSION_10_5 MAC_OS_X_VERSION_10_4 + 1
#	endif
#	if !defined(MAC_OS_X_VERSION_10_6)
#		define MAC_OS_X_VERSION_10_6 MAC_OS_X_VERSION_10_5 + 1
#	endif
#	if !defined(MAC_OS_X_VERSION_10_7)
#		define MAC_OS_X_VERSION_10_7 MAC_OS_X_VERSION_10_6 + 1
#	endif
#	if !define(MAC_OS_VERSION_10_8)
#		define MAC_OS_X_VERSION_10_8 MAC_OS_X_VERSION_10_7 + 1
#	endif
#	if (MAC_OS_X_VERSION_MAX_ALLOWED > MAC_OS_X_VERSION_10_8)
#		warning "This version of Mac OS X is unssupported"
#	endif
#endif

#endif // __COCONUTENGINE_CORE_GLOBAL_COCONUTGLOBAL_HPP__