#pragma once

#define THREE_DIM

#if defined(_WIN32) && defined(THREE_DIM)
#define SHADER_PATH ".\\.\\Src\\Test3D\\Assets\\Hlsl\\"
#else
#define SHADER_PATH "../../Src/Test3D/Assets/Hlsl/"
#endif

#include "src/Core/Application.h"
#include "src/Core/Layer.h"
#include "src/Core/LayerStack.h"
#include "src/Core/Window.h"
#include <glm/glm.hpp>

#include "src/Renderer/VertexArray.h"
#include "src/Renderer/Buffer.h"
#include "src/Renderer/VertexBuffer.h"
#include "src/Renderer/Shader.h"
#include "src/Renderer/Camera.h"

#include <iostream>
#include <stdint.h>
#include <memory>

