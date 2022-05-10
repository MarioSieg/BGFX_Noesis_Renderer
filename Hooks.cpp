#include "../../../Common/Logger.hpp"
#include "../../../Common/Panic.hpp"

namespace Aetherverse::Services::Rendering::AppGUI
{
    auto LogHook
    (
        [[maybe_unused]] const char*,
        [[maybe_unused]] std::uint32_t,
        std::uint32_t level,
        [[maybe_unused]] const char*,
        const char* msg
    ) -> void
    {
        switch (level)
        {
            case 0:
            case 1:
            case 2:
            default:    Info("[GUI-Frontend]: {}", msg);      break;
            case 3:     Warn("[GUI-Frontend]: {}", msg);      break;
            case 4:     Critical("[GUI-Frontend]: {}", msg);  break;
        }
    }

    auto ErrorHook
    (
        [[maybe_unused]] const char*,
        [[maybe_unused]] std::uint32_t,
        const char* msg,
        const bool fatal
    ) -> void
    {
        if (fatal)
        {
            Panic(Format("GUI-Frontend]: {}", msg));
        }
        else
        {
            Critical("[GUI-Frontend]: {}", msg);
        }
    }
}
