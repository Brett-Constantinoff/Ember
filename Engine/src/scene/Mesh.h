#pragma once
#include "../core/TinyObj.h"
#include "../core/Glm.h"
#include "../core/OpenGL.h"
#include <string>
#include <stdexcept>

namespace Ember::Scene
{
	struct Material
	{
		glm::vec3 m_ambient{};
		glm::vec3 m_diffuse{};
		glm::vec3 m_specular{};

		float m_shine{};

		std::string m_diffuseTexture{};
		std::string m_specularTexture{};
		std::string m_normalTexture{};
		std::string m_emissiveTexture{};
	};

	struct RenderData
	{
		std::vector<float> m_vertexPositions{};
		std::vector<uint32_t> m_indices{};
		std::vector<float> m_normals{};
		std::vector<float> m_uvCoords{};

		Material m_material{};

		// this contatins things created by opengl
		std::vector<uint32_t> m_resources;
		std::vector<uint32_t> m_textures;

		uint32_t m_vbo{};
		uint32_t m_ibo{};
		uint32_t m_nbo{};
		uint32_t m_vao{};
	};

	class Mesh
	{
	public:
		Mesh(const RenderData& renderData);
		~Mesh();

		RenderData& getRenderData();

	private:
		void initRenderData();

	private:
		RenderData m_renderData;
	};
}