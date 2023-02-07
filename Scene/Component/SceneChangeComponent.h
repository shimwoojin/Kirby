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

private:
	static std::string scene_names[10];
	static uint scene_count;

private:
	class Scene* scene = nullptr;
	class InputManager* key = nullptr;
	class SceneManager* scene_manager = nullptr;
};

