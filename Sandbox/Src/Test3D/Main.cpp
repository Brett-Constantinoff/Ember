#include "Test3DApp.h"

int main(int argc, char** argv)
{
	Test3DApp app("3D Test Application");
	Test3DLayer layer("Test 3D Layer");
	app.pushLayer(&layer);
	app.start();
	return 0;
}