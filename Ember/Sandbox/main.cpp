#include "../Src/Core/Application.h"
#include "TestLayer.h"

class Sandbox :  public Application
{
public:
	Sandbox(const std::string label) : Application(label)
	{
	}
};

int main()
{
	Sandbox engine("Hello World!");
	engine.pushLayer(new TestLayer());
	engine.start();
	return 0;
}