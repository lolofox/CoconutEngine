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

/*
	C++11 support

	Paper				Macro
	N2341				COCONUT_COMPILER_ALIGNAS
	N2341				COCONUT_COMPILER_ALOGNOF
	N2427				COCONUT_COMPILER_ATOMICS
	N2761				COCONUT_COMPILER_ATTRIBUTES
	N2541				COCONUT_COMPILER_AUTO_FUNCTION
	N1984 N2546			COCONUT_COMPILER_AUTO_TYPE
	N2437				COCONUT_COMPILER_CLASS_ENUM
	N2235				COCONUT_COMPILER_CONSTEXPR
	N2343 N3276			COCONUT_COMPILER_DECLTYPE
	N2346				COCONUT_COMPILER_DEFAULT_MEMBERS
	N2346				COCONUT_COMPILER_DELETE_MEMBERS
	N1986				COCONUT_COMPILER_DELEGATING_CONSTRUCTORS
	N3206 N3272			COCONUT_COMPILER_EXPLICIT_OVERRIDES
	N1987				COCONUT_COMPILER_EXTERN_TEMPLATES
	N2540				COCONUT_COMPILER_INHERITING_CONSTRUCTORS
	N2672				COCONUT_COMPILER_INITIALIZER_LISTS
	N2658 N2927			COCONUT_COMPILER_LAMBDA
	N2756				COCONUT_COMPILER_NONSTATIC_MEMBER_INIT
	N2855 N3050			COCONUT_COMPILER_NOEXCEPT
	N2431				COCONUT_COMPILER_NULLPTR
	N2930				COCONUT_COMPILER_RANGE_FOR
	N2442				COCONUT_COMPILER_RAW_STRINGS
	N2439				COCONUT_COMPILER_REF_QUALIFIERS
	N2118 N2844 N3053	COCONUT_COMPILER_RVALUE_REFS
	N1720				COCONUT_COMPILER_STATIC_ASSERT
	N2258				COCONUT_COMPILER_TEMPLATE_ALIAS
	N2659				COCONUT_COMPILER_THREAD_LOCAL
	N2765				COCONUT_COMPILER_UDL
	N2442				COCONUT_COMPILER_UNICODE_STRINGS
	N2544				COCONUT_COMPILER_UNRESTRICTED_UNIONS
	N1653				COCONUT_COMPILER_VARIADIC_MACROS
	N2242 N2555			COCONUT_COMPILER_VARIADIC_TEMPLATES
*/

#ifdef COCONUT_CC_INTEL
#	if __INTEL_COMPILER < 1200
#		define COCONUT_NO_TEMPLATE_FRIENDS
#	endif
#	if __cplusplus >= 201103L
#		define COCONUT_COMPILER_VARIADIC_MACROS
#		if __INTEL_COMPILER >= 1200
#			define COCONUT_COMPILER_AUTO_TYPE
#			define COCONUT_COMPILER_CLASS_ENUM
#			define COCONUT_COMPILER_DECLTYPE
#			define COCONUT_COMPILER_DEFAULT_MEMBERS
#			define COCONUT_COMPILER_DELETE_MEMBERS
#			define COCONUT_COMPILER_EXTERN_TEMPLATES
#			define COCONUT_COMPILER_LAMBDA
#			define COCONUT_COMPILER_RVALUE_REFS
#			define COCONUT_COMPILER_STATIC_ASSERT
#			define COCONUT_COMPILER_THREAD_LOCAL
#			define COCONUT_COMPILER_VARIADOC_MACROS
#		endif
#		if __INTEL_COMPILER >= 1210
#			define COCONUT_COMPILER_ATTRIBUTES
#			define COCONUT_COMPILER_AUTO_FUNCTION
#			define COCONUT_COMPILER_NULLPTR
#			define COCONUT_COMPILER_TEMPLATE_ALIAS
#			define COCONUT_COMPILER_UNICODE_STRINGS
#			define COCONUT_COMPILER_VARIADIC_TEMPLATES
#		endif
#		if __INTEL_COMPILER >= 1300
#			define COCONUT_COMPILER_INITIALIZERS_LISTS
#			define COCONUT_COMPILER_NOEXCEPT
#		endif
#	endif
#endif

#ifdef COCONUT_OS_CLANG
/* General C++ features */
#	if !__has_features(cxx_exceptions)
#		ifndef COCONUT_NO_EXCEPTIONS
#			define COCONUT_NO_EXCEPTIONS
#		endif
#	endif
#	if !__has_feature(cxx_rtti)
#		define COCONUT_NORTTI
#	endif

