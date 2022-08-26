#include "Callbacks.h"

void resize(GLFWwindow* win, int32_t width, int32_t height)
{
	glViewport(0, 0, width, height);
}
