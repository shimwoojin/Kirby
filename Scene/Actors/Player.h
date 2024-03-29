#pragma once
#include "Actor.h"
#include "Monster.h"

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

	KirbyState GetKirbyState() { return state; }
	void SetKirbyState(KirbyState state) { this->state = state; }

	Monster_Attribute GetKirbyEaten() { return kirby_eaten; }
	void SetKirbyEaten(Monster_Attribute kirby_eaten) { this->kirby_eaten = kirby_eaten; }

	float GetHp() { return hp; }
	void SetHp(float hp) { this->hp = hp; }
	void SubHp() { hp -= 50.0f; }

private:
	void AddComponents();
	void AddAnimations();

private:
	KirbyState state = KirbyState::Hungry;
	Monster_Attribute kirby_eaten = Monster_Attribute::None;

	float hp = 500.0f;
};