/* C++11 features, see http://clang.llvm.org/cxx_status.html */
#	if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
	/* Detect C++ features using __has_feature(), see http://clang.llvm.org/docs/LanguageExtensions.html#cxx11 */
#		if __has_feature(cxx_alignas)
#			define COCONUT_COMPILER_ALIGNAS
#			define COCONUT_COMPILER_ALOGNOF
#		endif
#		if 0 /* not implemented yet */
#			define COCONUTE_COMPILER_ATOMICS
#		endif
#		if __has_feature(cxx_attributes)
#			define COCONUT_COMPILER_ATTRIBUTES
#		endif
#		if __has_feature(cxx_auto_type)
#			define COCONUT_COMPILER_AUTO_FUNCTION
#			define COCONUT_COMPILER_AUTO_TYPE
#		endif
#		if __has_feature(cxx_string_enums)
#			define COCONUT_COMPILER_CLASS_ENUM
#		endif
#		if __has_feature(cxx_constexpr)
#			define COCONUT_COMPILER_CONSTEXPR
#		endif
#		if __has_feature(cxx_decltype)
#			define COCONUT_COMPILER_DECLTYPE
#		endif
#		if __has_feature(cxx_defaulted_functions)
#			define COCONUT_COMPILER_DEFAULT_MEMBERS
#		endif
#		if __has_feature(cxx_deleted_functions)
#			define COCONUT_COMPILER_DELETE_MEMBERS
#		endif
#		if __has_feature(cxx_delegating_constructors)
#			define COCONUT_COMPILER_DELEGATING_CONSTRUCTORS
#		endif
#		if __has_feature(cxx_override_control)
#			define COCONUT_COMPILER_EXPLICIT_OVERRIDES
#		endif
#		if __has_feature(cxx_inheriting_constructors)
#			define COCONUT_COMPILER_INHERITING_CONSTRUCTORS
#		endif
#		if __has_feature(cxx_generalized_initializers)
#			define COCONUT_COMPILER_INITIALIZER_LISTS
#		endif
#		if __has_feature(cxx_lambdas)
#			define COCONUT_COMPILER_LAMBDA
#		endif
#		if __has_feature(cxx_noexcept)
#			define COCONUT_COMPILER_NOEXCEPT
#		endif
#		if __has_feature(cxx_nonstatic_member_init)
#			define COCONUT_COMPILER_NONSTATIC_MEMBER_INIT
#		endif
#		if __has_feature(cxx_nullptr)
#			define COCONUT_COMPILER_NULLPTR
#		endif
#		if __has_feature(cxx_range_for)
#			define COCONUT_COMPILER_RANGE_FOR
#		endif
#		if __has_feature(cxx_raw_string_literals)
#			define COCONUT_COMPILER_RAW_STRINGS
#		endif
#		if __has_feature(cxx_reference_qualified_functions)
#			define COCONUT_COMPILER_REF_QUALIFIERS
#		endif
#		if __has_feature(cxx_rvalue_references)
#			define COCONUT_COMPILER_RVALUE_REFS
#		endif
#		if __has_feature(cxx_static_assert)
#			define COCONUT_COMPILER_STATIC_ASSERT
#		endif
#		if __has_feature(cxx_alias_templates)
#			define COCONUT_COMPILER_TEMPLATE_ALIAS
#		endif
#		if 0 /* not implemented in clang yet */
#			define COCONUT_COMPILER_THREAD_LOCAL
#		endif
#		if __has_feature(cxx_user_literals)
#			define COCONUT_COMPILER_UDL
#		endif
#		if __has_feature(cxx_unicoode_literals)
#			define COCONUT_COMPILER_UNICODE_STRINGS
#		endif
#		if __has_feature(cxx_unrestricted_unions)
#			define COCONUT_COMPILER_UNRESTRICTED_UNIONS
#		endif
#		if __has_feature(cxx_variadic_templates)
#			define COCONUT_COMPILER_VARIADIC_TEMPLATES
#		endif
		/* Features that have no __has_features() check */
#		if ((__clang_major__ * 100) +  __clang_minor__) >= 209 /* since clang 2.9 */
#			define COCONUT_COMPILER_EXTERN_TEMPLATES
#			define COCONUT_COMPILER_VARIADIC_MACROS
#		endif
#	endif
#endif // COCONUT_CC_CLANG

#if defined(COCONUT_CC_GNUC) && !defined(COCONUT_CC_INTEL) && !defined(COCONUT_CC_CLANG)
#	if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
#		if (__GNUC__ * 100 + __GNUC_MINOR__) >= 403
			/* C++11 features supported in GCC 4.3: */
