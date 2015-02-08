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
#include <vector>

int main()
{
	int ret = 0;

	pector_a va;
	for (int i = 0; i < 20; i++) {
		va.emplace_back(i);
	}

	va.assign(4, A(5));
	if (va.size() != 4) {
		std::cerr << "wrong size!" << std::endl;
		ret = 1;
	}

	std::vector<A> sva;
	for (int i = 0; i < 10; i++) {
		sva.emplace_back(i);
	}

	va.assign(std::begin(sva), std::end(sva));
	if (va.size() != 10) {
		std::cerr << "wrong size!" << std::endl;
		ret = 1;
	}
	for (int i = 0; i < (int)va.size(); i++) {
		if (!va.at(i).equals(i)) {
			std::cerr << "wrong value at " << i << std::endl;
			ret = 1;
		}
	}

	pector_int v;
	for (int i = 0; i < 20; i++) {
		v.emplace_back(i);
	}

	v.assign((size_t) 4, 5);
	if (v.size() != 4) {
		std::cerr << "wrong size!" << std::endl;
		ret = 1;
	}

	std::vector<int> sv;
	for (int i = 0; i < 10; i++) {
		sv.emplace_back(i);
	}

	v.assign(std::begin(sv), std::end(sv));
	if (v.size() != 10) {
		std::cerr << "wrong size!" << std::endl;
		ret = 1;
	}
	for (int i = 0; i < (int)v.size(); i++) {
		if (v.at(i) != i) {
			std::cerr << "wrong value at " << i << std::endl;
			ret = 1;
		}
	}

	v.assign({0, 1, 2, 3});
	if (v.size() != 4) {
		std::cerr << "wrong size!" << std::endl;
		ret = 1;
	}
	for (int i = 0; i < (int)v.size(); i++) {
		if (v.at(i) != i) {
			std::cerr << "wrong value at " << i << std::endl;
			ret = 1;
		}
	}

	pector_int vil({0, 1, 2, 3, 4, 5, 6});
	for (int i = 0; i < (int)v.size(); i++) {
		if (vil.at(i) != i) {
			std::cerr << "wrong value at " << i << std::endl;
			ret = 1;
		}
	}

	return ret;
}
