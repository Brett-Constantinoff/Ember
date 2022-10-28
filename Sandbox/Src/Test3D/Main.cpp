#include "Test3DApp.h"

int main(int argc, char** argv)
{
	Test3DApp app("3D Test Application");
	app.pushLayer(new Test3DLayer("Test 3D layer"));
	app.start();
	return 0;
}