#			define COCONUT_COMPILER_DECLTYPE
#			define COCONUT_COMPILER_RVALUE_REFS
#			define COCONUT_COMPILER_STATIC_ASSERT
#			define COCONUT_COMPILER_VARIADIC_MACROS
#		endif
#		if (__GNUC__ * 100 + __GNUC_MINOR__) >= 404
			/* C++11 features supported in GCC 4.4: */
#			define COCONUT_COMPILER_AUTO_FUNCTION
#			define COCONUT_COMPILER_AUTO_TYPE
#			define COCONUT_COMPILER_CLASS_ENUM
#			define COCONUT_COMPILER_DEFAULT_MEMBERS
#			define COCONUT_COMPILER_DELETE_MEMBERS
#			define COCONUT_COMPILER_EXTERN_TEMPLATES
#			define COCONUT_COMPILER_INITIALIZER_LISTS
#			define COCONUT_COMPILER_UNICODE_STRINGS
#			define COCONUT_COMPILER_VARIADIC_TEMPLATES
#		endif
#		if (__GNUC__ * 100 + __GNUC_MINOR__) >= 405
			/* C++11 features supported in GCC 4.5: */
#			define COCONUT_COMPILER_LAMBDA
#			define COCONUT_COMPILER_RAW_STRINGS
#		endif
#		if (__GNUC__ * 100 + __GNUC_MINOR__) >= 406
			/* C++11 features supported in GCC 4.6: */
#			define COCONUT_COMPILER_CONSTEXPR
#			define COCONUT_COMPILER_NULLPTR
#			define COCONUT_COMPILER_UNRESTRICTED_UNIONS
#			define COCONUT_COMPILER_RANGE_FOR
#		endif
#		if (__GNUC__ * 100 + __GNUC_MINOR__) >= 407
#			define COCONUT_COMPILER_ATOMICS
#			define COCONUT_COMPILER_NOEXCEPT
#			define COCONUT_COMPILER_NONSTATIC_MEMBER_INIT
#			define COCONUT_COMPILER_DELEGATING_CONSTRUCTORS
#			deifne COCONUT_COMPILER_EXPLICIT_OVERRIDES
#			define COCONUT_COMPILER_TEMPLATE_ALIAS
#			define COCONUT_UDL
#		endif
#		if (__GNUC__ * 100 + __GNUC_MINOR__) >= 408
#			define COCONUT_COMPILER_ATTRIBUTES
#			define COCONUT_COMPILER_ALIGNAS
#			define COCONUT_COMPILER_ALIGNOF
#			define COCONUT_COMPILER_INHERITING_CONSTRUCTORS
#			define COCONUT_COMPILER_THREAD_LOCAL
#			if (__GNUC__ * 100 + __GNUC_MINOR__) > 408 || __GNUC_PATCHLEVEL__ > 1
#				define COCONUT_COMPILER_REF_QUALIFIERS
#			endif
#		endif
		/* C++11 features are complete as of GCC 4.8.1 */
#	endif
#endif

#if defined(COCONUT_CC_MSVC) && !defined(COCONUT_CC_INTEL)
#	if _MSC_VER >= 1400
		/* C++11 features supported in VC8 = VC2005: */
#		define COCONUT_COMPILER_VARIADOC_MACROS
#		define COCONUT_COMPILER_OVERRIDE override
#		define COCONUT_COMPILER_FINAL sealed
#	endif
#	if _MSC_VER >= 1600
		/* C++11 features suppported in VC10 = VC2010: */
#		define COCONUT_COMPILER_AUTO_FUNCTION
#		define COCONUT_COMPILER_AUTO_TYPE
#		define COCONUT_COMPILER_LAMBDA
#		define COCONUT_COMPILER_DECLTYPE
#		define COCONUT_COMPILER_RVALUE_REFS
#		define COCONUT_COMPILER_STATIC_ASSERT
#		define COCONUT_COMPILER_INITIALIZER_LISTS
#	endif
#	if _MSC_VER >= 1700
		/* C++11 features supporte in VC11 = VC2010: */
#		undef COCONUT_DECL_OEVERRIDE
#		undef COCONUT_DECL_FINAL
#		define COCONUT_COMPILER_EXPLICIT_OVERRIDES
#		define COCONUT_COMPILER_RANGE_FOR
#		define COCONUT_COMPILER_CLASS_ENUM
#		define COCONUT_COMPILER_ATOMICS
#	endif
#endif

