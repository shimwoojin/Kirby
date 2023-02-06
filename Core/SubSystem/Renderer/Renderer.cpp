#include "stdafx.h"
#include "Renderer.h"
#include "Scene/Actors/Actor.h"
#include "Scene/Scenes/Scene.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/MeshRendererComponent.h"

Renderer::~Renderer()
{
}

bool Renderer::Initialize()
{
	graphics = context->GetSubSystem<Graphics>();
	graphics->CreateBackBuffer(
		static_cast<uint>(Settings::Get().GetWidth()),
		static_cast<uint>(Settings::Get().GetHeight())
		);

	pipeline = std::make_shared<D3D11_Pipeline>(graphics);

	CreateConstantbuffers();
	CreateRasterizerStates();
	CreateBlendStates();

	return true;
}

void Renderer::Update()
{
	if (camera == nullptr) return;

	D3DXMatrixTranspose(&cpu_camera_buffer.view, &camera->GetViewMatrix());
	D3DXMatrixTranspose(&cpu_camera_buffer.projection, &camera->GetProjectionMatrix());
	UpdateCameraBuffer();

	graphics->Begin();
	PassMain();
	graphics->End();
}

void Renderer::UpdateRenderables(Scene* const scene)
{
	renderables[RenderableType::Camera].clear();
	renderables[RenderableType::Opaque].clear();

	auto actors = scene->GetActors();

	if (actors.empty() == true) return;

	for (const auto& actor : actors)
	{
		auto camera_component = actor->GetComponent<CameraComponent>();
		auto mesh_renderer_component = actor->GetComponent<MeshRendererComponent>();

		if (camera_component != nullptr)
		{
			renderables[RenderableType::Camera].emplace_back(actor.get());
			camera = camera_component.get();
		}

		if (mesh_renderer_component != nullptr)
		{
			renderables[RenderableType::Opaque].emplace_back(actor.get());
		}


	}
}

void Renderer::UpdateCameraBuffer()
{
	auto buffer = gpu_camera_buffer->Map<CAMERA_DATA>();
	*buffer = cpu_camera_buffer;
	gpu_camera_buffer->Unmap();
}

void Renderer::UpdateObjectBuffer()
{
	auto buffer = gpu_object_buffer->Map<TRANSFORM_DATA>();
	*buffer = cpu_object_buffer;
	gpu_object_buffer->Unmap();
}

void Renderer::UpdateAnimationBuffer()
{
	auto buffer = gpu_animation_buffer->Map<ANIMATION_DATA>();
	*buffer = cpu_animation_buffer;
	gpu_animation_buffer->Unmap();
}
