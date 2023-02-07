#pragma once
#include "Actor.h"

enum class KirbyState
{
	Hungry,
	Full,
	Fire,
	Ice
};

class Player final : public Actor
{
public:
	Player(class Context* const context);

	KirbyState GetState() { return state; }
	void SetState(KirbyState state) { this->state = state; }

private:
	void AddComponents();
	void AddAnimations();

private:
	KirbyState state = KirbyState::Hungry;
};

