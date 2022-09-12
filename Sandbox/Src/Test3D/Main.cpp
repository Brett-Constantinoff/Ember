#include "Test3DApp.h"

int main(int argc, char** argv)
{
	Test3DApp* app = new Test3DApp("3D Test Application");
	app->pushLayer(new Test3DLayer("Test layer"));
	app->start();
	delete app;
	return 0;
}