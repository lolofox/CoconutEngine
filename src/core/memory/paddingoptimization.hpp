#ifndef __COCONUTENGINE_CORE_MEMORY_PADDINGOPTIMIZATION_HPP__
#define __COCONUTENGINE_CORE_MEMORY_PADDINGOPTIMIZATION_HPP__

#include "../global/typelist.hpp"

#define DECLARE_TYPES_FOR_OPTIMIZATION(...) \
	CoconutEngine::Core::MakeTypeList<__VA_ARGS__>::Result TypesForOptimization;
	
DECLARE_TYPES_FOR_OPTIMIZATION(double, float, int, short, char)

#endif // __COCONUTENGINE_CORE_MEMORY_PADDINGOPTIMIZATION_HPP__