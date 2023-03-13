#pragma once
#include "../core/TinyObj.h"
#include "../core/Glm.h"
#include "../core/OpenGL.h"
#include <string>
#include <stdexcept>

namespace Ember::Scene
{
	struct RenderData
	{
		std::vector<float> m_vertexPositions{};
		std::vector<uint32_t> m_indices{};
		std::vector<float> m_normals{};
		std::vector<float> m_uvCoords{};

		glm::vec3 m_ambient{};
		glm::vec3 m_diffuse{};
		glm::vec3 m_specular{};
		float m_shine{};

		// this contatins things created by opengl
		std::vector<uint32_t> resources;

		uint32_t m_vbo{};
		uint32_t m_ibo{};
		uint32_t m_nbo{};
		uint32_t m_vao{};
	};

	struct TransformData
	{
		glm::mat4 m_rotate{1.0f};
		glm::vec3 m_centroid{};
		glm::vec3 m_translation{0.0f};
		glm::vec3 m_scale{1.0f};
		float m_angle{};
	};

	class Mesh
	{
	public:
		Mesh(const std::string& objFile);
		~Mesh();

		RenderData& getRenderData();
		TransformData& getTransformData();

	private:
		void loadFromObj();
		void initRenderData();
		void normalizeVertexData();

	private:
		std::string m_objFile;
		RenderData m_renderData;
		TransformData m_transformData;
	};
}