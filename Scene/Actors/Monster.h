#pragma once
#include "Actor.h"

enum class Monster_Attribute : uint
{
	None,
	Fire,
	Ice,
};

class Monster : public Actor
{
public:
	Monster(class Context* const context);

	const Monster_Attribute& GetAttribute() const { return attribute; }
	void SetAttribute(const Monster_Attribute& attribute) { this->attribute = attribute; }

	float GetHp() { return hp; }
	void SubHp() { hp -= 2.0f; }
	void SetHp(float hp) { this->hp = hp; }

	void SetIsBoss(bool is_boss) { this->is_boss = is_boss; }
	bool GetIsBoss() { return is_boss; }

private:
	void AddComponents();
	void AddAnimations();

private:
	Monster_Attribute attribute = Monster_Attribute::None;
	bool is_boss = false;

	float hp = 200.0f;
};

