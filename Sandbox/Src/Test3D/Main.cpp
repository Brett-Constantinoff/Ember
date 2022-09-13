#include "Test3DApp.h"

#if _DEBUG
#include <src/Core/AllocationMetrics.h>
#endif

int main(int argc, char** argv)
{
#if _DEBUG
	s_allocationMetrics.currentUsage();

	Test3DApp* app = new Test3DApp("3D Test Application");
	s_allocationMetrics.currentUsage();

	app->start();
	s_allocationMetrics.currentUsage();

	delete app;
	s_allocationMetrics.currentUsage();

	std::cin.get();
	return 0;

#else
	Test3DApp* app = new Test3DApp("3D Test Application");
	app->pushLayer(new Test3DLayer("Test layer"));
	app->start();
	delete app;
	std::cin.get();
	return 0;
#endif
}