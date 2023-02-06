#include "stdafx.h"
#include "Texture2D.h"

Texture2D::Texture2D(Context* const context)
    : IResource(context, ResourceType::Texture2D)
{
}

bool Texture2D::SaveToFile(const std::string& path)
{
    return true;
}

bool Texture2D::LoadFromFile(const std::string& path)
{
    texture = std::make_shared<D3D11_Texture>(context->GetSubSystem<Graphics>());
    texture->Create(path);

    return true;
}
