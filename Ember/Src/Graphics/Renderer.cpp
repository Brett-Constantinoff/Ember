#include "Renderer.h"

Renderer::Renderer(RenderSettings settings) : 
	m_settings{settings}
{
	glEnable(GL_DEPTH_TEST);

	if (m_settings.m_blend)
	{
		glEnable(GL_BLEND);
		glBlendFunc(m_settings.m_sFactorBlend, m_settings.m_dFactorBlend);
	}
}

Renderer::~Renderer()
{
}

void Renderer::clear()
{
	GLbitfield field = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	if (m_settings.m_clearStencil)
	{
		field |= GL_STENCIL_BUFFER_BIT;
	}
	glClearColor(m_settings.m_backgroundCol.r, m_settings.m_backgroundCol.g, m_settings.m_backgroundCol.b, 1.0f);
	glClearDepth(m_settings.m_depthValue);
	glClearStencil(m_settings.m_stencilValue);
	glClear(field);
}

void Renderer::render(Scene* scene)
{
	clear();

    std::vector<Mesh*> meshes = *scene->getMeshes();
    LightCaster<DirectionalLight>* dirLightCaster = scene->getDirLightCaster();

    //render meshes in scene
    for (Mesh* m : meshes)
    {
        TransformationInfo* meshTransform = m->getTransforms();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, meshTransform->m_pos);
        model *= meshTransform->m_rotation;
        model = glm::scale(model, meshTransform->m_scale);
        meshTransform->m_model = model;

        //update mesh uniforms
        Material* meshMat = m->getMaterial();
        Shader* meshShader = m->getShader();
        meshShader->use();
        if (m->hasTexture())
        {
            meshShader->setInt("uTexture", 0);
        }
        meshShader->setMat4("uModel", meshTransform->m_model);
        meshShader->setMat4("uProjection", *scene->getProj());
        meshShader->setMat4("uView", *scene->getView());
        meshShader->setVec3("uMaterial.m_amb", meshMat->m_props.m_amb);
        meshShader->setVec3("uMaterial.m_diff", meshMat->m_props.m_diff);
        meshShader->setVec3("uMaterial.m_spec", meshMat->m_props.m_spec);
        meshShader->setFloat("uMaterial.m_shine", meshMat->m_props.m_shine);
  
        //update dir light uniforms
        meshShader->setVec3("uViewPos", *scene->getMainCam()->getPos());
        meshShader->setVec3("uDirLight.m_dir", dirLightCaster->getLight()->m_dir);
        meshShader->setVec3("uDirLight.m_amb", dirLightCaster->getLight()->m_color.m_amb);
        meshShader->setVec3("uDirLight.m_diff", dirLightCaster->getLight()->m_color.m_diff);
        meshShader->setVec3("uDirLight.m_spec", dirLightCaster->getLight()->m_color.m_spec);

        if (m->hasTexture())
        {
            m->getTexture()->active(0);
            m->getTexture()->bind();
        }
        m->getVao()->bind();
        if (m->getIbo() != nullptr)
        {
            m->getIbo()->draw();
        }
        else
        {
            m->getVbo()->draw();
        }
        m->getVao()->unBind();

        if (m->hasTexture())
        {
            m->getTexture()->unBind();
        }
    }

    //render skybox last
    glDepthFunc(GL_LEQUAL);
    Mesh* skybox = scene->getSkybox();
    Shader* skyboxShader = skybox->getShader();
    skyboxShader->use();
    skyboxShader->setMat4("uProjection", *scene->getProj());
    skyboxShader->setMat4("uView", glm::mat4(glm::mat3(*scene->getView())));
    skyboxShader->setInt("uSkybox", 0);
    skybox->getVao()->bind();
    skybox->getSkyboxTexture()->active(0);
    skybox->getSkyboxTexture()->bind();
    skybox->getVbo()->draw();
    skybox->getVao()->unBind();
    skybox->getSkyboxTexture()->unBind();
    glDepthFunc(GL_LESS);
}