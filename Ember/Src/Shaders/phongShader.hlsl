#shader vertexShader
#version 330 core

//make sure the layout matches order in Mesh.cpp
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in vec2 aUv;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

out vsOut
{
	vec3 fragPos;
	vec3 norm;
	vec2 uv;
}oVs;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
	oVs.fragPos = aPos;
	oVs.norm = aNorm;
	oVs.uv = aUv;
}

/*-------------------------------------------------------------------------------*/

#shader fragmentShader
#version 330 core

in vsOut
{
	vec3 fragPos;
	vec3 norm;
	vec2 uv;
}aFs;

uniform vec3 uColor;
uniform sampler2D uTexture;

out vec4 oFragColor;

void main()
{
	vec4 color = vec4(uColor, 1.0);
	color *= texture(uTexture, aFs.uv);
	oFragColor = color;
}
