#include "stdafx.h"
#include "Renderer.h"

void Renderer::CreateConstantbuffers()
{
	gpu_camera_buffer = std::make_shared<D3D11_ConstantBuffer>(graphics);
	gpu_camera_buffer->Create<CAMERA_DATA>();

	gpu_object_buffer = std::make_shared<D3D11_ConstantBuffer>(graphics);
	gpu_object_buffer->Create<TRANSFORM_DATA>();

	gpu_animation_buffer = std::make_shared<D3D11_ConstantBuffer>(graphics);
	gpu_animation_buffer->Create<ANIMATION_DATA>();
}

void Renderer::CreateRasterizerStates()
{
	rasterizers[RasterizerStateType::Cull_Front_Fill_Solid] = std::make_shared<D3D11_RasterizerState>(graphics);
	rasterizers[RasterizerStateType::Cull_Front_Fill_Solid]->Create(D3D11_CULL_FRONT, D3D11_FILL_SOLID);

	rasterizers[RasterizerStateType::Cull_Back_Fill_Solid] = std::make_shared<D3D11_RasterizerState>(graphics);
	rasterizers[RasterizerStateType::Cull_Back_Fill_Solid]->Create(D3D11_CULL_BACK, D3D11_FILL_SOLID);

	rasterizers[RasterizerStateType::Cull_None_Fill_Solid] = std::make_shared<D3D11_RasterizerState>(graphics);
	rasterizers[RasterizerStateType::Cull_None_Fill_Solid]->Create(D3D11_CULL_NONE, D3D11_FILL_SOLID);

	rasterizers[RasterizerStateType::Cull_Front_Fill_Wireframe] = std::make_shared<D3D11_RasterizerState>(graphics);
	rasterizers[RasterizerStateType::Cull_Front_Fill_Wireframe]->Create(D3D11_CULL_FRONT, D3D11_FILL_WIREFRAME);

	rasterizers[RasterizerStateType::Cull_Back_Fill_Wireframe] = std::make_shared<D3D11_RasterizerState>(graphics);
	rasterizers[RasterizerStateType::Cull_Back_Fill_Wireframe]->Create(D3D11_CULL_BACK, D3D11_FILL_WIREFRAME);

	rasterizers[RasterizerStateType::Cull_None_Fill_Wireframe] = std::make_shared<D3D11_RasterizerState>(graphics);
	rasterizers[RasterizerStateType::Cull_None_Fill_Wireframe]->Create(D3D11_CULL_NONE, D3D11_FILL_WIREFRAME);
}

void Renderer::CreateBlendStates()
{
	blend_states[BlendStateType::Disabled] = std::make_shared<D3D11_BlendState>(graphics);
	blend_states[BlendStateType::Disabled]->Create(false);

	blend_states[BlendStateType::Alpha] = std::make_shared<D3D11_BlendState>(graphics);
	blend_states[BlendStateType::Alpha]->Create(true);
}
