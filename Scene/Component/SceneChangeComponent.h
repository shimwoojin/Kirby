#pragma once
#include "IComponent.h"

class SceneChangeComponent : public IComponent
{
public:
	using IComponent::IComponent;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void SetScene(class Scene* scene);

public:
	static uint scene_count;

private:
	static std::string scene_names[10];

private:
	class Scene* scene = nullptr;
	class InputManager* key = nullptr;
	class SceneManager* scene_manager = nullptr;
};

