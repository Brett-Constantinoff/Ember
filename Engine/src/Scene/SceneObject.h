#pragma once
#include <string>
#include "../../libs/math/glm/glm.hpp"
#include "../../libs/math/glm/gtc/matrix_transform.hpp"
#include "../../libs/math/glm/gtc/type_ptr.hpp"
#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/Shader.h"
#include "../Renderer/Material.h"
#include "../Renderer/Transformation.h"

namespace Ember
{
	namespace Scene
	{
		class SceneObject
		{
		public:
			SceneObject(const char* name, const Renderer::Material& material, const Renderer::Transformation& transformation);
			SceneObject(const char* name, const Renderer::Material& material);
			~SceneObject();

			Renderer::Material* getMaterial();
			Renderer::Transformation* getTransform();
			Renderer::VertexBuffer* getVbo();
			Renderer::VertexArray* getVao();

			void rotate(float angle, glm::vec3& axis);

		protected:
			const char* m_name;
			Renderer::VertexBuffer m_vbo;
			Renderer::VertexArray m_vao;
			Renderer::Material m_mat;
			Renderer::Transformation m_trans;
		};
	}
}