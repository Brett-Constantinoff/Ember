#pragma once
#include <string>
#include "Window.h"

namespace Ember
{
    namespace Core
    {
        class Layer
        {
        public:
            Layer(const char* name = "Layer");
            virtual ~Layer() = default;

            virtual void onAttach(Window* win) {};
            virtual void onDetach() {};
            virtual void onUpdate(float dt) {};
            virtual void onRender() {};
            virtual void onImguiRender() {};
            const char* getName();

        protected:
            const char* m_name;
        };
    }
}
