#include "Test3DApp.h"

#if DEBUG && defined(_WIN32)
struct AllocationMetrics
{
	uint32_t m_allocations = 0;
	uint32_t m_frees = 0;

	void report()
	{
		std::cout << "Allocations: " << m_allocations << std::endl;
		std::cout << "Frees: " << m_frees << std::endl;
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

int main(int argc, char** argv)
{
	Test3DApp* app = new Test3DApp("3D Test Application");
	app->pushLayer(new Test3DLayer("Test 3D Layer"));
	app->start();
	delete app;
	s_metrics.report();
	return 0;
}

#elif DEBUG && __APPLE__
int main(int argc, char** argv)
{
	Test3DApp* app = new Test3DApp("3D Test Application");
	app->pushLayer(new Test3DLayer("Test 3D Layer"));
	app->start();
	delete app;
	return 0;
}
#endif