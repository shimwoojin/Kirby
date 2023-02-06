#pragma once
#include "stdafx.h"

struct CAMERA_DATA
{
	D3DXMATRIX view;
	D3DXMATRIX projection;
};

struct TRANSFORM_DATA
{
	D3DXMATRIX world;
};

struct ANIMATION_DATA
{
	D3DXVECTOR2 sprite_offset;
	D3DXVECTOR2 sprite_size;
	D3DXVECTOR2 texture_size;
	float is_animated;
	float is_mirrored;
};