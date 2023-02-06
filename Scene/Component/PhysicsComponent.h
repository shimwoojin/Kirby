#pragma once
#include "IComponent.h"

class PhysicsComponent : public IComponent
{
public:
	using IComponent::IComponent;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	bool IsUpdate() const { return is_update; }
	void SetIsUpdate(const bool is_update) { this->is_update = is_update; }

	bool IsOnGround() const { return is_on_ground; }
	void SetOnGround(const bool is_on_ground) { this->is_on_ground = is_on_ground; }

	float GetGravity() { return gravity; }
	void SetGravity(float gravity) { this->gravity = gravity; }

	void SetScene(class Scene* scene) { this->scene = scene; }

	bool CheckOnGround(class Actor* map_tile);

private:
	class Scene* scene = nullptr;

	float gravity = 0.5f;

	bool is_update = true;
	bool is_on_ground = true;
};
