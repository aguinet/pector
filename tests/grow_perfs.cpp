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
//#include "bench.h"

#include <chrono>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#define NRUNS 9

#if defined _WIN32 || defined __APPLE__
#   warning NOT supported on this platform
void *malloc_get_state()
{
    return nullptr;
}
void malloc_set_state(void *)
{
}
#endif

template <class V>
double one_run(int const N)
{
	V v;
	const auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < N; i++) {
		v.emplace_back(i);
	}
	const auto end = std::chrono::steady_clock::now();
	return (double)(std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count())/1000.0;
}

template <class V>
double perf_N(const char* name, int const N)
{
	double runs[NRUNS];
	for (size_t i = 0; i < NRUNS; i++) {
		void* state = malloc_get_state();
		runs[i] = one_run<V>(N);
		malloc_set_state(state);
	}

	std::sort(std::begin(runs), std::end(runs));
	double sum = 0;
	for (size_t i = 2; i <= NRUNS-2; i++) {
		sum += runs[i];
	}
	const double mean = (sum/(NRUNS-3));

	std::cout << name << ": " << N << " add in " << (mean*1000.0) << " ms" << std::endl;
	return mean;
}

#define WRITE_PERFS(ar, n_start, n_step, n_end)\
	write_perfs(#ar ".csv", ar, n_start, n_step, n_end)

void write_perfs(const char* file, double* values, size_t n_start, size_t n_step, size_t n_end)
{
	std::ofstream ofs(file, std::ofstream::out);
	size_t i = 0;
	for (size_t N = n_start; N <= n_end; N += n_step) {
		ofs << N << "," << values[i]*1000.0 << std::endl;
		i++;
	}
}

int main(int argc, char** argv)
{
	if (argc < 4) {
		std::cerr << "Usage: " << argv[0] << " N_start N_step N_end" << std::endl;
		return 1;
	}
	size_t N_start = atoll(argv[1]);
	size_t N_step = atoll(argv[2]);
	size_t N_end = atoll(argv[3]);

	const size_t S = (N_end-N_start+1)/N_step + 1;

	double* std_alloc_15 = new double[S];
	double* std_alloc_2 = new double[S];
	double* realloc_nsw_15 = new double[S];
	double* realloc_nsw_2 = new double[S];
	double* realloc_sw_15 = new double[S];
	double* realloc_sw_2 = new double[S];
	double* std_vector = new double[S];

	size_t i = 0;
	for (size_t N = N_start; N <= N_end; N += N_step) {
		std::cout << "N = " << N << std::endl;
		std_alloc_15[i]   = perf_N<pector<int, std::allocator<int>, size_t, recommended_size_multiply_by<3,2>, false>>("std::allocator, multiply by 1.5", N);
		std_alloc_2[i]    = perf_N<pector<int, std::allocator<int>, size_t, recommended_size_multiply_by<2,1>, false>>("std::allocator, multiply by 2", N);
		realloc_nsw_15[i] = perf_N<pector<int, malloc_allocator<int, true, false>, size_t, recommended_size_multiply_by<3,2>, false>>("malloc_allocator, reallocable, not size aware, multiply by 1.5", N);
		realloc_nsw_2[i]  = perf_N<pector<int, malloc_allocator<int, true, false>, size_t, recommended_size_multiply_by<2,1>, false>>("malloc_allocator, reallocable, not size aware, multiply by 2", N);
		realloc_sw_15[i]  = perf_N<pector<int, malloc_allocator<int, true, true>, size_t, recommended_size_multiply_by<3,2>, false>>("malloc_allocator, reallocable, size aware, multiply by 1.5", N);
		realloc_sw_2[i]   = perf_N<pector<int, malloc_allocator<int, true, true>, size_t, recommended_size_multiply_by<2,1>, false>>("malloc_allocator, reallocable, size aware, multiply by 2", N);
		std_vector[i]     = perf_N<std::vector<int>>("std::vector, standard allocator", N);
		std::cout << std::endl;
		i++;
	}

	WRITE_PERFS(std_alloc_15, N_start, N_step, N_end);
	WRITE_PERFS(std_alloc_2, N_start, N_step, N_end);
	WRITE_PERFS(realloc_nsw_15, N_start, N_step, N_end);
	WRITE_PERFS(realloc_nsw_2, N_start, N_step, N_end);
	WRITE_PERFS(realloc_sw_15, N_start, N_step, N_end);
	WRITE_PERFS(realloc_sw_2, N_start, N_step, N_end);
	WRITE_PERFS(std_vector, N_start, N_step, N_end);

	delete [] std_alloc_15;
	delete [] std_alloc_2;
	delete [] realloc_nsw_15;
	delete [] realloc_nsw_2;
	delete [] realloc_sw_15;
	delete [] realloc_sw_2;
	delete [] std_vector;
	
	return 0;
}
