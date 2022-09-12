#pragma once
#include <iostream>
#include <stdint.h>
#include <memory>

struct AllocationMetrics
{
	int32_t m_totalAllocatedBytes = 0;
	int32_t m_totalFreedBytes = 0;
	int32_t m_totalAllocations = 0;
	int32_t m_totalFrees = 0;

	void currentUsage()
	{
		std::cout << "Total memory usage: " << m_totalAllocatedBytes - m_totalFreedBytes << " bytes\n";
		std::cout << "Total Allocations: " << m_totalAllocations << "\n";
		std::cout << "Total Frees: " << m_totalFrees << "\n\n";
	}
};
static AllocationMetrics s_allocationMetrics;

void* operator new(size_t size)
{
	s_allocationMetrics.m_totalAllocations += 1;
	s_allocationMetrics.m_totalAllocatedBytes += size;
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	s_allocationMetrics.m_totalFrees += 1;
	s_allocationMetrics.m_totalFreedBytes += size;
	free(memory);
}
