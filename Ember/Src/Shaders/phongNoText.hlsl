#shader vertexShader
#version 330 core

//make sure the layout matches order in Mesh.cpp
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

out vsOut
{
	vec3 fragPos;
	vec3 norm;
}oVs;

void main()
{
	oVs.fragPos = vec3(uModel * vec4(aPos, 1.0));
	oVs.norm = (transpose(inverse(uModel)) * vec4(aNorm, 1.0)).xyz;
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}

/*-------------------------------------------------------------------------------*/

#shader fragmentShader
#version 330 core

struct Material
{
	vec3 m_amb;
	vec3 m_diff;
	vec3 m_spec;
	float m_shine;
};

struct DirLight
{
	vec3 m_dir;
	vec3 m_amb;
	vec3 m_diff;
	vec3 m_spec;
};

in vsOut
{
	vec3 fragPos;
	vec3 norm;
}aFs;

uniform vec3 uViewPos;
uniform DirLight uDirLight;
uniform Material uMaterial;

out vec4 oFragColor;

vec3 calcDirLight(DirLight light, Material material, vec3 normal, vec3 viewPos)
{
	vec3 lightDir = normalize(-light.m_dir);
	float diff = max(dot(lightDir, normal), 0.0);

	vec3 halfWay = normalize(lightDir + viewPos);
	float spec = pow(max(dot(normal, halfWay), 0.0), material.m_shine);

	vec3 ambient = light.m_amb * material.m_amb;
	vec3 diffuse = light.m_diff * diff * material.m_diff;
	vec3 specular = light.m_spec * spec * material.m_spec;
	return (ambient + diffuse + specular);
}

void main()
{
	vec3 normal = normalize(aFs.norm);
	vec3 viewPos = normalize(uViewPos - aFs.fragPos);
	vec3 result = calcDirLight(uDirLight, uMaterial, normal, viewPos);

	oFragColor = vec4(result, 1.0);
}

