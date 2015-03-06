#include <cstdlib>
#include <cstdint>
#include <chrono>
#include <iostream>
#include <vector>
#include <pector/pector.h>

template <class T>
__attribute__((noinline)) T* sum(size_t const n, T* a, T* b)
{
	T* ret = (T*) malloc(sizeof(T)*n);
	for (size_t i = 0; i < n; i++) {
		ret[i] = a[i] + b[i];
	}
	return ret;
}

template <class T>
__attribute__((noinline)) T* sum_memset(size_t const n, T* a, T* b)
{
	T* ret = (T*) malloc(sizeof(T)*n);
	memset(ret, 0, sizeof(T)*n);
	for (size_t i = 0; i < n; i++) {
		ret[i] = a[i] + b[i];
	}
	return ret;
}

template <class T>
__attribute__((noinline)) std::vector<T> sum_vec(size_t const n, T* a, T* b)
{
	std::vector<T> ret;
	ret.resize(n);
	for (size_t i = 0; i < n; i++) {
		ret[i] = a[i] + b[i];
	}
	return std::move(ret);
}

template <class T>
__attribute__((noinline)) std::vector<T> sum_vec_reserve(size_t const n, T* a, T* b)
{
	std::vector<T> ret;
	ret.reserve(n);
	for (size_t i = 0; i < n; i++) {
		ret.emplace_back(a[i] + b[i]);
	}
	return std::move(ret);
}

template <class T>
__attribute__((noinline)) pt::pector<T> sum_pector(size_t const n, T* a, T* b)
{
	pt::pector<T> ret;
	ret.resize_no_construct(n);
	for (size_t i = 0; i < n; i++) {
		ret[i] = a[i] + b[i];
	}
	return std::move(ret);
}

template <class T, class F>
void bench(const char* name, size_t const n, F const& f)
{
	f();
	auto start = std::chrono::steady_clock::now();
	f();
	auto end = std::chrono::steady_clock::now();

	double time_s = ((double)std::chrono::duration_cast<std::chrono::microseconds>(end-start).count())/1000000.0;
	std::cout << name << ": " << time_s*1000.0 << "ms\t" << (double)(n*sizeof(T)*2)/(1024.0*1024.0*time_s) << " MB/s" << std::endl;
}

template <class T>
void do_bench(const char* name, size_t const n)
{
	T* a = new T[n];
	T* b = new T[n];
	T* ret = new T[n];

	for (size_t i = 0; i < n; i++) {
		a[i] = rand();
		b[i] = rand();
	}

	std::cout << name << std::endl;
	bench<T>("original", n, [=] { return sum<T>(n,a,b); });
	bench<T>("sum_pector",  n, [=] { return sum_pector<T>(n,a,b); });
	bench<T>("original+memset", n, [=] { return sum_memset<T>(n,a,b); });
	bench<T>("sum_vec",  n, [=] { return sum_vec<T>(n,a,b); });
	bench<T>("sum_vec_reserve",  n, [=] { return sum_vec_reserve<T>(n,a,b); });
	std::cout << "-------" << std::endl << std::endl;

	delete [] a;
	delete [] b;
	delete [] ret;
}

int main(int argc, char** argv)
{
	size_t n = atoll(argv[1]);

	do_bench<int>("int", n);
	do_bench<short>("short", n);

	return 0;
}
