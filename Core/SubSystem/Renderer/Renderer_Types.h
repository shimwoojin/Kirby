#pragma once
#include "stdafx.h"

enum class RenderableType : uint
{
	Opaque,
	Camera
};

enum class RasterizerStateType : uint
{
	Cull_Front_Fill_Solid,
	Cull_Back_Fill_Solid,
	Cull_None_Fill_Solid,
	Cull_Front_Fill_Wireframe,
	Cull_Back_Fill_Wireframe,
	Cull_None_Fill_Wireframe
};

enum class BlendStateType : uint
{
	Disabled,
	Alpha
};
