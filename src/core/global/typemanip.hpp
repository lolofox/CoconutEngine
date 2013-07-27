#ifndef __COCONUT_CORE_GLOBAL_TYPEMANIP_HPP__
#define __COCONUT_CORE_GLOBAL_TYPEMANIP_HPP__

namespace CoconutEngine
{
	namespace Core
	{
		template <typename T, typename U>
		struct IsSmaller
		{
			enum { Value = sizeof(T) < sizeof(U) };
		};
		
		/*
			Class template select
			selects one of two types upon a boolean constant
			Invocation: Select<flag, T, U>::Result
			Where:
			flag is a compile-time boolean constant
			T ans U are types
			Result evaluates to t of flag is true, and to U otherwise.
		*/
		template <bool flag, typename T, typename U>
		struct Select
		{
			typedef T Result;
		};
		
		template <typename T, typename U>
		struct Select<false, T, U>
		{
			typedef U Result;
		};
		
		namespace Private
		{
			template <typename T, typename U>
			struct ConversionHelper
			{
				typedef char Small;
				struct Big { char dummy[2]; };
				static Big Test(...);
				static Small Test(U);
				static T MakeT();
			};
		}
		
		template <typename T, typename U>
		struct Conversion
		{
			typedef Private::ConversionHelper<T, U> H;
			
			enum { exists = sizeof(typename H::Small) == sizeof((H::Test(H::MakeT()))) };
			
			enum { exists2Way = exists && Conversion<U, T>::exists };
			enum { sameType = false };
		};
		
		template<typename T>
		struct Conversion<T, T>
		{
			enum { exists = 1, exists2Way = 1, sameType = 1 };
		};
		
		template <typename T>
		struct Conversion<void, T>
		{
			enum { exists = 0, exists2Way = 0, sameType = 0 };
		};
		
		template <typename T>
		struct Conversion<T, void>
		{
			enum { exists = 0, exists2Way = 0, sameType = 0 };
		};
		
		template <>
		struct Conversion<void, void>
		{
			enum { exists = 1, exists2Way = 1, sameType = 1 };
		};
		
		/*
			Class template SuperSubClass
			Invocation: SuperSubClass<B, D>::Value where B and D are types.
			Returns true if B is a public base of D, or if B and D are aliases of the same type.
		*/
		template <typename T, typename U>
		struct SuperSubClass
		{
			enum { value = (::CoconutEngine::Core::Conversion<const volatile U*, const volatile T*>::exists &&
							!::CoconutEngine::Core::Conversion<const volatile T*, const volatile void*>::sameType) };
							
			enum { dontUseWithIncompleteTypes = (sizeof(T) == sizeof(U)) };
		};
		
		template <>
		struct SuperSubClass<void, void>
		{
			enum { value = false };
		};
		
		template <typename U>
		struct SuperSubClass<void, U>
		{
			enum { value = (::CoconutEngine::Core::Conversion<const volatile U*, const volatile void*>::exists &&
							!::CoconutEngine::Core::Conversion<const volatile void*, const volatile void*>::sameType) };
							
			enum { dontUseWithIncompleteType = (0 == sizeof(U)) };
		};
		
		template <typename T>
		struct SuperSubClass<T, void>
		{
			enum { value = (::CoconutEngine::Core::Conversion<const volatile void*, const volatile T*>::exists &&
							!::CoconutEngine::Core::Conversion<const volatile T*, const volatile void *>::sameType) };
							
			enum { dontUseWithIncompleteTypes = (sizeof(T) == 0) };
		};
	}
}

#endif // __COCONUT_CORE_GLOBAL_TYPEMANIP_HPP__