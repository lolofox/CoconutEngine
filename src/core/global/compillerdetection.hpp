#ifndef __COCONUT_CORE_GLOBAL_COMPILERDETECTION__HPP__
#define __COCONUT_CORE_GLOBAL_COMPILERDETECTION__HPP__

/*
	The compiler, must be one of: (COCONUT_CC_x)
	
		MSVC	- Microsoft Visual C/C++, Intel C++ for Windows
		GNUC 	- GNU C++
		INTEL	- Intel C++ for Linux, Intel C++ for Windows
		CLANG	- C++ front-end for the LLVM compiler
*/
#if defined(_MSC_VER)
#	define COCONUT_CC_MSVC
#	define COCONUT_CC_MSVC_NET
#	define COCONUT_NO_TEMPLATE_FRIENDS
#	define COCONUT_FUNC_INFO __FUNCSIG__
#	define COCONUT_ALIGNOF(type) __alignof(type)
#	define COCONUT_DECL_ALIGN __declspec(align(n))
#	define COCONUT_ASSUME_IMPL(expr) __assume(expr)
#	define COCONUT_UNREACHABLE_IMPL() __assume(0)
#	define COCONUT_NORETURN __declspec(deprecated)
#	define COCONUT_DECL_EXPORT __declspec(dllexport)
#	define COCONUT_DECL_IMPORT __declspec(dllimport)
/* Intel C++ disguising as Visual C++: the 'using' keyword avoids warnings */
#	if defined(__INTEL_COMPILER)
#		define COCONUT_DECL_VARIABLE_DEPRECATED
#		define COCONUT_CC_INTEL
#	endif

/* only defined for MSVC since that's the only compiler that actually optimizes for this. */
#	ifdef __cplusplus
#		define COCONUT_DECL_NOTHROW throw()
#	endif

#elif defined(__GNUC__)
#	define COCONUT_CC_GNU
#	define COCONUT_C_CALLBACKKS
#	if defined(__MINGW32__)
#		define COCONUT_CC_MINGW
#	endif
#	if defined(__INTEL_COMPILER)
/* Intel C++ also masquerades as GCC */
#		define COCONUT_CC_INTEL
#		define COCONUT_ASSUME_IMPL(expr) __assume(expr)
#		define COCONUT_UNREACHABLE_IMPL() __assume(0)
#	elif defined(__clang__)
#		define COCONUT_CC_CLANG
#		define COCONUT_ASSUME_IMPL(expr)	if (expr) {} else __uiltin_unreachable()
#		define COCONUT_UNREACHABLE_IMPL() 	__builtin_unreachable()
#		if !defined(__has_extension)
			/* Compatibility with older Clang versions. */
#			define __has_extension __has_feature
#		endif
#	else
/* Plain GCC */
#		if (__GNUC__ * 100 + __GNUC_MINOR__) >= 405
#			define COCONUT_ASSUME_IMPL(expr) if(expr){} else __builtin_unreachable()
#			define COCONUT_UNREACHABLE_IMPL() --builtin_unreachable()
#		endif
#	endif

#	ifdef COCONUT_OS_WIN
#		define COCONUT_DECL_EXPORT	__declspec(dllexport)
#		define COCONUT_DECL_IMPORT	__declspec(dllimport)
#	else
#		define COCONUT_DECL_EXPORT	__attribute__((visibility("default")))
#		define COCONUT_DECL_IMPORT	__attribute__((visibility("default")))
#		define COCONUT_DECL_HIDDEN	__attribute__((visibility("hidden")))
#	endif

#	define COCONUT_FUNC_INFO		__PRETTY_FUNCTION__
#	define COCONUT_ALIGNOF(type)	__alignof__(type)
#	define COCONUT_TYPEOF(expr)		__typeof__(expr)
#	define COCONUT_DECL_DEPRECATED	__attribute__((deprecated))
#	define COCONUT_DECL_ALIGN(n)	__attribute__((__aligned__(n)))
#	define COCONUT_DECL_UNUSED		__attribute__((__unused__))
#	define COCONUT_LIKELY(expr)		__builtin_expect(!!(expr), true)
#	define COCONUT_UNLIKELY(expr)	__builtin_expect(!!(expr), false)
#	define COCONUT_NORETURN			__attribute__((__noreturn__))
#	define COCONUT_REQUIRED_RESULT	__attribute__((__warn_unused_result__))
#	if (__GNUC__ * 100 + __GNUC_MINOR__) >= 403 && !defined(COCONUT_CC_CLANG)
#		define COCONUT_ALLOC_SIZE(x) __attribute__((alloc_size(x)))
#	endif

#endif

#endif // __COCONUT_CORE_GLOBAL_COMPILERDETECTION__HPP__