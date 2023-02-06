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
private:
	void AddComponents();
	void AddAnimations();


private:
	Monster_Attribute attribute = Monster_Attribute::None;
};

