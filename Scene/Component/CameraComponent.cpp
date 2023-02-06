#include "stdafx.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Scene/Scenes/Scene.h"
#include "Scene/Actors/Actor.h"

void CameraComponent::Initialize()
{
	key = context->GetSubSystem<InputManager>();
	scene_manager = context->GetSubSystem<SceneManager>();

	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	UpdateViewMatrix();
	UpdateProjectionMatrix();
}


void CameraComponent::Update()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();

	if (key->IsHoldOrDown(DIK_W))
	{
		auto actors = scene->GetActors();
		for (const auto& actor : actors)
		{
			auto type = actor.get()->GetActorType();
			if (type == ActorType::Door)
			{
				if (Collide::IsCollided(scene->GetPlayer().get(), actor.get()) == true)
				{
					scene_manager->SetCurrentScene("1-2");
				}
			}
		}
	}
}

void CameraComponent::Destroy()
{
}

void CameraComponent::SetCameraPosition(D3DXVECTOR3 position)
{
	transform->SetPosition(position);
}

void CameraComponent::SetScene(Scene* scene)
{
	this->scene = scene;
	SceneSize scene_size = scene->GetSceneSize();

	camera_position_strict.min_x = scene_size.min_x + static_cast<uint>(Settings::Get().GetWidth() / 2);
	camera_position_strict.max_x = scene_size.max_x - static_cast<uint>(Settings::Get().GetWidth() / 2);
	camera_position_strict.min_y = scene_size.min_y + static_cast<uint>(Settings::Get().GetHeight() / 2);
	camera_position_strict.max_y = scene_size.max_y - static_cast<uint>(Settings::Get().GetHeight() / 2);
}

void CameraComponent::UpdateViewMatrix()
{
	stricted_position = transform->GetPosition();

	if (stricted_position.x < camera_position_strict.min_x) stricted_position.x = camera_position_strict.min_x;
	if (stricted_position.x > camera_position_strict.max_x) stricted_position.x = camera_position_strict.max_x;
	if (stricted_position.y < camera_position_strict.min_y) stricted_position.y = camera_position_strict.min_y;
	if (stricted_position.y > camera_position_strict.max_y)stricted_position.y = camera_position_strict.max_y;

	D3DXVECTOR3 at = stricted_position + transform->GetForward();
	D3DXVECTOR3 up = transform->GetUp();

	D3DXMatrixLookAtLH(&view, &stricted_position, &at, &up);
}

void CameraComponent::UpdateProjectionMatrix()
{
	D3DXMatrixOrthoLH(&projection, Settings::Get().GetWidth(), Settings::Get().GetHeight(), 0.0f, 1.0f);
}
