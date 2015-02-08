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

#include <pector/pector.h>
#include "types_test.h"

int check_v(pector_int const& v)
{
	for (int i = 0; i < (int) v.size(); i++) {
		if (i != v.at(i)) {
			return 1;
		}
	}
	return 0;
}

int check_va(pector_a const& v)
{
	for (int i = 0; i < (int) v.size(); i++) {
		if (!v.at(i).equals(i)) {
			return 1;
		}
	}
	return 0;
}

int main()
{
	int ret = 0;

	{
		pector_int v;
		v.resize(20);
		for (int i = 0; i < 20; i++) {
			v[i] = i;
		}

		v = v;
		ret |= check_v(v);

		pector_int v2;
		v2 = v;
		if (&v2.front() == &v.front()) {
			std::cerr << "error copy!" << std::endl;
			ret = 1;
		}

		ret |= check_v(v2);

		int* buf = &v.front();
		pector_int vm(std::move(v));
		if ((&vm.front() != buf) || (v.size() != 0) || (v.capacity() != 0)) {
			std::cerr << "error move constructor!" << std::endl;
			ret = 1;
		}
		ret |= check_v(vm);

		pector_int vm2;
		vm2.reserve(4);
		vm2 = std::move(vm);
		if ((&vm2.front() != buf) || (vm.size() != 0) || (vm.capacity() != 0)) {
			std::cerr << "error move constructor!" << std::endl;
			ret = 1;
		}
		ret |= check_v(vm2);

		pector_a va;
		va.reserve(20);
		for (int i = 0; i < 20; i++) {
			va.emplace_back(i);
		}

		va = va;
		ret |= check_va(va);

		A* bufa = &va.front();
		pector_a vma(std::move(va));
		if ((&vma.front() != bufa) || (va.size() != 0) || (va.capacity() != 0)) {
			std::cerr << "error move constructor!" << std::endl;
			ret = 1;
		}
		ret |= check_va(vma);

		pector_a vma2;
		vma2.reserve(4);
		vma2 = std::move(vma);
		if ((&vma2.front() != bufa) || (vma.size() != 0) || (vma.capacity() != 0)) {
			std::cerr << "error move constructor!" << std::endl;
			ret = 1;
		}
		ret |= check_va(vma2);

		pector_a vac;
		vac.resize(5);
		vac = vma2;
		ret |= check_va(vac);

		pector_a vac2(vac);
		if (vac2.size() != vac.size()) {
			std::cerr << "Error on vector copy: wrong size!" << std::endl;
			ret = 1;
		}
		ret |= check_va(vac2);

	}

	{
		pector_a v1;
		pector_a v2;

		v1.resize(4);
		v2.resize(5);

		A* buf_1 = &v1.front();
		A* buf_2 = &v2.front();

		v1.swap(v2);
		if (buf_1 != &v2.front()) {
			std::cerr << "buf_1 != v2" << std::endl;
			ret = 1;
		}

		if (buf_2 != &v1.front()) {
			std::cerr << "buf_2 != v1" << std::endl;
			ret = 1;
		}

		if (v1.size() != 5 || v2.size() != 4) {
			std::cerr << "invalid sizes!" << std::endl;
			ret = 1;
		}
	}

	return ret;
}
