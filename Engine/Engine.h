#pragma once

#define THREE_DIM

#ifdef _DEBUG && defined(_WIN32)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define EMBER_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define EMBER_DELETE delete
#else
#define EMBER_NEW new
#define EMBER_DELETE delete
#endif

#if defined(_WIN32) && defined(THREE_DIM)
#define SHADER_PATH ".\\.\\Src\\Test3D\\Assets\\Hlsl\\"
#endif

#include "src/core/Glm.h"
#include "src/core/Application.h"
#include "src/core/Window.h"
#include "src/core/Gui.h"
#include "src/core/ImGui.h"
#include "src/core/OpenGL.h"
#include "src/core/Glm.h"

#include "src/renderer/Renderer.h"
#include "src/renderer/Shader.h"

#include "src/scene/Camera.h"

