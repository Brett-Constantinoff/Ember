#include "SceneObject.h"

namespace Ember
{
	namespace Scene
	{
		SceneObject::SceneObject(const char* name, const Renderer::Material& material, const Renderer::Transformation& transformation) :
			m_name{ name }, m_mat{ material }, m_trans{ transformation }, m_vbo{ GL_ARRAY_BUFFER }, m_vao{}
		{
		}

		SceneObject::SceneObject(const char* name, const Renderer::Material& material) :
			m_name{ name }, m_mat{ material }, m_vbo{ GL_ARRAY_BUFFER }, m_vao{}
		{
		}

		SceneObject::~SceneObject()
		{
		}

		Renderer::Material* SceneObject::getMaterial()
		{
			return &m_mat;
		}

		Renderer::Transformation* SceneObject::getTransform()
		{
			return &m_trans;
		}

		Renderer::VertexArray* SceneObject::getVao()
		{
			return &m_vao;
		}

		Renderer::VertexBuffer* SceneObject::getVbo()
		{
			return &m_vbo;
		}

		void SceneObject::rotate(float angle, glm::vec3& axis)
		{
			m_trans.m_rotation = glm::rotate(m_trans.m_rotation, glm::radians(angle), axis);
		}
	}
}
