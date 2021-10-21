#include <cassert>

#ifdef DEBUG
	#define ASSERT(exp, msg) assert(((void)msg, exp))
#else
	#define ASSERT(exp, msg)
#endif
