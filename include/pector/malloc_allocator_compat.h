#ifndef PECTOR_MALLOC_ALLOCATOR_COMPAT_H
#define PECTOR_MALLOC_ALLOCATOR_COMPAT_H

#ifdef __APPLE__
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif

#if defined __linux__ || defined __gnu_hurd__ || defined _WIN32 || defined __APPLE__ || defined __FreeBSD__

#define PT_SIZE_AWARE_COMPAT

#if defined _WIN32
#define PT_MALLOC_USABLE_SIZE(p) _msize(p)
#elif defined __APPLE__
#define PT_MALLOC_USABLE_SIZE(p) malloc_size(p)
#elif defined __gnu_hurd__ || __linux__ || defined __FreeBSD__
#define PT_MALLOC_USABLE_SIZE(p) malloc_usable_size(p)
#endif

#endif // defined __GNUC__ || defined _WIN32 || defined __APPLE__


#endif
