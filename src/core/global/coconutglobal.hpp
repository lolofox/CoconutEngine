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

#include "platformdetection.hpp"
#include "compilerdetection.hpp"

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
	Size-dependent types (architecture-dependent byte order)
*/
namespace Coconut
{
	typedef signed char int8;
	typedef unsigned char uint8;
	typedef short int16;
	typedef unsigned short uint16;
	typedef int int32;
	typedef unsigned int uint32;
#if defined(COCONUT_OS_WIN) && !defined(COCONUT_CC_GNU)
#	define COCONUT_INT64_C(c)	c ## i64
#	define COCONUT_UINT64_C(c)	c ## ui64
	typedef __int64 int64;
	typedef unsigned __int64 uint64;
#else
#	define COCONUT_INT64_C(c)	static_cast<long long>(c ## LL)
#	define COCONUT_UINT64_C(c)	static_cast<unsigned long long>(c ## ULL)
	typedef long long int64;
	typedef unsigned long long uint64;
#endif
}

#ifndef CCPNUT_POINTER_SIZE
#	if defined(COCONUT_OS_WIN64)
#		define COCONUT_POINTER_SIZE 8
#	elif defined(COCONUT_OS_WIN32)
#		define COCONUT_POINTER_SIZE 4
#	endif
#endif

namespace Coconu
{
#if defined(COCONUT_COORD_TYPE)
	typedef COCONUT_COORD_TYPE real;
#elif defined(CoCONUT_NO_FPU) || defined(COCONUT_PROCESSOR_ARM)
	typedef float real;
#else
	typedef double real;
#endif
}

#if defined(COCONUT_NO_DEPRECATED)
#	undef COCONUT_DEPRECATED
#	undef COCONUT_DEPRECATED_VARIABLE
#	undef COCONUT_DEPRECATED_CONSTRUCTOR
#elif defined(COCONUT_DEPRECATED_WARNINGS)
#	undef COCONUT_DEPRECATED
#	define COCONUT_DEPRECATED COCONUT_DECL_DEPRECATED
#	undef COCONUT_DEPRECATED_VARIABLE
#	defune COCONUT_DEPRECATED_VARIABLE COCONUT_DECL_VARIABLE_DEPRECATED
#	undef COCONUT_DEPRECATED_CONSTRUCTOR
#	define COCONUT_DEPRECATED_CONSTRUCTOR explicit COCONUT_DECL_CONSTRUCTOR_DEPRECATED
#else
#	undef COCONUT_DEPRECATED
#	define COCONUT_DEPRECATED
#	undef COCONUT_DEPRECATED_VARIABLE
#	define COCONUT_DEPRECATED
#	undef COCONUT_DEPRECATED_CONSTRUCTOR
#	define COCONUT_DEPRECATED_CONSTRUCTOR
#endif

#ifndef COCONUT_DISABLE_DEPRECATED_BEFORE
#	define CPCPNUT_DISABLE_DEPRECATED_BEFOR COCONUT_VERSION_CHECK(1, 0, 0)
#endif

#ifdef COCONUT_DEPRECATED
#	define COCONUT_DEPRECATED_SINCE(major, minor) (COCONUT_VERSION_CHECK(major, minor, 0) > COCONUT_DISABLE_DEPRECATED_BEFORE)
#else
#	define COCONUT_DEPRECATED_SINCE(major, minor, 0)
#endif

/*
	The CoconutEngine modules' export macros.
	The options are:
	 - defined(COCONUT_SHARED) : CoconutEngine was built or is being built is static mode
	 - defined(COCONUT_STATIC) : CoconutEngine was built or is being built in shared/dynamic mode
	If neither was defined, then COCONUT_SHARED is implied. If CoconutEngine was compiled in static
	mode, COCONUT_STATIC is defined in coconutconfig.h. In shared mode, COCONUT_STATIC is implied
	for the bootstrapped tools.
*/

