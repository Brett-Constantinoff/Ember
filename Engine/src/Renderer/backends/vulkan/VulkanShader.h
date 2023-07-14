#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <filesystem>

#include "../../../core/Logger.h"

namespace Ember::Renderer
{
	class VulkanShader
	{
	public:
		VulkanShader(const std::string& shaderPath);
		~VulkanShader();

	private:
		void parseShader();
		void compileShader();

	private:
		std::string m_shaderPath{};
		std::stringstream m_ss[2];
	};
}

