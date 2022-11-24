#shader vertexShader
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 uView;
uniform mat4 uProj;
uniform mat4 uModel;
uniform mat4 uLightMat;

out vec4 oFragToLight;
out vec3 oNormal;
out vec3 oFragPos;

void main()
{
    oFragPos = vec3(uModel * vec4(aPos, 1.0));
    oNormal = transpose(inverse(mat3(uModel))) * aNormal;
    oFragToLight = uLightMat * vec4(oFragPos, 1.0);
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
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
in vec4 oFragToLight;

uniform vec3 uViewPos;
uniform DirLight uDirLight;
uniform vec3 uDiff;
uniform vec3 uSpec;
uniform vec3 uAmb;
uniform float uShine;
uniform sampler2D uShadowMap;

out vec4 oFragColor;

float calcShadow(vec4 fragToLight)
{
    vec3 proj = fragToLight.xyz / fragToLight.w;
    proj = proj * 0.5 + 0.5;
    float closest = texture(uShadowMap, proj.xy).r;
    float curr = proj.z;

    vec3 normal = normalize(oNormal);
    vec3 lightDir = normalize(uDirLight.m_dir - oFragPos);
    float bias = max(0.05 * (1.0 - dot(normal, uDirLight.m_dir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(uShadowMap, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(uShadowMap, proj.xy + vec2(x, y) * texelSize).r;
            shadow += curr - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if (proj.z > 1.0)
        shadow = 0.0;

    return shadow;
}

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

    float shadow = calcShadow(oFragToLight);
    vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular));
    oFragColor = vec4(result, 1.0);
}