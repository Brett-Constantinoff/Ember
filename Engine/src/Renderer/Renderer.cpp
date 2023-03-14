#include "Renderer.h"

namespace Ember::Renderer
{
	Renderer::Renderer(const RendererCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_perspective{}, m_view{}, m_wireFrameEnabled{false}
	{
		glEnable(GL_DEPTH_TEST);
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::update(float dt)
	{
		glClearColor(m_createInfo.m_backgroundCol[0], m_createInfo.m_backgroundCol[1], m_createInfo.m_backgroundCol[2], m_createInfo.m_backgroundCol[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		updateGui();
		

		// update the projection matrix
		float aspect = static_cast<float>(m_createInfo.m_window->getWidth()) / static_cast<float>(m_createInfo.m_window->getHeight());
		float near = m_createInfo.m_scene->getCamera()->getNear();
		float far = m_createInfo.m_scene->getCamera()->getFar();
		float zoom = m_createInfo.m_scene->getCamera()->getZoom();
		m_perspective = glm::perspective(glm::radians(zoom), aspect, near, far);

		// update view
		m_view = m_createInfo.m_scene->getCamera()->getView();

		m_createInfo.m_scene->getCamera()->move(dt);

		// check for wireframe
		// only want to make these calls once hence the inner if's
		if (m_createInfo.m_scene->getWireFrame())
		{
			if (!m_wireFrameEnabled)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				m_wireFrameEnabled = true;
			}
		}
		else
		{
			if (m_wireFrameEnabled)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				m_wireFrameEnabled = false;
			}
		}

	}

	void Renderer::render()
	{
		auto& objects = m_createInfo.m_scene->getEntities();
		for (const auto& entity : objects)
		{
			// only render the physical objetcs in the scene
			if (entity->getType() == Ember::Scene::EntityType::RENDERABLE)
			{
				for (const auto& mesh : entity->getMeshes())
				{
					// update transforms
					Ember::Scene::TransformData transforms{ mesh->getTransformData() };
					glm::mat4 model{ 1.0f };

					model = glm::translate(model, transforms.m_translation) *
						glm::translate(model, entity->getCentroid()) * 
						transforms.m_rotate *
						glm::translate(model, -entity->getCentroid()) *
						glm::scale(model, transforms.m_scale);

					// update the uniforms
					Shader* sceneShader{ m_createInfo.m_scene->getShader() };
					sceneShader->use();
					sceneShader->setMat4("model", model);
					sceneShader->setMat4("projection", m_perspective);
					sceneShader->setMat4("view", m_view);
					sceneShader->setVec3("uViewPos", m_createInfo.m_scene->getCamera()->getPos());
					sceneShader->setVec3("uDiffuse", mesh->getRenderData().m_material.m_diffuse);
					Ember::Scene::RenderData data{ mesh->getRenderData() };

					// render the object
					glBindVertexArray(data.m_vao);
					glDrawArrays(GL_TRIANGLES, 0, data.m_vertexPositions.size() / 3);
				}
			}
		}

		// render our gui
		renderGui();
	}

	void Renderer::updateGui()
	{
		if (m_createInfo.m_guiEnabled)
			m_createInfo.m_gui->update();
	}

	void Renderer::renderGui()
	{
		if (m_createInfo.m_guiEnabled)
			m_createInfo.m_gui->render();
	}
}