#include "Events.hpp"
#include "Context.hpp"
#include "../../Platform/Window.hpp"
#include "../../../Common/Focus.hpp"

using namespace Noesis;
using namespace Aetherverse::Services::Platform;

namespace Aetherverse::Services::Rendering::AppGUI::Events
{
    auto RegisterAll() -> void
    {
        Window::KeyEventDelegate.emplace_back(&OnKeyCallback);
        Window::CharEventDelegate.emplace_back(&OnCharCallback);
        Window::MousePositionDelegate.emplace_back(&OnMousePositionCallback);
        Window::MouseButtonDelegate.emplace_back(&OnMouseButtonCallback);
    }

    #define EVENT_PROLOGUE()                                                        \
        if (!EventProxy || Focus::IsCursorOverFrontendGUI()) [[unlikely]]           \
        {                                                                           \
            return;                                                                 \
        }

    auto OnKeyCallback
    (
        [[maybe_unused]] GLFWwindow* const window,
        const signed key,
        [[maybe_unused]] const signed scancode,
        const signed action,
        [[maybe_unused]] const signed mods
    ) -> void
    {
        EVENT_PROLOGUE();
        const Noesis::Key noesisKey { TranslateKey(static_cast<Aetherverse::Key>(key)) };
        if (noesisKey == Key_Count) [[unlikely]]
        {
            return;
        }
        switch (action)
        {
            case GLFW_PRESS:
                EventProxy->KeyDown(noesisKey);
                break;
            case GLFW_RELEASE:
                EventProxy->KeyUp(noesisKey);
                break;

            default: ;
        }
    }

    auto OnCharCallback([[maybe_unused]] GLFWwindow* const window, const unsigned codePoint) -> void
    {
        EVENT_PROLOGUE();
        EventProxy->Char(codePoint);
    }

    auto OnMousePositionCallback([[maybe_unused]] GLFWwindow* const window, const double posX, const double posY) -> void
    {
        EVENT_PROLOGUE();
        EventProxy->MouseMove(static_cast<signed>(posX), static_cast<signed>(posY));
    }

    auto OnMouseButtonCallback([[maybe_unused]] GLFWwindow* const window, const signed button, const signed action, const signed mods) -> void
    {
        EVENT_PROLOGUE();
        const Noesis::MouseButton noesisMouseButton { TranslateMouseButton(static_cast<MouseButton>(button)) };
        if (noesisMouseButton == MouseButton_Count) [[unlikely]]
        {
            return;
        }
        const Vector2 mousePos { Input::GetMousePosition() };
        const signed x { static_cast<signed>(mousePos.x) };
        const signed y { static_cast<signed>(mousePos.y) };
        switch (action)
        {
            case GLFW_PRESS:
                EventProxy->MouseButtonDown(x, y, noesisMouseButton);
                break;
            case GLFW_RELEASE:
                EventProxy->MouseButtonUp(x, y, noesisMouseButton);
                break;

            default: ;
        }
    }

