#ifndef __COCONUT_CORE_GLOBAL_TYPELIST_HPP__
#define __COCONUT_CORE_GLOBAL_TYPELIST_HPP__

namespace CoconutEngine
{
	namespace Core
	{
		template <typename T, typename S>
		struct TypeList
		{
			typedef T Head;
			typedef S Tail;
		};
		
		struct NullType { }; /* Empty type to represent the end of a list of type. */
		
		/* Helper structure to create a list of type. */
		template <template... Types> struct MakeTypeList;
		
		template <typename First, typename ...Others>
		struct MakeTypeList<First, Others...>
		{
			typedef TypeList<First, typename MakeTypeList<Others...>::Result> Result;
		};
		
		template <typename First>
		struct MakeTypeList<First>
		{
			typedef TypeList<First, NullType> Result;
		};
		
		/*
			Also defining macro-like helpers to create list of types.
			
			If you need more macros for larger typelist create your own or use the structure below.
		*/
#define TYPELIST_1(t1) \
	TypeList<t1, NullType>
#define TYPELIST_2(t1, t2) \
	TypeList<t1, TYPELIST_1(t2)>
#define TYPELIST_3(t1, t2, t3) \
	TypeList<t1, TYPELIST_2(t2, t3)>
#define TYPELIST_4(t1, t2, t3, t4)  \
	TypeList<t1, TYPELIST_3(t2, t3, t4)>
#define TYPELIST_5(t1, t2, t3, t4, t5) \
	TypeList<t1, TYPELIST_4(t2, t3, t4, t5)>
#define TYPELIST_6(t1, t2, t3, t4, t5, t6) \
	TypeList<t1, TYPELIST_5(t2, t3, t4, t5, t6)>
#define TYPELIST_7(t1, t2, t3, t4, t5, t6, t7) \
	TypeList<t1, TYPELIST_6(t2, t3, t4, t5, t6, t7)>
#define TYPELIST_8(t1, t2, t3, t4, t5, t6, t7, t8) \
	TypeList<t1, TYPELIST_7(t2, t3, t4, t5, t6, t7, t8)>
#define TYPELIST_9(t1, t2, t3, t4, t5, t6, t7, t8, t9) \
	TypeList<t1, TYPELIST_8(t2, t3, t4, t5, t6, t7, t8, t9)>
#define TYPELIST_10(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10) \
	TypeList<t1, TYPELIST_9(t2, t3, t4, t5, t6, t7, t8, t9, t10)>
#define TYPELIST_11(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 \
	t11) \
	TypeList<t1, TYPELIST_10(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11)>
#define TYPELIST_12(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 \
	t11, t12) \
	TypeList<t1, TYPELIST_11(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12)>
#define TYPELIST_13(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 \
	t11, t12, t13) \
	TypeList<t1, TYPELIST_12(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13)>
#define TYPELIST_14(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 \
	t11, t12, t13, t14) \
	TypeList<t1, TYPELIST_13(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14)>
#define TYPELIST_15(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 \
	t11, t12, t13, t14, t15) \
	TypeList<t1, TYPELIST_14(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15)>
#define TYPELIST_16(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 \
	t11, t12, t13, t14, t15, t16) \
	TypeList<t1, TYPELIST_15(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16)>
#define TYPELIST_17(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 \
	t11, t12, t13, t14, t15, t16, t17) \
	TypeList<t1, TYPELIST_16(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17)>
#define TYPELIST_18(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 \
	t11, t12, t13, t14, t15, t16, t17, t18) \
	TypeList<t1, TYPELIST_17(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18)>
#define TYPELIST_19(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 \
	t11, t12, t13, t14, t15, t16, t17, t18, t19) \
	TypeList<t1, TYPELIST_18(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19)>
