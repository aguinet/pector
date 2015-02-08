#ifndef PECTOR_TYPES_TEST_H
#define PECTOR_TYPES_TEST_H

#include <string>
#include <sstream>
#include <stdlib.h>
#include <pector/malloc_allocator.h>

using namespace pt;

typedef pector<int> pector_int;
typedef pector<int, malloc_allocator<int>> pector_int_ea;

struct A
{
	A() = default;
	A(int i)
	{
		std::stringstream ss;
		ss << i;
		s = ss.str();
	}

	bool equals(int i) const
	{
		return atoi(s.c_str()) == i;
	}

	bool operator==(int i) const { return equals(i); }
	bool operator==(A const& o) const { return s == o.s; }

private:
	std::string s;
};

typedef pector<A> pector_a;
typedef pector<A, malloc_allocator<A>> pector_a_ea;

template <class V>
static bool cmp(V const& a, V const& b)
{
	return a == b;
}


#endif
