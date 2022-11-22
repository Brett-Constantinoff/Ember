#shader vertexShader
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 oFragPos;
out vec3 oNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    oNormal = mat3(transpose(inverse(uModel))) * aNormal;
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
    oFragPos = aPos;
}

/*-------------------------------------------------------------------------------*/
#shader fragmentShader
#version 330 core

struct DirLight {
    vec3 m_dir;
    vec3 m_amb;
    vec3 m_diff;
    vec3 m_spec;
};

in vec3 oFragPos;
in vec3 oNormal;

uniform vec3 uViewPos;
uniform DirLight uDirLight;
uniform vec3 uDiff;
uniform vec3 uSpec;
uniform vec3 uAmb;
uniform float uShine;

out vec4 oFragColor;

void main()
{
    // ambient
    vec3 ambient = uDirLight.m_amb * uAmb;

    // diffuse 
    vec3 norm = normalize(oNormal);
    vec3 lightDir = normalize(-uDirLight.m_dir);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = uDirLight.m_diff * diff * uDiff;

    // specular
    vec3 viewDir = normalize(uViewPos - oFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShine);
    vec3 specular = uDirLight.m_spec * spec * uSpec;

    vec3 result = ambient + diffuse + specular;
    oFragColor = vec4(result, 1.0);
}