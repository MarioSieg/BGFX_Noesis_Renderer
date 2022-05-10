#pragma once

#include <NoesisPCH.h>

#include "../../../Common/Config/Descriptor.hpp"
#include "Renderer/RenderDevice.hpp"

namespace Aetherverse::Services::Rendering::AppGUI
{
    struct Context final
    {
        static constexpr const char* const AppFile { "Widgets/App.xaml" };

        Context(const Descriptor& descriptor);
        ~Context();

        auto Frame() -> void;
        auto Resize(std::uint16_t width, std::uint16_t height) -> void;
        auto CreateViewFromFile(const char* fileName) -> void;

    private:
        const Descriptor& Descriptor_;
        Noesis::Ptr<RenderDevice> RenderDevice_ { };
        Noesis::Ptr<Noesis::Grid> Root_ { };
        Noesis::Ptr<Noesis::IView> View_ { };
    };
}
