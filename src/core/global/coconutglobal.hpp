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

#endif // __COCONUTENGINE_CORE_GLOBAL_COCONUTGLOBAL_HPP__