#pragma once
#include "IComponent.h"

class ColliderComponent : public IComponent
{
public:
	using IComponent::IComponent;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void SetScene(class Scene* scene) { this->scene = scene; }

	bool GetCollideMapTile() { return collide_maptile; }
	bool GetCollideMonster() { return collide_monster; }

private:
	bool CollideMapTile();
	bool CollideMonster();

private:
	class Scene* scene = nullptr;

	bool collide_maptile = false;
	bool collide_monster = false;
};

