#pragma once
#include "IComponent.h"

class TransformComponent final : public IComponent
{
public:
	TransformComponent(
		class Context* const context,
		class Actor* const actor,
		class TransformComponent* const transform
	);
	~TransformComponent();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	//====================================
	// [Local]
	//====================================

	const D3DXVECTOR3& GetLocalScale() const { return local_scale; }
	void SetLocalScale(const D3DXVECTOR3& scale);

	const D3DXVECTOR3& GetLocalPosition() const { return local_position; }
	void SetLocalPosition(const D3DXVECTOR3& position);

	const D3DXVECTOR3& GetLocalRotation() const { return local_rotation; }
	void SetLocalRotation(const D3DXVECTOR3& rotation);

	const D3DXMATRIX& GetLocalMatrix() const { return local; }

	//====================================
	// [World]
	//====================================

	const D3DXVECTOR3 GetScale();
	void SetScale(const D3DXVECTOR3& world_scale);

	const D3DXVECTOR3 GetPosition();
	void SetPosition(const D3DXVECTOR3& world_position);

	const D3DXVECTOR3 GetRotation();
	void SetRotation(const D3DXVECTOR3& world_rotation);

	const D3DXMATRIX GetWorldRotationMatrix();

	const D3DXMATRIX& GetWorldMatrix() const { return world; }

	const D3DXVECTOR3 GetRight() const;
	const D3DXVECTOR3 GetUp() const;
	const D3DXVECTOR3 GetForward() const;

	//====================================
	// [Transform]
	//====================================

	void UpdateTransform();
	bool HasParent() const { return parent.expired() ? false : true; }

	bool HasChilds() const { return childs.empty() != true; }

	std::weak_ptr<TransformComponent> const GetParent() { return parent; }
	void SetParent(std::weak_ptr<TransformComponent> const new_parent);

	const std::vector<std::weak_ptr<TransformComponent>>& GetChilds() const { return childs; }

	std::weak_ptr<TransformComponent> const GetChildFromIndex(const uint& index);

	uint GetChildCount() const { return static_cast<uint>(childs.size()); }

	void AddChild(std::weak_ptr<TransformComponent> const child);

private:
	//자신의 크 자 이 값
	D3DXVECTOR3 local_scale = D3DXVECTOR3(1, 1, 1);
	D3DXVECTOR3 local_position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 local_rotation = D3DXVECTOR3(0, 0, 0);

	D3DXMATRIX local;	//local = s * r * t
	D3DXMATRIX world;	//local * parent;

	std::weak_ptr<TransformComponent> parent;
	std::vector<std::weak_ptr<TransformComponent>> childs;
};

