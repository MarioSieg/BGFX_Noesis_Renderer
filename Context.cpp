#include <cstdint>
#include <cstddef>

#include "Context.hpp"
#include "License.hpp"

#include "../../../Common/SystemVariables.hpp"
#include "../../../Common/Time.hpp"

#include "Packages.hpp"
#include "Cursor.hpp"
#include "Hooks.hpp"
#include "HoverTest.hpp"
#include "Events.hpp"

#include "Providers/LocalXAMLProvider.hpp"
#include "Providers/LocalFontProvider.hpp"
#include "Providers/LocalTextureProvider.hpp"

#include <NoesisPCH.h>

using namespace Noesis;

namespace Aetherverse::Services::Rendering::AppGUI
{
    Context::Context( const Descriptor& descriptor) :
    Descriptor_ { descriptor },
    RenderDevice_ { *new RenderDevice { descriptor } }
    {
        // set handlers
        SetLogHandler(&LogHook);
        SetErrorHandler(&ErrorHook);

        // active license
        GUI::SetLicense(LicenseName, LicenseKey);

        // initialize
        GUI::Init();
        Packages::Initialize();

        // bind resource providers
        GUI::SetXamlProvider(MakePtr<LocalXAMLProvider>("Assets"));
        GUI::SetFontProvider(MakePtr<LocalFontProvider>("Assets"));
        GUI::SetTextureProvider(MakePtr<LocalTextureProvider>("Assets"));
        GUI::SetFontDefaultProperties(15.F, FontWeight_Normal, FontStretch_Normal, FontStyle_Normal);
        GUI::LoadApplicationResources("Theme/NoesisTheme.LightBlue.xaml");

        if constexpr (IS_CLIENT)
        {
            GUI::SetCursorCallback(nullptr, &CursorCallback);
        }
        Events::RegisterAll();

        this->CreateViewFromFile("Widgets/App.xaml");
    }

    Context::~Context()
    {
        if (this->Root_)
        {
            this->Root_.Reset();
        }
        if (this->View_)
        {
            this->View_.Reset();
        }
        this->RenderDevice_.Reset();
        Packages::Shutdown();
        GUI::Shutdown();
    }

    auto Context::Frame() -> void
    {
        if (const SystemVar& var { GetSystemVar(SystemVarID::R_EnableFrontendGUI) }; this->View_ && var.Value.AsBool) [[likely]]
        {
            this->View_->Update(Time::GetTime());
            this->View_->GetRenderer()->UpdateRenderTree();
            this->View_->GetRenderer()->RenderOffscreen();
            this->View_->GetRenderer()->Render();
            IsHoveredThisFrame = HoverTest(this->Root_);
        }
        else
        {
            AppGUI::IsHoveredThisFrame = false;
        }
    }

    auto Context::Resize(const std::uint16_t width, const std::uint16_t height) -> void
    {
        if (this->View_) [[likely]]
        {
            this->View_->SetSize(static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height));
        }
        this->RenderDevice_->Resize(width, height);
    }

    auto Context::CreateViewFromFile(const char* const fileName) -> void
    {
        this->Root_ = Noesis::GUI::LoadXaml<Noesis::Grid>(fileName);
        this->View_ = Noesis::GUI::CreateView(this->Root_);
        this->View_->SetSize
        (
            static_cast<std::uint32_t>(this->Descriptor_.Display.Width),
            static_cast<std::uint32_t>(this->Descriptor_.Display.Height)
        );
        this->View_->SetFlags(Noesis::RenderFlags_PPAA | Noesis::RenderFlags_LCD);
        this->View_->GetRenderer()->Init(dynamic_cast<Noesis::RenderDevice*>(&*this->RenderDevice_));
        this->View_->SetTessellationMaxPixelError(Noesis::TessellationMaxPixelError::HighQuality());
        this->View_->SetScale(1.F);

        Events::EventProxy = this->View_;
    }
}
