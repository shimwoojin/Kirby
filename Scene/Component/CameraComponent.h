#pragma once
#include "IComponent.h"

class CameraComponent final : public IComponent
{
public:
	using IComponent::IComponent;
	~CameraComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	const D3DXMATRIX& GetViewMatrix() const { return view; }
	const D3DXMATRIX& GetProjectionMatrix() const { return projection; }

	void SetCameraPosition(D3DXVECTOR3 position);
	void SetScene(class Scene* scene);

	const D3DXVECTOR3& GetStrictedPosition() const { return stricted_position; }

private:
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

private:
	D3DXMATRIX view;
	D3DXMATRIX projection;

	class Scene* scene = nullptr;
	class InputManager* key = nullptr;
	class SceneManager* scene_manager = nullptr;
	
	struct SceneSize camera_position_strict = { 0,0,0,0 };
	D3DXVECTOR3 stricted_position = { 0,0,0 };
};

