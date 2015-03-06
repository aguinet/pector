#include <pector/pector.h>
#include "types_test.h"

#include <iostream>

int multiply_by()
{
	pector<A, std::allocator<A>, uint8_t, recommended_size_multiply_by<3,2>> v;
	// 169 is the limit before we will be close to max_size
	v.resize(169);
	v.emplace_back(1);
	if (v.capacity() != 254) {
		std::cerr << "overflow occured in the capacity computation!" << std::endl;
		return 1;
	}
	v.resize_fit(180);
	v.emplace_back(1);
	if (v.capacity() != 255) {
		std::cerr << "overflow occured in the capacity computation!" << std::endl;
		return 1;
	}
	v.resize(254);
	v.emplace_back(1);
	try {
		v.emplace_back(2);
	}
	catch (std::length_error const&) {
		std::cerr << "got overflow exception" << std::endl;
		return 0;
	}

	std::cerr << "should have caught an overflow exception!" << std::endl;
	return 1;
}

int add_by()
{
	pector<A, std::allocator<A>, uint8_t, recommended_size_add_by<50>> v;
	// 169 is the limit before we will be close to max_size
	v.resize(205);
	v.emplace_back(1);
	if (v.capacity() != 255) {
		std::cerr << "overflow occured in the capacity computation!" << std::endl;
		return 1;
	}
	return 0;
}

int main()
{
	int ad = add_by();
	int mb = multiply_by();
	return ad | mb;
}
