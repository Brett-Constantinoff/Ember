#shader vertexShader
#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 uView;
uniform mat4 uProj;
uniform mat4 uModel;

void main()
{
	gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
}

/*-------------------------------------------------------------------------------*/

#shader fragmentShader
#version 330 core

uniform vec3 uDiff;
out vec4 oFragColor;

void main()
{
	oFragColor = vec4(uDiff, 1.0);
}