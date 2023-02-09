#pragma once
#include "IComponent.h"

class ActionComponent : public IComponent
{
public:
	using IComponent::IComponent;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	bool GetIsUpdate() { return is_update; }
	void SetIsUpdate(bool is_update) { this->is_update = is_update; }

	void SetScene(class Scene* scene) { this->scene = scene; }

	void Swallow();
	void Attack();

private:
	class Scene* scene = nullptr;

	bool is_update = false;
};

