#include "Application3D.h"

int main(int argc, char** argv)
{
	try
	{
		Ember::Core::ApplicationCreateInfo createInfo;
		createInfo.m_label = "Application 3D";
		Application3D app{ createInfo };

		app.run();	
	}
	catch (std::runtime_error e)
	{
		return -1;
	}

#if defined(_WIN32)
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}