#include <cstdint>
#include <cstddef>

#include "LocalTextureProvider.hpp"
#include "../../../../Common/Logger.hpp"

using namespace Noesis;

namespace Aetherverse::Services::Rendering::AppGUI
{
    LocalTextureProvider::LocalTextureProvider(const char* const root)
    {
        StrCopy(this->RootPath_, sizeof(this->RootPath_), root);
    }

    auto LocalTextureProvider::OpenStream(const Noesis::Uri& uri) -> Noesis::Ptr<Noesis::Stream>
    {
        FixedString<512> path;
        uri.GetPath(path);

        char filename[512];

        if (StrIsNullOrEmpty(this->RootPath_))
        {
            StrCopy(filename, sizeof(filename), path.Str());
        }
        else
        {
            StrCopy(filename, sizeof(filename),this->RootPath_);
            StrAppend(filename, sizeof(filename), "/");
            StrAppend(filename, sizeof(filename), path.Str());
        }

        Info("[GUI-Frontend]: LocalTextureProvider request: {}", filename);
        return OpenFileStream(filename);
    }
}
