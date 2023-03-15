#pragma once

#define THREE_DIM

#if defined(_WIN32) && defined(THREE_DIM)
#define SHADER_PATH ".\\.\\Src\\Test3D\\Assets\\Hlsl\\"
#define OBJ_PATH ".\\.\\Src\\Test3D\\Assets\\objFiles\\"
#define TEXTURE_PATH ".\\.\\Src\\Test3D\\Assets\\textures\\"
#endif

#if defined(__APPLE__)
#define SHADER_PATH "../../Src/Test3D/Assets/Hlsl/"
#define OBJ_PATH "../../Src/Test3D/Assets/objFiles/"
#define TEXTURE_PATH "../../Src/Test3D/Assets/textures/"
#endif

#include "libs/objLoader/tiny_obj_loader.h"

#include "src/core/Glm.h"
#include "src/core/Application.h"
#include "src/core/Window.h"
#include "src/core/Gui.h"
#include "src/core/ImGui.h"
#include "src/core/OpenGL.h"
#include "src/core/Glm.h"
#include "src/core/Memory.h"

#include "src/renderer/Renderer.h"
#include "src/renderer/Shader.h"

#include "src/scene/Camera.h"
#include "src/scene/Scene.h"
#include "src//scene/Entity.h"

