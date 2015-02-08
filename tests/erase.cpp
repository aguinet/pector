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
#include <string>
#include <sstream>
#include <vector>

#include <pector/pector.h>
#include "types_test.h"

template <class V>
int test1(V& v)
{
	typedef typename V::value_type A;
	v.resize(8);
	for (int i = 0; i < 8; i++) {
		v[i] = i;
	}
	v.erase(v.cend()-1);

	V ref0({A(0), A(1), A(2), A(3), A(4), A(5), A(6)});
	if (!cmp(v, ref0)) {
		std::cerr << "erase last failed!" << std::endl;
		return 1;
	}

	v.erase(v.cbegin()+3);

	V ref({A(0), A(1), A(2), A(4), A(5), A(6)});
	if (!cmp(v, ref)) {
		std::cerr << "erase begin+3 failed!" << std::endl;
		return 1;
	}

	v.erase(v.cbegin()+1, v.cbegin()+4);
	V ref1({A(0), A(5), A(6)});
	if (!cmp(v, ref1)) {
		std::cerr << "erase range failed" << std::endl;
		return 1;
	}

	v.erase(v.cbegin()+1);
	V ref5({A(0), A(6)});
	if (!cmp(v, ref5)) {
		std::cerr << "erase middle failed" << std::endl;
		return 1;
	}

	v.erase(v.cbegin());
	V ref2({A(6)});
	if (!cmp(v, ref2)) {
		std::cerr << "erase begin failed" << std::endl;
		return 1;
	}

	v.erase(v.cend()-1);
	V ref4({});
	if (!cmp(v, ref4)) {
		std::cerr << "erase last bis failed" << std::endl;
		return 1;
	}
	return 0;
}

template <class V>
int test2(V& v)
{
	v.resize(5);
	for (int i = 0; i < 5; i++) {
		v[i] = i;
	}
	v.erase(v.cbegin(), v.cend());
	if (v.size() != 0) {
		std::cerr << "error erase all!" << std::endl;
		return 1;
	}
	return 0;
}

template <class V>
int test_all()
{
	int ret = 0;
	{
		V v;
		ret |= test1(v);
	}
	{
		V v;
		ret |= test2(v);
	}
	return ret;
}

int main()
{
	int ret = 0;
	ret |= test_all<pector_int>();
	ret |= test_all<pector_int_ea>();
	ret |= test_all<pector_a>();
	ret |= test_all<pector_a_ea>();

	return ret;
}