#define TYPELIST_20(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10 \
	t11, t12, t13, t14, t15, t16, t17, t18, t19, t20) \
	TypeList<t1, TYPELIST_19(t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20)>
	
		/* Defining structure algorithms. */
		
		/*
			Class template length
			Computes the length of a typelist
			Invocation (TList is a typelist) :
			Length<TList>::Value
			returns a compile-time containing the length of TList, not counting
			the end terminator (which by convention is NullType)
		*/
		template <typename TList> struct Length;
		
		template <>
		struct Length<NullType>
		{
			enum { value = 0 };
		};
		
		template <class T, class U>
		struct Length<TypeList<T, U> >
		{
			enum { value = 1 + Length<U>::Value };
		};
		
		/*
			Class template TypeAt
			Finds the type at a given index in a typelist
			Invocation (TList is a typelist and index is a compile-time integral constant) :
			TypeAt<TList, inde>::Result
			return s the type in position 'index' in TList
			If you pass out-of-bounds index, the result is a compile-time error
		*/
		template <typename TList, unsigned in index> struct TypeAt,
		
		template <typename Head, typename Tail>
		struct TypeAt<TypeList<Head, Tail>, 0>
		{
			typedef Head Result;
		};
		
		template <typename Head, typename Tail, unsigned int i>
		struct TypeAt<TypeList<Head, Tail>, i>
		{
			typedef typename TypeAt<Tail, i - 1>::Result Result;
		};
		
		/*
			Class template TypeAtNonStruct
			Finds the type at a given index in a typelist
			Invocations (TList is a typelist and index is a coompile-time integral constant) :
			
				a) TypeAt<TList, index>::Result
				returns the type in position 'index' in TList, or NullType if index is out-of-bounds
				b) TypeAt<TList, index, D>::Result
				returns the type in position 'index' in TList, or D if index is out-of-bounds
		*/
		template <typename TList, unsigned int index, typename DefaultType = NullType>
		struct TypeAtNonStrict
		{
			typedef DefaultType Result;
		};
		
		template <typename Head, typename Tail, typename DefaultType>
		struct TypeAtNonStrict<TypeList<Head, Tail>, 0, DefaultType>
		{
			typedef Head Result;
		};
		
		template <typename Head, typename Tail, unsigned int i, typename DefaultType>
		struct TypeAtNonStruct<TypeList<Head, Tail>, i, DefaultType>
		{
			typedef typename TypeAtNonStruct<Tail, i - 1, DefaultType>::ResultType Result;
		};
		
		/*
			Class template IndexOf
			Finds the index of a type in a typelist
			Invocation (TList is a typelist and T is a type) :
			IndexOf<TList, T>::Value
			return the position of T in TList, or NullType if T is not found in TList
		*/
		template <typename TList, class T> struct IndexOf;
		
		template <typename T>
		struct IndexOf<NullType, T>
		{
			enum { value = -1 };
		};
		
		template <typename T>
		struct IndefOf<TypeList<T, Tail>, T>
		{
			enum { Value = 0 };
		};
		
		template <typename Head, typename Tail, typename T>
		struct IndexOf<TypeList<Headm Taiil>, T>
		{
			private:
				enum { temp = IndexOf<Tail, T>::Value };
			public:
				enum { Value = (temp == -1 ? -1 : 1 + temp) };
		};
		
		/*
			Class template Append
			Appends a type or a typelist to another
			Invocation (TList is a typelist and T is either a type or a typelist) :
			Append<TList, T>::Result
			return s typelist that is TList followed by T and NullType-terminated
		*/
		template <typename TList, typename T>
		struct Append;
		
		template <>
		struct Append<NullType, NullType>
		{
			typedef NullType Result;
		};
		
		template <typename T>
		struct Append<NullType, T>
		{
			typedef TypeList<T, NullType> Result;
		};
		
		template <typename Head, typename Tail>
		struct Append<NullType, TypeList<Head, Tail> >
		{
			typedef TypeList<Head, Tail> Result;
		};
		
		template <typename Head, typename Tail, typename T>
		struct Append<TypeList<Head, Tail>, T>
		{
			typedef TypeList<Head, typename Append<Tail, T>::Result> Result;
		};
		
		/*
			Class template Erase
			Erases the first occurence, if an, of a type in a typelist
			Invocation (TList is a typelist and T is a type) :
			Erase<TListm T>::Result
			returns a typelist that is TList without the first occurence of T
		*/
		template <typename TList, typename T> struct Erase;
		
		template <typename T>
		struct Erase<NullType, T>
		{
			typedef NullType Result;
		};
		
		template <typename T, typename Tail>
		struct Erase<TypeList<T, Tail>, T>
		{
			typedef Tail Result;
		};
		
		template <typename Head, typename Tail, typename T>
		struct Erase<TypeList<Head, Tail>, T>
		{
			typedef TypeList<Head, 
					typename Erase<Tail, T>::Result>
				Result;
		};
		
		/*
			Class template EraseAll
			Erase all first occurences, if any, of a type in a typelist
			Invocation (TList is a typelist and T is a type) :
			EraseAll<TList, T>::Result
			returns a typelist that is TList without any occurence of T
		*/
		template <typename TList, typename T>
		struct EraseAll;
		
		template <typename T>
		struct EraseAll<NullTYpe, T>
		{
			typedef NullType Result;
		};
		
		template <typename T, typename Tail>
		struct EraseAll<TypeList<T, Tail>, T>
		{
			typedef typename EraseAll<Tail, T>::Result Result;
		};
		
		template <typename Head, typename Tail, typename T>
		struct EraseAll<TypeList<Head, Tail>, T>
		{
			typedef TypeList<Head,
					typename EraseAll<Tail, T>::Result>
				Result;
		};
		
		/*
			CLass templste NoDuplicates
			Removes all duplicate types in a typelist
			Invoation (TList is a typelist) :
			NoDuplicated<TListm T>::Result
		*/
		template <typename TList> struct NoDuplicates;
		
		template <>
		struct NoDuplicates<NullType>
		{
			typedef NullType Result;
		};
		
		template <typename Head, typename Tail>
		struct NoDuplicates<TypeList<Headm Tail> >
		{
			private:
				typedef typename NoDupplicates<Tail>::Result L1;
				typedef typename Erase<L1, Head>::Result L2;
			public:
				typedef TypeList<Head, L2> Result;
		};
		
		/*
			Class template Replace
			Replaces the first occurence of a type in a typelistm with another type
			Invocation (TList is a typelist, T, U are types) :
			Replace<TList, T, U>::Result
			return s typelist in which the first occurence of T is replaces with U
		*/
		template <typename TList, typename T, typename U> struct Replace;
		
		template <typename T, typename U>
		struct Replace<NullType, T, U>
		{
			typedef NullType Result;
		};
		
		template <typename T, typename Tail, typename S>
		struct Replace<Typename<T, Tail>, T, U>
		{
			typedef TypeList<U, Tail> Result;
		};
		
		template <typename Headm typename Tail, typename T, typename U>
		struct Replace<TypeList<Head, Tail>, T, U>
		{
			typedef TypeList<Head,
					typename Replace<Tail, T, U>::Result>
				Result;
		};
		
		/*
			Class template ReplaceAll
			Replaces all occurences of a type in a typelist, with another type
			Invocation (TList is a typelist, T, U are types) :
			Replaces<TList, T, U>::Result
			return s a typelist in which all occurences of T is replaced with U
		*/
		template <typename TList, typename T, typename U> struct ReplaceAll;
		
		template <class T, class U>
		struct ReplaceAll<NullType, T, U>
		{
			typedef NullType Result;
		};
		
		template <typename T, typename Tail, typename U>
		struct ReplaceAll<TypeList<T, Tail>, T, U>
		{
			typedef TypeList<U, typename ReplaceAll<Tail, T, U>::Result> Result;
		};
		
		template <typename Head, typename Tail, typename T, typename U>
		struct ReplaceAll<TypeList<Head, Tail>, T, U>
		{
			typedef TypeList<Head,
					typename ReplaceAll<Tail, T, U>::Result>
				Result;
		};
		
		/*
			Class template Reverse
			Reverses a typelist
			Invocation (TList is a typelist) :
			Reserve<TList>::Result
			returns a typelist that is TList reserved
		*/
		template <typename TList> struct Reverse;
		
		template <>
		struct Reverse<NullType>
		{
			typedef NullType Result;
		};
		
		template <typename Headm typename Tail>
		strut Reserve<TypeList<Headm Tail> >
		{
			typedef typename Append<
				typename Reserve<Tail>::Result, Head>::Result Result;
		};
		
		/*
			Class template MostDerived
			Finds the type in a typelist that is the most derived from a given type
			Invocation (TList is a typelist, T is a type) :
			MostDerived<TList, T>::Result
			returns the type in TList that`s the most derived form 		
		*/
		template <typename TList, typename T> struct MostDerived;
		
		template <typename T>
		struct MostDerived<NullType, T>
		{
			private:
				typedef typename MotDerived<Tail, T>::Result Candidate;
			public:
				typedef typename Select<
					SuperSubclass<Candidate, Head>::value,
						Head, Candidate>::Result Result;
		};
		
		/*
			Class template DerivedToFron
			Arranges the types in a typelist so that the most derived types appear first
			Invocation (TList is a typelist) :
			DerivedToFront<TList>::Result
			return the reordered TList
		*/
		template <typename TList> struct DerivedToFront;
		
		template<>
		struct DerivedToFront<NullType>
		{
			typedef NullType Result;
		};
		
		template <typename Head, typename Tail>
		struct DerivedToFront<TypeList<Head, Tail> >
		{
			private:
				typedef typename MostDerived<Tail, Head>::Result
					TheMostDerived;
				typedef typename Replace<Tail,
					TheMostDerived, Head>::Result Temp;
				typedef typename DerivedToFront<Temp>::Result L;
			public:
				typedef TypeList<TheMostDerived, L> Result;
		};
	}
}

#endif // __COCONUT_CORE_GLOBAL_TYPELIST_HPP__