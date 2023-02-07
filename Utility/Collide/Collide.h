#pragma once

enum Collide_Dir : uint
{
	Collide_Null	= 0,
	Collide_Left	= 1,
	Collide_Right	= 2,
	Collide_Up		= 4,
	Collide_Down	= 8
};

class Collide
{
public:
	static bool IsCollided(class Actor* lhs, class Actor* rhs);
	static bool CollideLeftRightDown(class Actor* lhs, class Actor* rhs);
	static uint GetCollide_Dir(class Actor* lhs, class Actor* rhs);
};

