#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "../core/OpenGL.h"
#include "../core/Glm.h"
#include "../Core/Logger.h"

namespace Ember::Renderer
{
    struct ShaderSource
    {
        std::string vertexSource;
        std::string fragmentSource;
    };

    class Shader
    {
    public:
        Shader(const std::string& filepath);
        ~Shader();
        int32_t getId(void) const;
        void setVec3(const std::string& name, const glm::vec3& uniform);
        void setVec4(const std::string& name, const glm::vec4& uniform);
        void setMat4(const std::string& name, const glm::mat4& uniform);
        void setInt(const std::string& name, int32_t uniform);
        void setFloat(const std::string& name, float unifrom);
        void use(void);
        void disuse(void);

    private:
        void parseShader();
        int32_t compileShader(const std::string& source, int32_t type);
        int32_t getUniform(const std::string& name);

    private:
        int32_t m_ID;
        std::string m_shaderFile;
        std::unordered_map<const char*, int32_t> m_uniformCache;
        std::unordered_map<const char*, int32_t> m_uniformNotFoundCache;
        ShaderSource m_shaderSource;
    };
}