/*
 C++11 keywords and expressions
*/
#ifdef COCONUT_COMPILER_NULLPTR
#	define COCONUT_NULLPTR		nullptr
#else
#	define COCONUT_NULLPTR		0
#endif

#ifdef COCONUT_COMPILER_DEFAULT_MEMBERS
#	define COCONUT_DECL_EQ_DEFAULT = default
#else
#	define COCONUT_DECL_EQ_DEFAULT
#endif

#ifdef COCONUT_COMPILER_DELETE_MEMBERS
#	define COCONUT_DECL_EQ_DELETE = delete
#else
#	define COCONUT_DECL_EQ_DELETE
#endif

#ifdef COCONUT_COMPILER_CONSTEXPR
#	define COCONUT_DECL_CONSTEXPR constexpr
#else
#	define COCONUT_DECL_CONSTEXPR
#endif

#ifdef COCONUT_COMPILER_EXPLICIT_OVERRIDES
#	define COCONUT_COMPILER_OVERRIDE override
#	define COCONUT_COMPILER_FINAL final
#else
#	ifndef COCONUT_DECL_OVERRIDE
#		define COCONUT_DECL_OVERRIDE
#	endif
#	ifndef COCONUT_DECL_FINAL
#		define COCONUT_DECL_FINAL
#	endif
#endif

#ifdef COCONUT_COMPILE_NOEXCEPT
#	define COCONUT_DECL_NOEXCEPT noexcept
#	define COCONUT_DECL_NOEXCEPT_EXPR(x) noexcept(x)
#	ifdef COCONUT_DECL_NOTHROZ
#		undef COCONUT_DECL_NOTHROW
#	endif
#else
#	define COCONUT_DECL_NOEXCEPT
#	define COCONUT_DECL_NOEXCEPT_EXPORT(x)
#endif
#ifndef COCONUT_DECL_NOTHROW
#	define COCONUT_DECL_NOTHROW COCONUT_DECL_NOEXCEPT
#endif

#if defined(COCONUT_COMPILER_ALIGNOF) && !defined(COCONUT_ALIGNOF)
#	define COCONUT_ALIGNOF(x) alignof(x)
#endif

/*
	Fall-back macros to certain compiler features
*/
#ifndef COCONUT_NORETURN
#	define COCONUT_NORETURN
#endif
#ifndef COCONUT_PACKED
#	define COCONUT_PACKED
#	undef COCONUT_NO_PACKED_REFERENCE
#endif
#ifndef COCONUT_LIKELY
#	define COCONUT_LIKELY(x) (x)
#endif
#ifndef COCONUT_UNLIKELY
#	define COCONUT_UNLIKELY(x) (x)
#endif
#ifndef COCONUT_ASSUME_IMPL
#	define COCONUT_ASSUME_IMPL(expr) // coconut_noop()
#endif
#ifndef COCONUT_UNREACHABLE_IMPL
#	define COCONUT_UNREACHABLE_IMPL() // coconut_noop()
#endif
#ifndef COCONUT_ALLOC_SIZE
#	define COCONUT_ALLOC_SIZE
#endif
#ifndef COCONUT_REQUIRED_RESULT
#	define COCONUT_REQUIRED_RESULT
#endif
#ifndef COCONUT_DECL_DEPRECATED
#	define COCONUT_DECL_DEPRECATED
#endif
#ifndef COCONUT_DECL_VARIABLE_DEPRECATED
#	define COCONUT_DECL_VARIABLE_DEPRECATED
#endif
#ifndef COCONUT_DECL_EXPORT
#	define COCONUT_DECL_EXPORT
#endif
#ifndef COCONUT_DECL_IMPORT
#	define COCONUT_DECL_IMPORT
#endif
#ifndef COCONUT_DECL_HIDDEN
#	define COCONUT_DECL_HIDDEN
#endif
#ifndef COCONUT_DECL_UNUSED
#	define COCONUT_DECL_UNUSED
#endif
#ifndef COCONUT_FUNC_INFO
#	define COCONUT_FUNC_INFO __FILE "(line number unavailable)"
#endif

/*
	Workaround for static const members on MSVC++.
*/
#if defined(COCONUT_CC_MSVC)
#	define COCONUT_STATIC_CONST static
#	define COCONUT_STATIC_CONST_IMPL
#else
#	define COCONUT_STATIC_CONST static const
#	define COCONUT_STATIC_CONST_INPL const
#endif

#endif // __COCONUT_CORE_GLOBAL_COMPILERDETECTION__HPP__