#include "Scene3D.h"

namespace Ember
{
	namespace Scene
	{
		Scene3D::Scene3D() :
			m_camera{ nullptr },		   m_skybox{ nullptr },				m_dirLight{ nullptr },
			m_win{ nullptr },			   m_proj{ glm::mat4(1.0f) },		m_view{ glm::mat4(1.0f) },
			m_lightMat{ glm::mat4(1.0f) }, m_shadowFbo {GL_FRAMEBUFFER},	m_shadowMap{ nullptr }, 
			m_depthShader{ nullptr }
		{
			glEnable(GL_DEPTH_TEST);
			m_shadowMap = new Renderer::Texture2D(GL_TEXTURE_2D, 7200, 7200);
			m_shadowFbo.attachDepthTex(m_shadowMap);

		}

		Scene3D::~Scene3D()
		{
			std::cout << "Destroying Scene\n";
			for (auto renderable : m_renderables)
			{
				delete renderable;
			}
			m_renderables.clear();
			delete m_camera;
			delete m_skybox;
			delete m_dirLight;
			delete m_shadowMap;
			delete m_depthShader;
		}

		void Scene3D::addRenderable(SceneObject* obj)
		{
			m_renderables.push_back(obj);
		}

		void Scene3D::addCamera(Renderer::Camera* camera)
		{
			m_camera = camera;
		}

		void Scene3D::addContext(Core::Window* window)
		{
			m_win = window;
		}

		void Scene3D::addSkyBox(SkyBox* skybox)
		{
			m_skybox = skybox;
		}

		void Scene3D::addDirLight(DirectionalLight* light)
		{
			m_dirLight = light;
		}

		void Scene3D::addDepthShader(Renderer::Shader* depth)
		{
			m_depthShader = depth;
		}

		std::vector<SceneObject*> Scene3D::getRenderables()
		{
			return m_renderables;
		}

		void Scene3D::update(float dt)
		{
			m_camera->move(m_win->getContext(), dt);
			m_proj = m_win->getPerspective();
			m_view = *m_camera->getView();
		}

		void Scene3D::render()
		{
			glClearColor(0.25f, 0.35f, 0.65f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			renderShadows();
			renderScene();
		}

		void Scene3D::renderShadows()
		{
			// render directional shadows
			glm::mat4 lightProj = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f, 500.0f);
			glm::mat4 lightView = glm::lookAt(m_dirLight->m_dir, glm::vec3{ 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
			m_lightMat = lightProj * lightView;

			m_depthShader->use();
			m_depthShader->setMat4("uLightMat", m_lightMat);

			m_win->setViewPort(m_shadowMap->getWidth(), m_shadowMap->getHeight());
			m_shadowFbo.bind();
			glClear(GL_DEPTH_BUFFER_BIT);
			
			for (auto obj : m_renderables)
			{
				Renderer::Transformation trans = *obj->getTransform();
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, trans.m_translation);
				model *= trans.m_rotation;
				model = glm::scale(model, trans.m_scale);
				m_depthShader->setMat4("uModel", model);

				obj->getVao()->bind();
				glDrawArrays(GL_TRIANGLES, 0, 36);
				obj->getVao()->unBind();
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void Scene3D::renderScene()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_win->setViewPort();
			for (auto obj : m_renderables)
			{
				Renderer::Transformation trans = *obj->getTransform();
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, trans.m_translation);
				model *= trans.m_rotation;
				model = glm::scale(model, trans.m_scale);

				Renderer::Material mat = *obj->getMaterial();
				mat.m_shader.use();
				
				mat.m_shader.setVec3("uDiff", mat.m_diff);
				mat.m_shader.setMat4("uProj", m_proj);
				mat.m_shader.setMat4("uView", m_view);
				mat.m_shader.setMat4("uModel", model);
				mat.m_shader.setMat4("uLightMat", m_lightMat);
				
				if (mat.m_lit)
				{
					mat.m_shader.setVec3("uAmb", mat.m_amb);
					mat.m_shader.setVec3("uSpec", mat.m_spec);
					mat.m_shader.setFloat("uShine", mat.m_shine);

					mat.m_shader.setVec3("uDirLight.m_dir", m_dirLight->m_dir);
					mat.m_shader.setVec3("uDirLight.m_diff", m_dirLight->m_diff);
					mat.m_shader.setVec3("uDirLight.m_amb", m_dirLight->m_amb);
					mat.m_shader.setVec3("uDirLight.m_spec", m_dirLight->m_spec);

					mat.m_shader.setVec3("uViewPos", *m_camera->getPos());
				}
				else
				{
					mat.m_shader.setVec3("uLightPos", m_dirLight->m_dir);
				}
				glActiveTexture(GL_TEXTURE0);
				m_shadowMap->bind();

				obj->getVao()->bind();
				glDrawArrays(GL_TRIANGLES, 0, 36);
				obj->getVao()->unBind();

				m_shadowMap->unbind();
			}
			renderSkybox();
		}

		void Scene3D::renderSkybox()
		{
			glDepthFunc(GL_LEQUAL);
			Renderer::Material skyBoxMat = *m_skybox->getMaterial();
			glm::mat4 view = glm::mat4(glm::mat3(*m_camera->getView()));

			skyBoxMat.m_shader.use();
			skyBoxMat.m_shader.setMat4("uView", view);
			skyBoxMat.m_shader.setMat4("uProj", m_proj);

			m_skybox->getVao()->bind();
			glActiveTexture(GL_TEXTURE0);
			m_skybox->getCubeMap()->bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glDepthFunc(GL_LESS);
		}
	}
}
