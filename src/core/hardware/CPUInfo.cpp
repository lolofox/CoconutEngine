#include "CPUInfo.hpp"

extern int cpuid_check(void);
extern void cpuid_get(int op, int *eax, int *ebx, int *ecx, int *edx);