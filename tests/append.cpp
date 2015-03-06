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

int main()
{
	int ret = 0;

	pector_int v;
	for (int i = 0; i < 20; i++) {
		v.push_back(i);
	}

	if (v.size() != 20) {
		std::cerr << "invalid size!" << std::endl;
		ret = 1;
	}

	size_t cur_capacity = v.capacity();

	v.reserve(10);
	if (v.capacity() != cur_capacity) {
		std::cerr << "resize 10 failure" << std::endl;
		ret = 1;
	}
	v.reserve(40);
	if (v.capacity() != 40) {
		std::cerr << "reserve 40 failure" << std::endl;
		ret = 1;
	}

	for (int i = 20; i < 40; i++) {
		v.emplace_back(i);
	}

	if (v.size() != 40) {
		std::cerr << "invalid size!" << std::endl;
		ret = 1;
	}

	for (int i = 0; i < (int)v.size(); i++) {
		if (v.at(i) != i) {
			std::cerr << "error at " << i << std::endl;
			ret = 1;
		}
	}

	pector_a va;
	for (int i = 0; i < 20; i++) {
		va.push_back(A(i));
	}

	if (va.size() != 20) {
		std::cerr << "invalid size!" << std::endl;
		ret = 1;
	}

	cur_capacity = va.capacity();

	va.reserve(10);
	if (va.capacity() != cur_capacity) {
		std::cerr << "resize 10 failure" << std::endl;
		ret = 1;
	}
	va.reserve(40);
	if (va.capacity() != 40) {
		std::cerr << "reserve 40 failure" << std::endl;
		ret = 1;
	}

	for (int i = 20; i < 40; i++) {
		va.emplace_back(i);
	}

	if (va.size() != 40) {
		std::cerr << "invalid size!" << std::endl;
		ret = 1;
	}

	for (int i = 0; i < (int)v.size(); i++) {
		if (!va.at(i).equals(i)) {
			std::cerr << "error at " << i << std::endl;
			ret = 1;
		}
	}

	pector_a vas;
	vas.resize(4, A(1));
	for (int i = 0; i < 4; i++) {
		if (!vas.at(i).equals(1)) {
			std::cerr << "error on resize with an object at " << i << std::endl;
			ret = 1;
		}
	}

	for (int i = 0; i < 4; i++) {
		vas.pop_back();
		if (vas.size() != (size_t)(3-i)) {
			std::cerr << "size error!" << std::endl;
			ret = 1;
		}
	}

	vas.reserve(40);
	vas.push_back(A(0));
	vas.push_back(A(1));
	vas.shrink_to_fit();
	if (vas.size() != 2 || vas.capacity() != 2) {
		std::cerr << "error with shrink_to_fit" << std::endl;
		ret = 1;
	}

	return ret;
}
