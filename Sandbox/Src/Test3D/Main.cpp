#include "Test3DApp.h"

#if DEBUG && defined(_WIN32)
void* operator new(size_t size)
{
	Ember::Core::s_metrics.m_allocations++;
	Ember::Core::s_metrics.m_memUsage += size;
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	Ember::Core::s_metrics.m_frees++;
	free(memory);
}
int main(int argc, char** argv)
{
	Test3DApp* app = new Test3DApp("3D Test Application");
	app->pushLayer(new Test3DLayer("Test 3D Layer"));
	app->start();
	delete app;
	std::cout << "Memory leaks present: " << Ember::Core::s_metrics.m_allocations - Ember::Core::s_metrics.m_frees << std::endl;
	std::cout << "Total memory used: " << Ember::Core::s_metrics.m_memUsage / 1000000 << " Mbytes" << std::endl;
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