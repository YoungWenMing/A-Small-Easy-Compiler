#ifndef GLOBAL_DEF_H
#define GLOBAL_DEF_H

#include <assert.h>

#if DEBUG

#define DCHECK(condition) assert(condition);
#else
#define DCHECK(condition) (void)0
#endif

#endif // GLOBAL_DEF_H
