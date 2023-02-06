#pragma once
#include "IResource.h"

class Texture2D : public IResource
{
public:
	Texture2D(class Context* const context);
	~Texture2D() = default;

	virtual bool SaveToFile(const std::string& path) override;
	virtual bool LoadFromFile(const std::string& path) override;

	const std::shared_ptr<class D3D11_Texture>& GetSpriteTexture() const { return texture; }
	void SetSpriteTexture(const std::shared_ptr<class D3D11_Texture>& sprite_texture) { this->texture = sprite_texture; }

private:
	std::shared_ptr<D3D11_Texture> texture;
};

