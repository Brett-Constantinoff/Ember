#shader vertexShader
#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 uProjection;
uniform mat4 uView;
out vec3 oUv;

void main()
{
	oUv = aPos;
	vec4 pos = uProjection * uView * vec4(aPos, 1.0);
	gl_Position = pos.xyww;
}

#shader fragmentShader
#version 330 core
in vec3 oUv;
uniform samplerCube uSkybox;
out vec4 oFragColor;

void main()
{
	oFragColor = texture(uSkybox, oUv);
}
