#include "HoverTest.hpp"
#include "../../../Common/Input.hpp"

using namespace Noesis;

namespace Aetherverse::Services::Rendering::AppGUI
{
    auto HoverTest(const Visual* const root) -> bool
    {
        Visual* const rootElem { VisualTreeHelper::GetRoot(root) };
        const Vector2 cursorPos { Input::GetMousePosition() };
        const Point point { cursorPos.x, cursorPos.y };
        const HitTestResult hit { VisualTreeHelper::HitTest(rootElem, point) };
        return hit.visualHit != nullptr;
    }
}
