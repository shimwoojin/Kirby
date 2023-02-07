#pragma once
#include "IComponent.h"

enum class State
{
	Idle,
	Walk,
	Run,
	Jump,
	OnAir,
	Fly,
	Action,
	Damaged,
	Pulled,
	Dead
};

class StateComponent final : public IComponent
{
public:
	using IComponent::IComponent;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	const State& GetState() { return state; }
	void SetState(const State& state) { this->state = state; }

	void SetIsMirroredAnimation(bool is_mirrored_animation) { this->is_mirrored_animation = is_mirrored_animation;  }
	bool GetIsMirroredAnimation() { return is_mirrored_animation; }

private:
	void UpdateActor();
	void UpdateMonster();

private:
	InputManager* key = nullptr;
	std::shared_ptr<class PhysicsComponent> physics = nullptr;
	std::shared_ptr<class ColliderComponent> collider = nullptr;

	State state = State::Idle;

	bool is_mirrored_animation = false;
};

