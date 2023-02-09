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

	bool GetIsUpdate() { return is_update; }
	void SetIsUpdate(bool is_update) { this->is_update = is_update; }

	bool IsCollideMapTile() { return collide_maptile; }
	bool IsCollideMonster() { return collide_monster; }

	uint GetCollideTileDir() { return collide_tile_dir; }

	//타일
	bool IsCollideLeftTile() { return collide_tile_dir & Collide_Left; }
	bool IsCollideRightTile() { return collide_tile_dir & Collide_Right; }
	bool IsCollideUpTile() { return collide_tile_dir & Collide_Up; }
	bool IsCollideDownTile() { return collide_tile_dir & Collide_Down; }

	//몬스터
	bool IsCollideLeftMonster() { return collide_monster_dir & Collide_Left; }
	bool IsCollideRightMonster() { return collide_monster_dir & Collide_Right; }
	bool IsCollideUpMonster() { return collide_monster_dir & Collide_Up; }
	bool IsCollideDownMonster() { return collide_monster_dir & Collide_Down; }

private:
	bool CollideMapTile();
	bool CollideMonster();

private:
	class Scene* scene = nullptr;
	StopWatch stop_watch;

	bool is_update = true;

	bool collide_maptile = false;
	bool collide_monster = false;

	uint collide_tile_dir = 0;
	uint collide_monster_dir = 0;

	float collide_time = 1001.0f;
};

