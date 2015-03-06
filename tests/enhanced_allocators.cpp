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


#include <pector/pector.h>
#include "types_test.h"

#include <iostream>

int main()
{
	pector<A, malloc_allocator<A, true, true>> v({A(1), A(2)});
	std::cout << sizeof(v) << std::endl;

	v.emplace_back(0);
	v.emplace_back(1);
	v.emplace_back(2);
	v.emplace_back(3);
	v.emplace_back(4);
	std::cout << v.capacity() << std::endl;
	v.resize(14);
	std::cout << v.capacity() << std::endl;

	pector<A, malloc_allocator<A, true, true>> v2 = std::move(v);
	std::cout << v2.capacity() << std::endl;

	return 0;
}
