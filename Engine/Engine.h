#pragma once

#define SHADER_PATH ".\\.\\Src\\Test3D\\assets\\Hlsl\\"
#define OBJ_PATH ".\\.\\Src\\Test3D\\assets\\models\\"
#define TEXTURE_PATH ".\\.\\Src\\Test3D\\assets\\textures\\"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tiny_obj_loader.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "src/core/Application.h"
#include "src/core/Window.h"
#include "src/core/Gui.h"
#include "src/core/Memory.h"
#include "src/core/Logger.h"

#include "src/renderer/Renderer.h"
#include "src/renderer/Shader.h"

#include "src/scene/Camera.h"
#include "src/scene/Scene.h"
#include "src//scene/Entity.h"

