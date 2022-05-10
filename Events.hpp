#pragma once

#include "../../../Common/Input.hpp"

#include <GLFW/glfw3.h>
#include <NoesisPCH.h>

namespace Aetherverse::Services::Rendering::AppGUI::Events
{
    extern auto RegisterAll() -> void;

    inline constinit Noesis::IView* EventProxy;

    extern auto OnKeyCallback(GLFWwindow* window, signed key, signed scancode, signed action, signed mods) -> void;
    extern auto OnCharCallback(GLFWwindow* window, unsigned codePoint) -> void;
    extern auto OnMousePositionCallback(GLFWwindow* const window, const double posX, const double posY) -> void;
    extern auto OnMouseButtonCallback(GLFWwindow* window, signed button, signed action, signed mods) -> void;

    [[nodiscard]] extern auto TranslateKey(Key key) noexcept -> Noesis::Key;
    [[nodiscard]] extern auto TranslateMouseButton(MouseButton button) noexcept -> Noesis::MouseButton;
}
