#pragma once
#include "IComponent.h"

class BackGroundComponent final : public IComponent
{
public:
	using IComponent::IComponent;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void SetCamera(class CameraComponent* camera);

private:
	class CameraComponent* camera = nullptr;
};

