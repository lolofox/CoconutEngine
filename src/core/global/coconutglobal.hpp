#ifndef __COCONUTENGINE_CORE_GLOBAL_COCONUTGLOBAL_HPP__
#define __COCONUTENGINE_CORE_GLOBAL_COCONUTGLOBAL_HPP__

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

#endif // __COCONUTENGINE_CORE_GLOBAL_COCONUTGLOBAL_HPP__