#include "stdafx.h"
#include "Renderer.h"
#include "Scene/Scenes/Scene.h"
#include "Scene/Actors/Actor.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/MaterialRendererComponent.h"
#include "Scene/Component/StateComponent.h"

void Renderer::PassMain()
{
	std::vector<Actor*>& actors = renderables[RenderableType::Opaque];

	if (actors.empty() == true) return;

	for (const auto& actor : actors)
	{
		auto renderable = actor->GetComponent<MeshRendererComponent>();
		if (renderable == nullptr) continue;

		auto transform = actor->GetTransform_Raw();
		if (transform == nullptr) continue;

		auto animator = actor->GetComponent<AnimatorComponent>();
		auto material_renderer = actor->GetComponent<MaterialRendererComponent>();

		D3D11_PipelineState pipeline_state;
		pipeline_state.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		pipeline_state.rasterizer_state = rasterizers[RasterizerStateType::Cull_Back_Fill_Solid].get();
		pipeline_state.blend_state = blend_states[BlendStateType::Alpha].get();

		if (animator != nullptr)
		{
			pipeline_state.vertex_shader = animator->GetVertexShader().get();
			pipeline_state.pixel_shader = animator->GetPixelShader().get();
			pipeline_state.input_layout = animator->GetInputLayout().get();
		}
		else if (material_renderer != nullptr)
		{
			pipeline_state.vertex_shader = material_renderer->GetVertexShader().get();
			pipeline_state.pixel_shader = material_renderer->GetPixelShader().get();
			pipeline_state.input_layout = material_renderer->GetInputLayout().get();
		}
		else return;

		if (pipeline->Begin(pipeline_state))
		{
			pipeline->SetVertexBuffer(renderable->GetVertexBuffer().get());
			pipeline->SetIndexBuffer(renderable->GetIndexBuffer().get());

			D3DXMatrixTranspose(&cpu_object_buffer.world, &transform->GetWorldMatrix());
			UpdateObjectBuffer();

			pipeline->SetConstantBuffer(0, ShaderScope_VS, gpu_camera_buffer.get());
			pipeline->SetConstantBuffer(1, ShaderScope_VS, gpu_object_buffer.get());

			if (animator != nullptr)
			{
				auto current_keyframe = animator->GetCurrentKeyframe();
				cpu_animation_buffer.sprite_offset = current_keyframe->offset;
				cpu_animation_buffer.sprite_size = current_keyframe->size;
				cpu_animation_buffer.texture_size = animator->GetCurrentAnimation()->GetSpriteTextureSize();
				cpu_animation_buffer.is_animated = 1.0f;
				cpu_animation_buffer.is_mirrored = 0.0f;
				if (auto state = actor->GetComponent<StateComponent>())
					cpu_animation_buffer.is_mirrored = static_cast<float>(state.get()->GetIsMirroredAnimation());
				UpdateAnimationBuffer();

				pipeline->SetConstantBuffer(2, ShaderScope_VS | ShaderScope_PS, gpu_animation_buffer.get());
				pipeline->SetShaderResource(0, ShaderScope_PS, animator->GetCurrentAnimation()->GetSpriteTexture().get());
			}
			else if(material_renderer != nullptr)
			{
				pipeline->SetShaderResource(0, ShaderScope_PS, material_renderer->GetTexture2D().lock()->GetSpriteTexture().get());
			}

			pipeline->DrawIndexed
			(
				renderable->GetIndexBuffer()->GetCount(),
				renderable->GetIndexBuffer()->GetOffset(),
				renderable->GetVertexBuffer()->GetOffset()
			);
		}
	}
}
