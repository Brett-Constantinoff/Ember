#shader vertexShader
#version 330 core

layout(location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos, 1.0);
}

/*-------------------------------------------------------------------------------*/

#shader fragmentShader
#version 330 core

out vec4 oFragColor;

void main()
{
	oFragColor = vec4(1.0, 0.0, 1.0, 1.0);
}