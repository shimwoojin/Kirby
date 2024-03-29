#include "stdafx.h"
#include "Collide.h"
#include "Scene/Actors/Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/StateComponent.h"

bool Collide::IsCollided(Actor* lhs, Actor* rhs)
{
	D3DXVECTOR3 lhs_scale = lhs->GetTransform()->GetScale();
	D3DXVECTOR3 lhs_position = lhs->GetTransform()->GetPosition();

	D3DXVECTOR3 rhs_scale = rhs->GetTransform()->GetScale();
	D3DXVECTOR3 rhs_position = rhs->GetTransform()->GetPosition();

	int min_x1 = lhs_position.x - lhs_scale.x / 2;
	int max_x1 = lhs_position.x + lhs_scale.x / 2;
	int min_y1 = lhs_position.y - lhs_scale.y / 2;
	int max_y1 = lhs_position.y + lhs_scale.y / 2;

	int min_x2 = rhs_position.x - rhs_scale.x / 2;
	int max_x2 = rhs_position.x + rhs_scale.x / 2;
	int min_y2 = rhs_position.y - rhs_scale.y / 2;
	int max_y2 = rhs_position.y + rhs_scale.y / 2;

	if (min_x1 < max_x2 && max_x1 > min_x2 && min_y1 < max_y2 && max_y1 > min_y2) return true;
	else return false;
}

bool Collide::IsCollidedActionBox(Actor* lhs, Actor* rhs, float x, float y)
{
	D3DXVECTOR3 lhs_scale = lhs->GetTransform()->GetScale();
	D3DXVECTOR3 lhs_position = lhs->GetTransform()->GetPosition();

	D3DXVECTOR3 rhs_scale = rhs->GetTransform()->GetScale();
	D3DXVECTOR3 rhs_position = rhs->GetTransform()->GetPosition();

	bool IsLeft = lhs->GetComponent<StateComponent>()->GetIsMirroredAnimation();

	int min_x1;
	int max_x1;

	if (IsLeft == false)
	{
		min_x1 = lhs_position.x;
		max_x1 = lhs_position.x + lhs_scale.x * x;
	}
	else
	{
		min_x1 = lhs_position.x - lhs_scale.x * x;
		max_x1 = lhs_position.x;
	}

	int min_y1 = lhs_position.y - lhs_scale.y * y / 2;
	int max_y1 = lhs_position.y + lhs_scale.y * y / 2;

	int min_x2 = rhs_position.x - rhs_scale.x / 2;
	int max_x2 = rhs_position.x + rhs_scale.x / 2;
	int min_y2 = rhs_position.y - rhs_scale.y / 2;
	int max_y2 = rhs_position.y + rhs_scale.y / 2;

	if (min_x1 < max_x2 && max_x1 > min_x2 && min_y1 < max_y2 && max_y1 > min_y2) return true;
	else return false;
}

bool Collide::CollideLeftRightDown(Actor* lhs, Actor* rhs)
{
	D3DXVECTOR3 lhs_scale = lhs->GetTransform()->GetScale();
	D3DXVECTOR3 lhs_position = lhs->GetTransform()->GetPosition();

	D3DXVECTOR3 rhs_scale = rhs->GetTransform()->GetScale();
	D3DXVECTOR3 rhs_position = rhs->GetTransform()->GetPosition();

	int min_x1 = lhs_position.x - lhs_scale.x / 2;
	int max_x1 = lhs_position.x + lhs_scale.x / 2;
	int min_y1 = lhs_position.y - lhs_scale.y / 2;
	int max_y1 = lhs_position.y + lhs_scale.y / 2;

	int min_x2 = rhs_position.x - rhs_scale.x / 2;
	int max_x2 = rhs_position.x + rhs_scale.x / 2;
	int min_y2 = rhs_position.y - rhs_scale.y / 2;
	int max_y2 = rhs_position.y + rhs_scale.y / 2;

	if (min_x1 < max_x2 && max_x1 > min_x2 && max_y1 < max_y2 && max_y1 > min_y2) return true;
	else return false;
}

uint Collide::GetCollide_Dir(Actor* lhs, Actor* rhs)
{
	D3DXVECTOR3 lhs_scale = lhs->GetTransform()->GetScale();
	D3DXVECTOR3 lhs_position = lhs->GetTransform()->GetPosition();

	D3DXVECTOR3 rhs_scale = rhs->GetTransform()->GetScale();
	D3DXVECTOR3 rhs_position = rhs->GetTransform()->GetPosition();

	int min_x1 = lhs_position.x - lhs_scale.x / 2;
	int max_x1 = lhs_position.x + lhs_scale.x / 2;
	int min_y1 = lhs_position.y - lhs_scale.y / 2;
	int max_y1 = lhs_position.y + lhs_scale.y / 2;

	int min_x2 = rhs_position.x - rhs_scale.x / 2;
	int max_x2 = rhs_position.x + rhs_scale.x / 2;
	int min_y2 = rhs_position.y - rhs_scale.y / 2;
	int max_y2 = rhs_position.y + rhs_scale.y / 2;

	uint temp = Collide_Null;

	if (min_x1 < max_x2 && max_x1 > min_x2 && min_y1 < max_y2 && max_y1 > min_y2)
	{
		if (lhs_position.x < rhs_position.x) temp = (uint)(temp | Collide_Right);
		else temp = (uint)(temp | Collide_Left);
		if (lhs_position.y < rhs_position.y) temp = (uint)(temp | Collide_Up);
		else temp = (uint)(temp | Collide_Down);
	}

	return temp;
}
