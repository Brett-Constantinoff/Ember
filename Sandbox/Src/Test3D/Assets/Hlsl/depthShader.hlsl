#shader vertexShader
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 uLightMat;
uniform mat4 uModel;

void main()
{
	gl_Position = uLightMat * uModel * vec4(aPos, 1.0);
}

/*-------------------------------------------------------------------------------*/

#shader fragmentShader
#version 330 core

void main()
{
	//gl_FragDepth = gl_FragCoord.z;
}