#pragma once

#include <NoesisPCH.h>

namespace Aetherverse::Services::Rendering::AppGUI
{
    struct LocalXAMLProvider final : public Noesis::XamlProvider
    {
        explicit LocalXAMLProvider(const char* root);

    private:
        [[nodiscard]] virtual auto LoadXaml(const Noesis::Uri& uri) -> Noesis::Ptr<Noesis::Stream> override;

        char RootPath_[512] { };
    };
}
