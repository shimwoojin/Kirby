#pragma once
#include "IComponent.h"

class MoveScriptComponent final : public IComponent
{
public:
	using IComponent::IComponent;
	~MoveScriptComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void SetSceneSize(SceneSize scene_size);
	void ClipActor(D3DXVECTOR3& position);

private:
	SceneSize scene_size;

	float jump_speed = 5.0f;
	float speed = 2.0f;
	float run_speed = 3.0f;
};

