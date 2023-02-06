#pragma once
#include "IResource.h"

enum class RepeatType : uint
{
	Once, Loop
};

struct Keyframe final
{
	Keyframe() = default;
	Keyframe(const D3DXVECTOR2& offset, const D3DXVECTOR2& size, const double& time)
		: offset(offset)
		, size(size)
		, time(time)
	{}

	D3DXVECTOR2 offset{ 0.0f, 0.0f };
	D3DXVECTOR2 size{ 0.0f, 0.0f };
	double time{ 0.0 };
};

class Animation final : public IResource
{
public:
	Animation(class Context* const context);
	~Animation();

	virtual bool SaveToFile(const std::string& path) override;
	virtual bool LoadFromFile(const std::string& path) override;

	const RepeatType& GetRepeatType() const { return repeat_type; }
	void SetRepeatType(const RepeatType& repeat_type) { this->repeat_type = repeat_type; }

	const D3DXVECTOR2& GetSpriteTextureSize() const { return sprite_texture_size; }
	void SetSpriteTextureSize(const D3DXVECTOR2& size) { this->sprite_texture_size = size; }

	const std::shared_ptr<class D3D11_Texture>& GetSpriteTexture() const { return sprite_texture; }
	void SetSpriteTexture(const std::shared_ptr<class D3D11_Texture>& sprite_texture) { this->sprite_texture = sprite_texture; }

	void SetSpriteTexture(const std::string& path);

	const std::string& GetSpriteTexturePath() const { return sprite_texture_path; }
	void SetSpriteTexturePath(const std::string& path) { this->sprite_texture_path = path; }

	const std::vector<Keyframe>& GetKeyframes() const { return keyframes; }
	void SetKeyframes(const std::vector<Keyframe>& keyframes) { this->keyframes = keyframes; }

	void AddKeyframe(const Keyframe& keyframe);
	void AddKeyframe(const D3DXVECTOR2& offset, const D3DXVECTOR2& size, const double& time);

	const Keyframe* const GetKeyframeFromIndex(const uint& index);
	const uint GetKeyframeCount() const { return keyframes.size(); }

private:
	RepeatType repeat_type = RepeatType::Loop;

	std::shared_ptr<class D3D11_Texture> sprite_texture;
	D3DXVECTOR2 sprite_texture_size = D3DXVECTOR2(1.0f, 1.0f);
	std::string sprite_texture_path = "";

	std::vector<Keyframe> keyframes;

};

