#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

namespace Ember::Scene
{
	struct Material
	{
		glm::vec3 m_ambient{};
		glm::vec3 m_diffuse{};
		glm::vec3 m_specular{};

		float m_shine{};

		std::string m_texturePath{};
		std::string m_diffuseTexture{};
		std::string m_ambientTexture{};
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

		std::vector<uint32_t> m_resources;
		std::vector<uint32_t> m_textures;

		uint32_t m_vbo{};
		uint32_t m_ibo{};
		uint32_t m_nbo{};
		uint32_t m_uvbo{};
		uint32_t m_vao{};

		uint32_t m_diffuseTexId{};
	};

	struct Mesh
	{
	public:
		Mesh(const RenderData& renderData);
		~Mesh();

		RenderData& getRenderData();
		void setRenderData(const RenderData& renderData);

	private:
		RenderData m_renderData;
	};
}