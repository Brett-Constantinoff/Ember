#pragma once
#include <stdint.h>

namespace Ember
{
	namespace Core
	{
		struct MemoryMetrics
		{
			uint32_t m_allocations = 0;
			uint32_t m_frees = 0;
			size_t m_memUsage = 0;
		};
		static MemoryMetrics s_metrics;
	}
}
