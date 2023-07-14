#include "VulkanShader.h"

namespace Ember::Renderer
{
	VulkanShader::VulkanShader(const std::string& shaderPath) :
		m_shaderPath{shaderPath}
	{
        parseShader();
        compileShader();
	}

	VulkanShader::~VulkanShader()
	{

	}

	void VulkanShader::parseShader()
	{
        enum class ShaderType
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        ShaderType type = ShaderType::NONE;
        std::ifstream stream(m_shaderPath);
        if (!stream)
            Core::Logger::getInstance().logError(std::string{"Cannot find shader file: " + m_shaderPath}, __FILE__);

        std::string line;

        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertexShader") != std::string::npos)
                    type = ShaderType::VERTEX;

                else if (line.find("fragmentShader") != std::string::npos)
                    type = ShaderType::FRAGMENT;

            }
            else
                m_ss[(int32_t)type] << line << '\n';
        }
	}

    void VulkanShader::compileShader()
    {
        std::string shaderPath{ "../Engine/assets/shaders/" };
        std::string vertShaderPath{shaderPath + "vulkanShader.vert"};
        std::string fragShaderPath{shaderPath + "vulkanShader.frag"};

        std::ofstream vertShader(vertShaderPath);
        std::ofstream fragShader(fragShaderPath);

        if (!vertShader || !fragShader)
            Core::Logger::getInstance().logError(std::string{"Cant create vulkan shaders"}, __FILE__);

        vertShader << m_ss[0].rdbuf();
        fragShader << m_ss[1].rdbuf();

        vertShader.close();
        fragShader.close();

        const char* sdkPath{ std::getenv("VULKAN_SDK") };
        if (!sdkPath)
            Core::Logger::getInstance().logError(std::string{"Cant find Vulkan Sdk"}, __FILE__);

        // go back to root of shaders
        std::filesystem::path absolutePath = std::filesystem::absolute(shaderPath);

        std::string vertCommand{std::string{sdkPath} + "/Bin/glslc.exe " + absolutePath.string() + "vulkanShader.vert" + " -o " + absolutePath.string() + "vulkanShaderVert.spv"};
        std::string fragCommand{std::string{sdkPath} + "/Bin/glslc.exe " + absolutePath.string() + "vulkanShader.frag" + " -o " + absolutePath.string() + "vulkanShaderFrag.spv"};

        std::system(vertCommand.c_str());
        std::system(fragCommand.c_str());

        m_source.vertexSource = getSource(shaderPath + "/vulkanShaderVert.spv");
        m_source.fragmentSource = getSource(shaderPath + "/vulkanShaderFrag.spv");

        // delete intermediate shader files
        std::remove(std::string{ shaderPath + "/vulkanShader.vert" }.c_str());
        std::remove(std::string{ shaderPath + "/vulkanShader.frag" }.c_str());
        std::remove(std::string{ shaderPath + "/vulkanShaderVert.spv" }.c_str());
        std::remove(std::string{ shaderPath + "/vulkanShaderFrag.spv" }.c_str());
    }

    std::string VulkanShader::getSource(const std::string& file)
    {
        std::ifstream f(file, std::ios::ate | std::ios::binary);

        if (!f.is_open()) 
            Core::Logger::getInstance().logError(std::string{ "Cant open shader file" }, __FILE__);
        

        std::size_t fileSize = static_cast<std::size_t>(f.tellg());
        std::vector<char> buffer(fileSize);

        f.seekg(0);
        f.read(buffer.data(), fileSize);
        std::string source{buffer.begin(), buffer.end()};
        f.close();

        return source;
    }

    ShaderSource VulkanShader::getSource()
    {
        return m_source;
    }
  
}