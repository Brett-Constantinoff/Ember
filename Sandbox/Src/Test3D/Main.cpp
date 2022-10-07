#include <Engine.h>
#include <cmath>

/*
vertex shader source
*/
const char* c_vsSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"		gl_Position = vec4(aPos, 1.0);\n"
"}\0";

/*
frag shader source
*/
const char* c_fsSource = "#version 330 core\n"
"out vec4 oFragColor;\n"
"uniform vec4 uColor;"
"void main() {\n"
"		oFragColor = uColor;\n"
"}\0";

/*
callback method for screen resizing
*/
void fbSizeCallBack(GLFWwindow* win, int32_t width, int32_t height);

int main()
{
	/*
	init glfw
	*/
	// check if glfw failed
	if (!glfwInit())
	{
		std::cout << "Failed to init glfw\n";
		std::cin.get();
		exit(1);
	}
	// tell glfw we want to use version 3.3 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create our window where all rendering happens
	GLFWwindow* win = glfwCreateWindow(1080, 1080, "Hello World", NULL, NULL);
	// check if window failed
	if (!win)
	{
		std::cout << "Failed to init glfw window\n";
		std::cin.get();
		exit(1);
	}
	// make this window the current rendering context
	glfwMakeContextCurrent(win);
	// set the re-size callback
	glfwSetFramebufferSizeCallback(win, fbSizeCallBack);

	// load opengl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init glad\n";
		std::cin.get();
		exit(1);
	}

	// create and check compilation of vs 
	uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &c_vsSource, NULL);
	glCompileShader(vs);
	int success;
	char infoLog[512];
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// create and check compilation of fs 
	uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &c_fsSource, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// create our shader program and cleanup intermediates
	uint32_t shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);
	glDeleteShader(vs);
	glDeleteShader(fs);

	// create and bind vao
	uint32_t vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// create some data for opengl to use
	float vertPos[] = {
	   -1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};
	// send data to gpu
	uint32_t vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertPos), vertPos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// initialize some colors
	glm::vec4 triColor = { 1.0f, 0.0f, 0.0f, 1.0f };
	glm::vec4 screenColor = { 0.35f, 0.35f, 0.65f, 1.0f };

	// render loop
	while (!glfwWindowShouldClose(win))
	{
		// set a background color and clear the color buffer
		glClearColor(screenColor.r, screenColor.g, screenColor.b, screenColor.a);
		glClear(GL_COLOR_BUFFER_BIT);

		// use our shader program for rendering
		glUseProgram(shaderProgram);

		// modify our uniform
		triColor.r = sin(static_cast<float>(glfwGetTime())) / 2.0f + 0.5f;
		triColor.b = cos(static_cast<float>(glfwGetTime())) / 2.0f + 0.5f;

		// ensure we can properly set our uniform
		int32_t result = glGetUniformLocation(shaderProgram, "uColor");
		if (result == -1)
		{
			std::cout << "Uniform not found\n";
			std::cin.get();
			exit(1);
		}
		glUniform4f(result, triColor.r, triColor.g, triColor.b, triColor.a);

		// render
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// swap front and back buffer
		glfwPollEvents();
		glfwSwapBuffers(win);
	}
}

void fbSizeCallBack(GLFWwindow* win, int32_t width, int32_t height)
{
	glViewport(0, 0, width, height);
}