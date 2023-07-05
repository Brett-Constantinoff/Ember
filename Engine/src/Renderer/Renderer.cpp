#include "Renderer.h"

namespace Ember::Renderer
{
	Renderer::Renderer(const RendererCreateInfo& createInfo) :
		m_createInfo{ createInfo }, m_perspective{}, m_view{}
	{
		glEnable(GL_DEPTH_TEST);
		if (m_createInfo.m_scene->getSkyboxEnabled())
			loadSkybox();
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
	}

	void Renderer::render()
	{
		std::vector<std::shared_ptr<Ember::Scene::Entity>> objects = m_createInfo.m_scene->getEntities();
		for (const auto& entity : objects)
		{
			// only render the physical objetcs in the scene
			if (entity->getType() == Ember::Scene::EntityType::RENDERABLE)
			{
				for (const auto& mesh : entity->getMeshes())
				{
					renderMesh(entity, mesh);
				}
			}
		}

		// render skybox last
		if (m_createInfo.m_scene->getSkyboxEnabled())
			renderSkybox();

		// render our gui
		renderGui();
	}

	void Renderer::loadSkybox()
	{
		std::filesystem::path dir{ std::filesystem::current_path() };
		std::string skyboxPath{ "../Engine/assets/textures/skybox/" };
		std::filesystem::path rel{ std::filesystem::relative(skyboxPath, dir) };
	
		//get skybox files
		std::vector<std::string> files = {
			rel.string() + "/right.jpg",
			rel.string() + "/left.jpg",
			rel.string() + "/top.jpg",
			rel.string() + "/bottom.jpg",
			rel.string() + "/front.jpg",
			rel.string() + "/back.jpg",
		};

		uint32_t textureID{};
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		stbi_set_flip_vertically_on_load_thread(false);

		int32_t width{};
		int32_t height{};
		int32_t channels{};
		for (int32_t i{0}; i < files.size(); i++) 
		{
			uint8_t* fileData{ stbi_load(files[i].data(), &width, &height, &channels, 0)};
			if (fileData) 
			{
				GLenum format{0};
				if (channels == 1) 
					format = GL_RED;
				else if (channels == 3) 
					format = GL_RGB;
				else if (channels == 4) 
					format = GL_RGBA;
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, fileData);
			}
			else 
			{
				Core::Logger::getInstance().logError(std::string{ "Cannot load skybox file: " + files[i] }, __FILE__);
			}
			stbi_image_free(fileData);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		// add the texture id to the list of texture resources for the skybox mesh
		m_createInfo.m_scene->getSkybox()->getMeshes()[0]->getRenderData().m_textures.push_back(textureID);
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

	void Renderer::renderMesh(const std::shared_ptr<Scene::Entity>& entity, const std::shared_ptr<Scene::Mesh>& mesh)
	{
		// update transforms
		glm::mat4 model{ 1.0f };
		const auto& centroid(entity->getCentroid());

		// move the object
		model = glm::translate(model, -centroid);
		model = glm::translate(model, entity->getPosition());

		// rotate the object
		float xRad{ entity->getRotationAxis().x * glm::two_pi<float>() };
		float yRad{ entity->getRotationAxis().y * glm::two_pi<float>() };
		float zRad{ entity->getRotationAxis().z * glm::two_pi<float>() };

		model = glm::rotate(model, xRad, { 1.0f, 0.0f, 0.0f});
		model = glm::rotate(model, yRad, { 0.0f, 1.0f, 0.0f });
		model = glm::rotate(model, zRad, { 0.0f, 0.0f, 1.0f });

		//scale the object
		model = glm::scale(model, entity->getScale());
		model = glm::translate(model, -centroid);

		// update the uniforms
		const auto& sceneShader{ m_createInfo.m_scene->getShader() };
		sceneShader->use();
		sceneShader->setMat4("model", model);
		sceneShader->setMat4("projection", m_perspective);
		sceneShader->setMat4("view", m_view);
		sceneShader->setVec3("uViewPos", m_createInfo.m_scene->getCamera()->getPos());
		sceneShader->setVec3("uDiffuse", mesh->getRenderData().m_material.m_diffuse);

		// check for diffuse texture
		if (!mesh->getRenderData().m_material.m_diffuseTexture.empty())
		{
			sceneShader->setInt("uDiffTextureExists", 1);
			sceneShader->setInt("uDiffTexture", 0);
		}
		else
		{
			sceneShader->setInt("uDiffTextureExists", 0);
		}

		const auto& data{ mesh->getRenderData() };

		// check for wire frame
		if (entity->getWireFrame())
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// render the object
		glBindVertexArray(data.m_vao);

		// diffuse texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, data.m_diffuseTexId);

		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(data.m_vertexPositions.size() / 3));
		glBindVertexArray(0);
		sceneShader->disuse();
	}

	void Renderer::renderSkybox()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDepthFunc(GL_LEQUAL);

		const auto& skybox{ m_createInfo.m_scene->getSkybox() };
		const auto& camera{ m_createInfo.m_scene->getCamera() };
		const auto& skyboxRenderData{ skybox->getMeshes()[0]->getRenderData() };
		const auto& skyboxShader{ m_createInfo.m_scene->getSkyboxShader() };

		skyboxShader->use();
		skyboxShader->setMat4("uProjection", m_perspective);

		// remove translation portion from view matrix, this makes it so the 
		// skybox appears infinitly far away
		skyboxShader->setMat4("uView", glm::mat4(glm::mat3(camera->getView())));
		skyboxShader->setInt("uSkybox", 0);

		glBindVertexArray(skyboxRenderData.m_vao);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxRenderData.m_textures[0]);
		glActiveTexture(GL_TEXTURE0);
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(skyboxRenderData.m_vertexPositions.size() / 3));
		glBindVertexArray(0);

		skyboxShader->disuse();
		glDepthFunc(GL_LESS);
	}
}