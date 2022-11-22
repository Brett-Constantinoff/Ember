#pragma once
#include <vector>
#include "../Renderer/Camera.h"
#include "../Renderer/Framebuffer.h"
#include "../Renderer/Texture2D.h"
#include "../Core/Window.h"
#include "SkyBox.h"
#include "SceneObject.h"
#include "DirectionalLight.h"

namespace Ember
{
	namespace Scene
	{
		class Scene3D
		{
		public:
			Scene3D();
			~Scene3D();

			void addRenderable(SceneObject* obj);
			void addCamera(Renderer::Camera* camera);
			void addContext(Core::Window* win);
			void addSkyBox(SkyBox* skybox);
			void addDirLight(DirectionalLight* light);
			std::vector<SceneObject*> getRenderables();
			void update(float dt);
			void render();

		private:
			void renderScene();
			void renderObj(SceneObject* obj);
			void renderSkybox();

		private:
			std::vector<SceneObject*> m_renderables;
			Renderer::Camera* m_camera;
			Core::Window* m_win;
			SkyBox* m_skybox;
			DirectionalLight* m_dirLight;
			Renderer::Framebuffer m_shadowFbo;
			Renderer::Texture2D* m_shadowMap;
			glm::mat4 m_proj;
			glm::mat4 m_view;
		};
	}
}
