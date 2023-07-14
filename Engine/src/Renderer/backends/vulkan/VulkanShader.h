#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <filesystem>
#include <vulkan/vulkan.h>

#include "../../../core/Logger.h"
#include "../../Shader.h"

namespace Ember::Renderer
{
	class VulkanShader
	{
	public:
		VulkanShader(const std::string& shaderPath);
		~VulkanShader();

		ShaderSource getSource();

	private:
		void parseShader();
		void compileShader();
		std::string getSource(const std::string& file);

	private:
		std::string m_shaderPath{};
		std::stringstream m_ss[2];
		ShaderSource m_source{};
	};
}