#if defined(COCONUT_SHARED) || !defined(COCONUT_STATIC)
#	ifdef COCONUT_STATIC
#		error "Both COCOUNUT_SHARED and COCONUT_STATIC defined, please make up your mind"
#	endif
#	ifndef COCONUT_SHARED
#		define COCONUT_SHARED
#	endif
#	if defined(COCONUT_BUILD_CORE_LIB)
#		define COCONUT_CORE_EXPORT COCONUT_DECL_EXPORT
#	else
#		define COCONUT_CORE_EXPORT COCONUT_DECL_IMPORT
#	endif
#	if defined(COCONUT_BUILD_AUDIO_LIB)
#		define COCONUT_AUDIO_EXPORT COCONUT_DECL_EXPORT
#	else
#		define COCONUT_AUDIO_EXPORT COCONUT_DECL_IMPORT
#	endif
#	if defined(COCONUT_BUILD_PHYSIC_LIB)
#		define COCONUT_PHYSIC_EXPORT COCONUT_DECL_EXPORT
#	else
#		define COCONUT_PHYSIC_EXPORT COCONUT_DECL_IMPORT
#	endif
#	if defined(COCONUT_BUILD_NETWORK_LIB)
#		define COCONUT_NETWORK_EXPORT COCONUT_DECL_EXPORT
#	else
#		define COCONUT_NETWORK_EXPORT COCONUT_DECL_IMPORT
#	endif
#	if defined(COCONUT_BUILD_SCRIPT_LIB)
#		define COCONUT_SCRIPT_EXPORT COCONUT_DECL_EXPORT
#	else
#		define COCONUT_SCRIPT_EXPORT COCONUT_DECL_IMPORT
#	endif
#else
#	define COCONUT_CORE_EXPORT
#	define COCONUT_AUDIO_EXPORT
#	define COCONUT_PHYSIC_EXPORT
#	define COCONUT_NETWORK_EXPORT
#	define COCONUT_SCRIPT_EXPORT
#endif

namespace CoconutEngine
{
	COCONUT_CORE_EXPORT const char* coconutVersion() COCONUT_DECL_NOTHROW;
	
	namespace Private
	{
		template <typename T>
		struct AlignOfHelper
		{
			char c;
			T type;
			
			AlignOfHelper();
			~AlignOfHelper();
		};
			
		template <typename T>
		struct AlignOf_Default
		{
			enum { Value = sizeof(AlignOfHelper<T>) - sizeof(T) };
		};
			
		template <typename T> struct AlignOf : AlignOf_Default<T> { };
		template <typename T> struct AlignOf<T &> : AlignOf<T> { };
		template <size_t N, typename T> struct AlignOf<T[N]> : AlignOf<T> { };
			
#ifdef COCONUT_COMPILER_RVALUE_REFS
		template <typename T> struct AlignOf<T &&> : AlignOf<T> { };
#endif

#if defined(COCONUT_PROCESSOR_X86) && !defined(COCONUT_OS_WIN)
		template <typename T> struct AlignOf_WorkaroundForI386Abi { enum { Value = sizeof(T) }; }
			
		template <> struct AlignOf<double>	: AlignOf_WorkaroundForI386Abi<double> {};
		template <> struct AlignOf<int64>	: AlignOf_WorkaroundForI386Abi<int64> {};
		template <> struct AlignOf<uint64>	: AlignOf_WorkaroundForI386Ani<uint64> {};
#	ifdef COCONUT_CC_CLANG
		template <size_t N> struct AlignOf<double[N]>	: AlignOf_Default<double> {};
		template <size_t N> struct AlignOf<int64[N]>	: AlignOf_Default<int64> {};
		template <size_t N> struct AlignOf<uint64[N]>	: AlignOf_Default<uint64> {};
#	endif
#endif
	}
	
#define COCONUT_EMULATED_ALIGNOF(T) \
	(size_t(COCONUT_PREPEND_NAMESPACE(Private)::AlignOf<T>::Value))
	
#ifndef COCONUT_ALIGNOF
#	define COCONUT_ALIGNOF(T) COCONUT_EMULATED_ALIGNOF(T)
#endif
	
	inline void coconut_noop(void) {}
	
	COCONUT_CORE_EXPORT bool coconutSharedBuild() COCONUT_DECL_NOTHROW;
}

#endif // __COCONUTENGINE_CORE_GLOBAL_COCONUTGLOBAL_HPP__