#pragma once

#ifndef PECTOR_BENCH_H
#define PECTOR_BENCH_H

#include <sys/time.h>
#include <cstdlib>

static double get_current_timestamp()
{
	struct timeval curt;
	gettimeofday(&curt, NULL);
	return (double)curt.tv_sec + ((double)curt.tv_usec)/1000000.0;
}

#endif
