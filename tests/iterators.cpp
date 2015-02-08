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

template <bool is_const, class T>
int test(T& v)
{
	typedef typename std::conditional<is_const, typename T::const_iterator, typename T::iterator>::type iterator_type;

	int ret = 0;
	int c = 0;
	for (int i: v) {
		if (i != c) {
			std::cerr << "error at " << c << std::endl;
			ret = 1;
		}
		c++;
	}

	c = 19;
	for (auto it = v.rbegin(); it != v.rend(); it++) {
		if (*it != c) {
			std::cerr << "error with reverse at " << c << std::endl;
			ret = 1;
		}
		c--;
	}

	{
		iterator_type it;
		it = v.end();
		--it;
		if (*it != 19) {
			std::cerr << "error with --iterator" << std::endl;
			ret = 1;
		}
		iterator_type prev_it = it--;
		if (*it != 18 || *prev_it != 19) {
			std::cerr << "error with --iterator" << std::endl;
			ret = 1;
		}

		it -= 10;
		if (*it != 8) {
			std::cerr << "error with iterator-=10" << std::endl;
			ret = 1;
		}
	}

	{
		iterator_type it;
		it = v.begin();
		++it;
		if (*it != 1) {
			std::cerr << "error with ++iterator" << std::endl;
			ret = 1;
		}
		iterator_type prev_it = it++;
		if (*it != 2 || *prev_it != 1) {
			std::cerr << "error with --iterator" << std::endl;
			ret = 1;
		}
		it += 15;
		if (*it != 17) {
			std::cerr << "error with iterator+=15" << std::endl;
			ret = 1;
		}
	}

	{
		iterator_type it1 = v.begin();
		iterator_type it2 = v.begin();
		it2 += 5;
		if ((it2 - it1) != 5) {
			std::cerr << "error on iterator-iterator" << std::endl;
			ret = 1;
		}
		if ((it1 - it2) != -5) {
			std::cerr << "error on iterator-iterator" << std::endl;
			ret = 1;
		}
	}
	return ret;
}

int main()
{
	int ret = 0;
	pector_int v;
	for (int i = 0; i < 20; i++) {
		v.push_back(i);
	}

	ret |= test<false>(v);
	ret |= test<true>(const_cast<pector_int const&>(v));

	v.clear();
	int i = 0;
	for (auto it = v.rbegin(); it != v.rend(); it++) {
		i++;
	}
	for (int i_: v) {
		(void)i_;
		i++;
	}
	pector_int v2;
	for (auto it = v.rbegin(); it != v.rend(); it++) {
		i++;
	}
	for (int i_: v2) {
		(void)i_;
		i++;
	}
	if (i != 0) {
		std::cerr << "empty container failure" << std::endl;
		ret = 1;
	}

	return ret;
}
