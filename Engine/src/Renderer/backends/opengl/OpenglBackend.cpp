#include "OpenglBackend.h"

namespace Ember::Renderer
{
	void OpenglBackend::init(const RendererCreateInfo& createInfo)
	{
		m_createInfo = createInfo;
		glEnable(GL_DEPTH_TEST);

		if (m_createInfo.m_scene->getSkyboxEnabled())
		{
			initMeshRenderData(m_createInfo.m_scene->getSkybox()->getMeshes()[0]);
			loadSkybox();
		}

		for (const auto& entity : m_createInfo.m_scene->getEntities())
		{
			for (const auto& mesh : entity->getMeshes())
			{
				initMeshRenderData(mesh);
				initMeshTextures(mesh);
			}
		}
	}

	void OpenglBackend::destroy()
	{
		for (const auto& entity : m_createInfo.m_scene->getEntities())
		{
			for (const auto& mesh : entity->getMeshes())
			{
				auto renderData{ mesh->getRenderData() };

				for (const auto& resource : renderData.m_resources)
					glDeleteBuffers(1, &resource);
				for (const auto& resource : renderData.m_textures)
					glDeleteTextures(1, &resource);

				glDeleteVertexArrays(1, &renderData.m_vao);
			}
		}
	}

	void OpenglBackend::loadSkybox()
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
		for (int32_t i{ 0 }; i < files.size(); i++)
		{
			uint8_t* fileData{ stbi_load(files[i].data(), &width, &height, &channels, 0) };
			if (fileData)
			{
				GLenum format{ 0 };
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
				Core::Logger::getInstance().logWarn(std::string{"File failed to load: " + files[i]}, __FILE__);
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

	void OpenglBackend::update(float dt)
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

	void OpenglBackend::render()
	{
		std::vector<std::shared_ptr<Ember::Scene::Entity>> objects = m_createInfo.m_scene->getEntities();
		for (const auto& entity : objects)
		{
			// only render the physical objetcs in the scene
			if (entity->getType() == Ember::Scene::EntityType::Renderable)
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

	void OpenglBackend::renderMesh(const std::shared_ptr<Scene::Entity>& entity, const std::shared_ptr<Scene::Mesh>& mesh)
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

		model = glm::rotate(model, xRad, { 1.0f, 0.0f, 0.0f });
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

	void OpenglBackend::renderSkybox()
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

	void OpenglBackend::initMeshRenderData(const std::shared_ptr<Scene::Mesh>& mesh)
	{
		auto renderData{ mesh->getRenderData() };

		// vertex array
		glGenVertexArrays(1, &renderData.m_vao);
		glBindVertexArray(renderData.m_vao);

		// normals
		if (renderData.m_normals.size() != 0)
		{
			glGenBuffers(1, &renderData.m_nbo);
			renderData.m_resources.push_back(renderData.m_nbo);

			// normal buffer
			glBindBuffer(GL_ARRAY_BUFFER, renderData.m_nbo);
			glBufferData(GL_ARRAY_BUFFER, renderData.m_normals.size() * sizeof(float), renderData.m_normals.data(), GL_STATIC_DRAW);

			// normal attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
		}

		// text coords
		if (renderData.m_uvCoords.size() != 0)
		{
			glGenBuffers(1, &renderData.m_uvbo);
			renderData.m_resources.push_back(renderData.m_uvbo);

			// uv buffer
			glBindBuffer(GL_ARRAY_BUFFER, renderData.m_uvbo);
			glBufferData(GL_ARRAY_BUFFER, renderData.m_uvCoords.size() * sizeof(float), renderData.m_uvCoords.data(), GL_STATIC_DRAW);

			// uv attribute attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(2);
		}

		// positions
		glGenBuffers(1, &renderData.m_vbo);
		renderData.m_resources.push_back(renderData.m_vbo);

		// position buffer
		glBindBuffer(GL_ARRAY_BUFFER, renderData.m_vbo);
		glBufferData(GL_ARRAY_BUFFER, renderData.m_vertexPositions.size() * sizeof(float), renderData.m_vertexPositions.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);

		mesh->setRenderData(renderData);
	}

	void  OpenglBackend::initMeshTextures(const std::shared_ptr<Scene::Mesh>& mesh)
	{
		auto renderData{ mesh->getRenderData() };

		if (!renderData.m_material.m_diffuseTexture.empty())
		{
			glGenTextures(1, &renderData.m_diffuseTexId);
			glBindTexture(GL_TEXTURE_2D, renderData.m_diffuseTexId);
			loadMeshTexture(renderData.m_material.m_texturePath + renderData.m_material.m_diffuseTexture);
			renderData.m_textures.push_back(renderData.m_diffuseTexId);
		}

		mesh->setRenderData(renderData);
	}
	void OpenglBackend::loadMeshTexture(const std::string& texture)
	{
		int32_t width{};
		int32_t height{};
		int32_t channels{};

		stbi_set_flip_vertically_on_load_thread(true);
		uint8_t* data = stbi_load(texture.c_str(), &width, &height, &channels, 0);
		if (data)
		{
			GLenum format{};
			if (channels == 1)
				format = GL_RED;
			else if (channels == 3)
				format = GL_RGB;
			else if (channels == 4)
				format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
		}
		else
		{
			Core::Logger::getInstance().logError(std::string{"ERROR LOADING TEXTURE: " + texture}, __FILE__);
		}
	}
}