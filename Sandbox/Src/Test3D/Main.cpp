#include "Test3DApp.h"

#if DEBUG && defined(_WIN32)
#include "../../../Engine/src/Core/MemoryMetrics.h"
int main(int argc, char** argv)
{
	Test3DApp* app = new Test3DApp("3D Test Application");
	app->pushLayer(new Test3DLayer("Test 3D Layer"));
	app->start();
	delete app;
	s_metrics.report();
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