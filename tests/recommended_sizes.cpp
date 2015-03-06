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
#include <iostream>

using namespace pt;

int main()
{
	pector<int, std::allocator<int>, size_t, recommended_size_add_by<5>, false> v;
	v.emplace_back(0);
	v.emplace_back(1);
	if (v.capacity() != 5) {
		std::cerr << "capacity should be of 5" << std::endl;
		return 1;
	}
	for (size_t i = 0; i < 7; i++) {
		v.emplace_back(i+2);
	}

	if (v.capacity() != 10) {
		std::cerr << "capacity should be of 10" << std::endl;
		return 1;
	}

	return 0;
}
