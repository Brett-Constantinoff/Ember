#shader vertexShader
#version 330 core

//make sure the layout matches order in Mesh.cpp
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;
layout(location = 2) in vec2 aUv;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

out vec2 oUv;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
	oUv = aUv;
}

/*-------------------------------------------------------------------------------*/

#shader fragmentShader
#version 330 core

in vec2 oUv;

uniform vec3 uColor;
uniform sampler2D uTexture;
uniform bool uEnableTexture;

out vec4 oFragColor;

void main()
{
	vec4 color = vec4(uColor, 1.0);
	if (uEnableTexture)
	{
		color *= texture(uTexture, oUv);
	}
	oFragColor = color;
}
