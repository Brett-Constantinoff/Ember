#shader vertexShader
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 uView;
uniform mat4 uProj;
uniform mat4 uModel;

out vec3 oColor;

void main()
{
	gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
	oColor = aColor;
}

/*-------------------------------------------------------------------------------*/

#shader fragmentShader
#version 330 core

in vec3 oColor;
out vec4 oFragColor;

void main()
{
	oFragColor = vec4(oColor, 1.0);
}