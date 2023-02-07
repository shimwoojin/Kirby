#pragma once

class Collide
{
public:
	static bool IsCollided(class Actor* lhs, class Actor* rhs);
	static bool CollideLeftRightDown(class Actor* lhs, class Actor* rhs);
};

