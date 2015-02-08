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
	v.resize(5);
	for (int i = 0; i < 5; i++) {
		v[i] = i;
	}
	std::vector<A> ar({A(10), A(11)});
	v.insert(v.cbegin()+1, ar.begin(), ar.end());

	V ref({A(0), A(10), A(11), A(1), A(2), A(3), A(4)});
	if (!cmp(v, ref)) {
		std::cerr << "Insert begin+1 failed!" << std::endl;
		return 1;
	}

	v.insert(v.cbegin(), ar.begin(), ar.end());
	V ref1({A(10), A(11), A(0), A(10), A(11), A(1), A(2), A(3), A(4)});
	if (!cmp(v, ref1)) {
		std::cerr << "Insert begin failed!" << std::endl;
		return 1;
	}

	v.insert(v.cend(), ar.begin(), ar.end());
	V ref2({A(10), A(11), A(0), A(10), A(11), A(1), A(2), A(3), A(4), A(10), A(11)});
	if (!cmp(v, ref2)) {
		std::cerr << "Insert end failed!" << std::endl;
		return 1;
	}
	return 0;
}

template <class V>
int test2(V& v)
{
	typedef typename V::value_type A;
	v.resize(2);
	for (int i = 0; i < 2; i++) {
		v[i] = i;
	}
	std::vector<A> ar({A(10), A(11), A(12), A(13), A(14)});
	v.insert(v.cbegin()+1, ar.begin(), ar.end());

	V ref({A(0), A(10), A(11), A(12), A(13), A(14), A(1)});
	if (!cmp(v, ref)) {
		std::cerr << "Insert begin+1 failed!" << std::endl;
		return 1;
	}

	v.insert(v.cbegin(), ar.begin(), ar.end());
	V ref1({A(10), A(11), A(12), A(13), A(14), A(0), A(10), A(11), A(12), A(13), A(14), A(1)});
	if (!cmp(v, ref1)) {
		std::cerr << "Insert begin failed!" << std::endl;
		return 1;
	}

	v.insert(v.cend(), ar.begin(), ar.end());
	V ref2({A(10), A(11), A(12), A(13), A(14), A(0), A(10), A(11), A(12), A(13), A(14), A(1), A(10), A(11), A(12), A(13), A(14)});
	if (!cmp(v, ref2)) {
		std::cerr << "Insert end failed!" << std::endl;
		return 1;
	}

	v.insert(v.cend(), 2, A(20));
	V ref4({A(10), A(11), A(12), A(13), A(14), A(0), A(10), A(11), A(12), A(13), A(14), A(1), A(10), A(11), A(12), A(13), A(14), A(20), A(20)});
	if (!cmp(v, ref4)) {
		std::cerr << "Insert (count,value) to the end failed!" << std::endl;
		return 1;
	}

	v.emplace(v.cbegin()+5, 21);
	V ref5({A(10), A(11), A(12), A(13), A(14), A(21), A(0), A(10), A(11), A(12), A(13), A(14), A(1), A(10), A(11), A(12), A(13), A(14), A(20), A(20)});
	if (!cmp(v, ref5)) {
		std::cerr << "emplace to begin+5 failed!" << std::endl;
		return 1;
	}

	v.insert(v.cbegin(), 2, A(40));
	V ref6({A(40), A(40), A(10), A(11), A(12), A(13), A(14), A(21), A(0), A(10), A(11), A(12), A(13), A(14), A(1), A(10), A(11), A(12), A(13), A(14), A(20), A(20)});
	if (!cmp(v, ref6)) {
		std::cerr << "emplace to begin+5 failed!" << std::endl;
		return 1;
	}

	v.insert(v.cbegin()+1, 2, A(41));
	V ref7({A(40), A(41), A(41), A(40), A(10), A(11), A(12), A(13), A(14), A(21), A(0), A(10), A(11), A(12), A(13), A(14), A(1), A(10), A(11), A(12), A(13), A(14), A(20), A(20)});
	if (!cmp(v, ref7)) {
		std::cerr << "emplace to begin+5 failed!" << std::endl;
		return 1;
	}

	v.insert(v.cbegin(), std::move(A(100)));
	V ref8({A(100), A(40), A(41), A(41), A(40), A(10), A(11), A(12), A(13), A(14), A(21), A(0), A(10), A(11), A(12), A(13), A(14), A(1), A(10), A(11), A(12), A(13), A(14), A(20), A(20)});
	if (!cmp(v, ref8)) {
		std::cerr << "insert to begin + std::move failed!" << std::endl;
		return 1;
	}

	A a_(101);
	v.insert(v.cbegin()+4, a_);
	V ref9({A(100), A(40), A(41), A(41), A(101), A(40), A(10), A(11), A(12), A(13), A(14), A(21), A(0), A(10), A(11), A(12), A(13), A(14), A(1), A(10), A(11), A(12), A(13), A(14), A(20), A(20)});
	if (!cmp(v, ref9)) {
		std::cerr << "insert to begin + copy failed!" << std::endl;
		return 1;
	}

	v.insert(v.cbegin()+7, {A(60), A(61)});
	V ref10({A(100), A(40), A(41), A(41), A(101), A(40), A(10), A(60), A(61), A(11), A(12), A(13), A(14), A(21), A(0), A(10), A(11), A(12), A(13), A(14), A(1), A(10), A(11), A(12), A(13), A(14), A(20), A(20)});
	if (!cmp(v, ref10)) {
		std::cerr << "insert to begin + copy failed!" << std::endl;
		return 1;
	}
	return 0;
}

template <class V>
int test_no_reserve()
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

template <class V>
int test_reserve()
{
	int ret = 0;
	{
		V v;
		v.reserve(100);
		ret |= test1(v);
	}
	{
		V v;
		v.reserve(100);
		ret |= test2(v);
	}
	return ret;
}

int main()
{
	int ret = 0;
	ret |= test_no_reserve<pector_int>();
	ret |= test_reserve<pector_int>();
	ret |= test_no_reserve<pector_a>();
	ret |= test_reserve<pector_a>();

	ret |= test_no_reserve<pector_int_ea>();
	ret |= test_reserve<pector_int_ea>();
	ret |= test_no_reserve<pector_a_ea>();
	ret |= test_reserve<pector_a_ea>();

	return ret;
}
