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


#include <iostream>


#include <pector/pector.h>
#include "types_test.h"

template <class V>
int test_no_ea()
{
	typedef typename V::value_type A;
	V v;
	v.resize(10);
	A* pfirst = &v[0];
	for (int i = 0; i < 10; i++) {
		v[i] = i;
	}
	v.shrink_to_fit();
	if (&v[0] != pfirst) {
		std::cerr << "shrink_to_fit should'nt have done nothing!" << std::endl;
		return 1;
	}

	v.resize_fit(4);
	if (&v[0] == pfirst) {
		std::cerr << "pointer to data stored should'nt be the same!" << std::endl;
		return 0;
	}
	V vref({A(0), A(1), A(2), A(3)});
	if (!cmp(v, vref)) {
		std::cerr << "invalid values after resize_fit" << std::endl;
		return 1;
	}

	return 0;
}

template <class V>
int test_ea()
{
	typedef typename V::value_type A;
	V v;
	v.resize(10);
	for (int i = 0; i < 10; i++) {
		v[i] = i;
	}
	v.shrink_to_fit();
	v.resize_fit(4);
	V vref({A(0), A(1), A(2), A(3)});
	if (!cmp(v, vref)) {
		std::cerr << "invalid values after resize_fit" << std::endl;
		return 1;
	}
	v.resize_no_construct(6);
	new (&v[4]) A(4);
	new (&v[5]) A(5);
	V vref2({A(0), A(1), A(2), A(3), A(4), A(5)});
	if (!cmp(v, vref2)) {
		std::cerr << "invalid values after resize_no_construct" << std::endl;
		return 1;
	}

	return 0;
}

int main()
{
	int ret = 0;

	ret |= test_no_ea<pector_int>();
	ret |= test_no_ea<pector_a>();

	ret |= test_ea<pector_int_ea>();
	ret |= test_ea<pector_a_ea>();

	return ret;
}