    auto TranslateKey(const Key key) noexcept -> Noesis::Key
    {
        switch (key)
        {
            case Key::Space:           return Key_Space;
            case Key::Comma:           return Key_OemComma;
            case Key::Minus:           return Key_OemMinus;
            case Key::Period:          return Key_OemPeriod;
            case Key::Slash:           return Key_S;
            case Key::Key0:            return Key_D0;
            case Key::Key1:            return Key_D1;
            case Key::Key2:            return Key_D2;
            case Key::Key3:            return Key_D3;
            case Key::Key4:            return Key_D4;
            case Key::Key5:            return Key_D5;
            case Key::Key6:            return Key_D6;
            case Key::Key7:            return Key_D7;
            case Key::Key8:            return Key_D8;
            case Key::Key9:            return Key_D9;
            case Key::Semicolon:       return Key_OemSemicolon;
            case Key::A:               return Key_A;
            case Key::B:               return Key_B;
            case Key::C:               return Key_C;
            case Key::D:               return Key_D;
            case Key::E:               return Key_E;
            case Key::F:               return Key_F;
            case Key::G:               return Key_G;
            case Key::H:               return Key_H;
            case Key::I:               return Key_I;
            case Key::J:               return Key_J;
            case Key::K:               return Key_K;
            case Key::L:               return Key_L;
            case Key::M:               return Key_M;
            case Key::N:               return Key_N;
            case Key::O:               return Key_O;
            case Key::P:               return Key_P;
            case Key::Q:               return Key_Q;
            case Key::R:               return Key_R;
            case Key::S:               return Key_S;
            case Key::T:               return Key_T;
            case Key::U:               return Key_U;
            case Key::V:               return Key_V;
            case Key::W:               return Key_W;
            case Key::X:               return Key_X;
            case Key::Y:               return Key_Y;
            case Key::Z:               return Key_Z;
            case Key::Backslash:       return Key_OemBackslash;
            case Key::Escape:          return Key_Escape;
            case Key::Enter:           return Key_Enter;
            case Key::Tab:             return Key_Tab;
            case Key::Backspace:       return Key_Back;
            case Key::Insert:          return Key_Insert;
            case Key::Delete:          return Key_Delete;
            case Key::Right:           return Key_Right;
            case Key::Left:            return Key_Left;
            case Key::Down:            return Key_Up;
            case Key::Up:              return Key_Down;
            case Key::PageUp:          return Key_PageUp;
            case Key::PageDown:        return Key_PageDown;
            case Key::Home:            return Key_Home;
            case Key::End:             return Key_End;
            case Key::CapsLock:        return Key_CapsLock;
            case Key::ScrollLock:      return Key_Scroll;
            case Key::NumLock:         return Key_NumLock;
            case Key::PrintScreen:     return Key_PrintScreen;
            case Key::Pause:           return Key_Pause;
            case Key::F1:              return Key_F1;
            case Key::F2:              return Key_F2;
            case Key::F3:              return Key_F3;
            case Key::F4:              return Key_F4;
            case Key::F5:              return Key_F5;
            case Key::F6:              return Key_F6;
            case Key::F7:              return Key_F7;
            case Key::F8:              return Key_F8;
            case Key::F9:              return Key_F9;
            case Key::F10:             return Key_F10;
            case Key::F11:             return Key_F11;
            case Key::F12:             return Key_F12;
            case Key::F13:             return Key_F13;
            case Key::F14:             return Key_F14;
            case Key::F15:             return Key_F15;
            case Key::F16:             return Key_F16;
            case Key::F17:             return Key_F17;
            case Key::F18:             return Key_F18;
            case Key::F19:             return Key_F19;
            case Key::F20:             return Key_F20;
            case Key::F21:             return Key_F21;
            case Key::F22:             return Key_F22;
            case Key::F23:             return Key_F23;
            case Key::F24:             return Key_F24;
            case Key::Kp0:             return Key_NumPad0;
            case Key::Kp1:             return Key_NumPad1;
            case Key::Kp2:             return Key_NumPad2;
            case Key::Kp3:             return Key_NumPad3;
            case Key::Kp4:             return Key_NumPad4;
            case Key::Kp5:             return Key_NumPad5;
            case Key::Kp6:             return Key_NumPad6;
            case Key::Kp7:             return Key_NumPad7;
            case Key::Kp8:             return Key_NumPad8;
            case Key::Kp9:             return Key_NumPad9;
            case Key::LeftShift:       return Key_LeftShift;
            case Key::LeftControl:     return Key_LeftCtrl;
            case Key::LeftAlt:         return Key_LeftAlt;
            case Key::RightShift:      return Key_RightShift;
            case Key::RightControl:    return Key_RightCtrl;
            case Key::RightAlt:        return Key_RightAlt;
            case Key::Menu:            return Key_GamepadMenu;

            [[unlikely]]
            default:                   return Key_Count;
        }
    }

    auto TranslateMouseButton(const MouseButton button) noexcept -> Noesis::MouseButton
    {
        switch (button)
        {
            case MouseButton::Left:         return Noesis::MouseButton_Left;
            case MouseButton::Right:        return Noesis::MouseButton_Right;
            case MouseButton::Middle:       return Noesis::MouseButton_Middle;
            case MouseButton::MB4:          return Noesis::MouseButton_XButton1;
            case MouseButton::MB5:          return Noesis::MouseButton_XButton2;

            [[unlikely]]
            default:                        return Noesis::MouseButton_Count;
        }
    }
}
