#include "Test3DApp.h"

#if DEBUG
struct AllocationMetrics
{
	size_t m_totalAllocated = 0;
	size_t m_totalFreed = 0;

	size_t currentUsage()
	{
		return m_totalAllocated - m_totalFreed;
	}
};
static AllocationMetrics s_metrics;

void* operator new(size_t size)
{
	s_metrics.m_totalAllocated += size;
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	s_metrics.m_totalFreed += size;
	free(memory);
}

int main(int argc, char** argv)
{
	Test3DApp* app = new Test3DApp("3D Test Application");
	app->pushLayer(new Test3DLayer("Test 3D Layer"));
	app->start();
	delete app;
	std::cout << "Total memory leaked: " << s_metrics.currentUsage() << std::endl;
	return 0;
}

#else
int main(int argc, char** argv)
{
	Test3DApp* app = new Test3DApp("3D Test Application");
	app->pushLayer(new Test3DLayer("Test 3D Layer"));
	app->start();
	delete app;
	return 0;
}
#endif