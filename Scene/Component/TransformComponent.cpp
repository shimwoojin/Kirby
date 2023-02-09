#include "stdafx.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(
	class Context* const context,
	class Actor* const actor,
	class TransformComponent* const transform
)
	: IComponent(context, actor, transform)
{
	D3DXMatrixIdentity(&local);
	D3DXMatrixIdentity(&world);
	UpdateTransform();
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Initialize()
{
}

void TransformComponent::Update()
{
}

void TransformComponent::Destroy()
{
}

void TransformComponent::SetLocalScale(const D3DXVECTOR3& scale)
{
	if (this->local_scale == scale) return;

	this->local_scale = scale;
	UpdateTransform();

	//월드 = 자신 * 부모
	//월드 = 
}

void TransformComponent::SetLocalPosition(const D3DXVECTOR3& position)
{
	if (this->local_position == position) return;

	this->local_position = position;
	UpdateTransform();
}

void TransformComponent::SetLocalRotation(const D3DXVECTOR3& rotation)
{
	if (this->local_rotation == rotation) return;

	this->local_rotation = rotation;
	UpdateTransform();
}

const D3DXVECTOR3 TransformComponent::GetScale()
{
	D3DXVECTOR3 world_scale;
	D3DXQUATERNION temp1;
	D3DXVECTOR3 temp2;

	D3DXMatrixDecompose(&world_scale, &temp1, &temp2, &world);

	return world_scale;
}

void TransformComponent::SetScale(const D3DXVECTOR3& world_scale)
{
	if (GetScale() == world_scale) return;

	/*
		world_scale 2 2 1
	
		월드 = 자신 * 부모

		자신 = 2 2 1
		부모 = 3 3 1
		월드 = 6 6 1

		월드 / 부모 = 자신
	*/

	if (HasParent() == true)
	{
		D3DXVECTOR3 scale;
		D3DXVECTOR3 parent_scale = parent.lock()->GetScale();
		scale.x = world_scale.x / parent_scale.x;
		scale.y = world_scale.y / parent_scale.y;
		scale.z = world_scale.y / parent_scale.z;

		SetLocalScale(scale);
	}
	else
		SetLocalScale(world_scale);
}

const D3DXVECTOR3 TransformComponent::GetPosition()
{
	D3DXVECTOR3 world_position;
	D3DXQUATERNION temp1;
	D3DXVECTOR3 temp2;

	D3DXMatrixDecompose(&temp2, &temp1, &world_position, &world);

	return world_position;
}

void TransformComponent::SetPosition(const D3DXVECTOR3& world_position)
{
	if (GetPosition() == world_position) return;

	if (HasParent() == true)
	{
		if (GetLocalPosition() == world_position) return;

		D3DXMATRIX inverse;
		D3DXMatrixInverse(&inverse, nullptr, &parent.lock()->GetWorldMatrix());

		//1x3 * 4x4
		//함수로 처리
		D3DXVECTOR3 position;
		D3DXVec3TransformCoord(&position, &world_position, &inverse);

		SetLocalPosition(position);
	}
	else
		SetLocalPosition(world_position);

}

const D3DXVECTOR3 TransformComponent::GetRotation()
{
	D3DXQUATERNION world_rotation;
	D3DXVECTOR3 temp2;

	D3DXMatrixDecompose(&temp2, &world_rotation, &temp2, &world);

	D3DXMATRIX rotation;
	D3DXMatrixRotationQuaternion(&rotation, &world_rotation);

	return D3DXVECTOR3 // Y - X - Z
	(
		atan2(rotation._31, rotation._33),
		atan2(-rotation._32, sqrt(pow(rotation._12, 2) + pow(rotation._22, 2))),
		atan2(rotation._12, rotation._22)
	);
}

void TransformComponent::SetRotation(const D3DXVECTOR3& world_rotation)
{
	if (GetRotation() == world_rotation) return;

	if (HasParent() == true)
	{
		D3DXMATRIX inverse;
		auto temp = GetWorldRotationMatrix();
		D3DXMatrixInverse(&inverse, nullptr, &temp);

		D3DXVECTOR3 rotation;
		D3DXVec3TransformNormal(&rotation, &world_rotation, &inverse);

		SetLocalRotation(rotation);
	}
	else
		SetLocalRotation(world_rotation);
}

const D3DXMATRIX TransformComponent::GetWorldRotationMatrix()
{
	D3DXQUATERNION world_rotation;
	D3DXVECTOR3 temp;

	D3DXMatrixDecompose(&temp, &world_rotation, &temp, &world);

	D3DXMATRIX rotation;
	D3DXMatrixRotationQuaternion(&rotation, &world_rotation);

	return rotation;
}

const D3DXVECTOR3 TransformComponent::GetRight() const
{
	D3DXVECTOR3 right;
	D3DXVECTOR3 vec(1, 0, 0);

	D3DXVec3TransformNormal(&right, &vec, &world);

	return right;
}

const D3DXVECTOR3 TransformComponent::GetUp() const
{
	D3DXVECTOR3 up;
	D3DXVECTOR3 vec(0, 1, 0);

	D3DXVec3TransformNormal(&up, &vec, &world);

	return up;
}

const D3DXVECTOR3 TransformComponent::GetForward() const
{
	D3DXVECTOR3 forward;
	D3DXVECTOR3 vec(0, 0, 1);

	D3DXVec3TransformNormal(&forward, &vec, &world);

	return forward;
}

void TransformComponent::UpdateTransform()
{
	D3DXMATRIX S, R, T;

	D3DXMatrixScaling(&S, local_scale.x, local_scale.y, local_scale.z);

	//yaw : 수직 방향 회전축
	//pitch : 횡(좌우) 방향 회전축
	//roll : 종(앞뒤) 방향 회전축
	D3DXMatrixRotationYawPitchRoll(&R, local_rotation.y, local_rotation.x, local_rotation.z);
	D3DXMatrixTranslation(&T, local_position.x, local_position.y, local_position.z);

	local = S * R * T;

	if (HasParent() == true)
		world = local * parent.lock()->GetWorldMatrix();
	else
		world = local;

	for (const auto& child : childs)
	{
		if (child.expired() != true)
			child.lock()->UpdateTransform();
	}
}

void TransformComponent::SetParent(std::weak_ptr<TransformComponent> const new_parent)
{
	if (new_parent.expired() == true) return;
	if (new_parent.lock().get() == this) return;

	parent = new_parent;
}

std::weak_ptr<TransformComponent> const TransformComponent::GetChildFromIndex(const uint& index)
{
	std::shared_ptr<TransformComponent> temp;

	if (HasChilds() == false) return temp;
	if (index >= GetChildCount()) return temp;
	
	return childs[index];
}

void TransformComponent::AddChild(std::weak_ptr<TransformComponent> const child)
{
	if (child.expired() == true) return;
	if (child.lock().get() == this) return;

	childs.emplace_back(child);
}
