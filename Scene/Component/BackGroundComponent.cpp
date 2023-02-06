#include "stdafx.h"
#include "BackGroundComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"

void BackGroundComponent::Initialize()
{
}

void BackGroundComponent::Update()
{
	if (camera != nullptr)
	{
		auto camera_transform = camera->GetStrictedPosition();
		transform->SetPosition(camera_transform);
	}
}

void BackGroundComponent::Destroy()
{
}

void BackGroundComponent::SetCamera(class CameraComponent* camera)
{
	if (camera == nullptr)
	{
		assert(false);
		return;
	}

	this->camera = camera;
}
