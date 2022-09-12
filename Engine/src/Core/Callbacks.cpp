#include "Callbacks.h"

void resize(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);
}
