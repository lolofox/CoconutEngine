#include "coconutglobal.hpp"

namespace CoconutEngine
{
	const char* coconutVersion() COCONUT_DECL_NOTHROW
	{
		return COCONUT_VERSION_STR;
	}
	
	bool coconutSharedBuild() COCONUT_DECL_NOTHROW
	{
#ifdef COCONUT_SHARED
		return true;
#else
		return false;
#endif
	}
}