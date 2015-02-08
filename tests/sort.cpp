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

#include <algorithm>
#include <random>
#include <iostream>

template <class Iter>
int check_vec(Iter begin, Iter end)
{
	int ret = 0;
	int i = 0;
	for (; begin != end; begin++) {
		if (*begin != i) {
			std::cerr << "error at " << i << ": " << *begin << std::endl;
			ret = 1;
		}
		i++;
	}
	return ret;
}

int main()
{
	int ret = 0;
	pector_int v;
	v.resize(40);
	for (int i = 0; i < 40; i++) {
		v[i] = i;
	}

	std::random_shuffle(v.begin(), v.end());
	std::sort(v.begin(), v.end());
	ret |= check_vec(v.begin(), v.end());

	std::random_shuffle(v.rbegin(), v.rend());
	std::sort(v.rbegin(), v.rend());
	ret |= check_vec(v.rbegin(), v.rend());

	return ret;
}
