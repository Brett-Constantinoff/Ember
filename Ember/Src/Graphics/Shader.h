#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Math/glm.hpp"

struct shaderSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{
public:
    Shader(const std::string& filepath);
    uint32_t getId(void);
    void setVec3(const char* name, glm::vec3 uniform);
    void setVec4(const char* name, glm::vec4 uniform);
    void setMat4(const char* name, glm::mat4 uniform);
    void setInt(const char* name, int32_t uniform);
    void setFloat(const char* name, float unifrom);
    void setBool(const char* name, bool uniform);
    void use(void);
    void disuse(void);

private:
    int32_t m_ID;
    std::unordered_map<const char*, int32_t> m_uniformCache;
private:
    shaderSource parseShader(const std::string& filePath);
    uint32_t compileShader(const std::string& source, uint32_t type);
    int32_t getUniform(const char* name);



};
