// This file is part of pector (https://github.com/aguinet/pector).
// Copyright (C) 2014-2015 Adrien Guinet <adrien@guinet.me> 
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

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
