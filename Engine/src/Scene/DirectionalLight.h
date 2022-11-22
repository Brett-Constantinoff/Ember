#pragma once
#include "../../libs/math/glm/glm.hpp"

namespace Ember
{
	namespace Scene
	{
		struct DirectionalLight
		{
		public:
			DirectionalLight(glm::vec3 direction, glm::vec3 diff, glm::vec3 amb, glm::vec3 spec) :
				m_dir{ direction }, m_diff{ diff }, m_amb{ amb }, m_spec{ spec }
			{
			}
			~DirectionalLight()
			{
			}

		public:
			glm::vec3 m_dir;
			glm::vec3 m_diff;
			glm::vec3 m_amb;
			glm::vec3 m_spec;
		};
	}
}