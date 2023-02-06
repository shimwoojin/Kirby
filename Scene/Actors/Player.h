#pragma once
#include "Actor.h"

class Player final : public Actor
{
public:
	Player(class Context* const context);

private:
	void AddComponents();
	void AddAnimations();
};

