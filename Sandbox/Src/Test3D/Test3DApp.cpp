#include "Test3DApp.h"

Test3DApp::Test3DApp(const char* label) : Application(label)
{
	pushLayer(new Test3DLayer("Test layer"));
}