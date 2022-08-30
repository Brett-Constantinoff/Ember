#include "../Src/Core/Application.h"
#include "TestLayer.h"

class Ember : public Application
{
public:
	Ember(const std::string label) : Application(label)
	{
	}
};


#ifdef _DEBUG
#include "../Src/Core/AllocationMetrics.h"

int main()
{
	s_allocationMetrics.currentUsage();

	Ember* engine = new Ember("Ember");
	s_allocationMetrics.currentUsage();

	engine->pushLayer(new TestLayer());
	s_allocationMetrics.currentUsage();

	engine->start();
	s_allocationMetrics.currentUsage();

	delete engine;
	s_allocationMetrics.currentUsage();

	std::cin.get();
}

#else
int main()
{
	Ember* engine = new Ember("Ember")
	engine->pushLayer(new TestLayer());
	engine->start();
	delete engine;
}

#endif







