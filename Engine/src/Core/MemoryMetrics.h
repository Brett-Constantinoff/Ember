#pragma once
#include <stdlib.h>
#include <iostream>

struct AllocationMetrics
{
	uint32_t m_allocations = 0;
	uint32_t m_frees = 0;

	void report()
	{
		std::cout << "Leaks present: " << m_allocations - m_frees << std::endl;
	}
};
static AllocationMetrics s_metrics;

void* operator new(size_t size)
{
	s_metrics.m_allocations++;
	return malloc(size);
}

void operator delete(void* memory)
{
	s_metrics.m_frees++;
	free(memory);
}
