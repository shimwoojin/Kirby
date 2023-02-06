//Texture.hlsl

struct VertexInput
{
	float4 position : POSITION0;
	float2 uv : TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float2 uv : TEXCOORD0;
};

cbuffer CameraBuffer : register(b0)
{
	matrix view;
	matrix projection;
}

cbuffer TransformBuffer : register(b1)
{
	matrix world;
}

PixelInput VS(VertexInput input)
{
	PixelInput output;

	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	output.uv = input.uv;

	return output;
}

Texture2D source_texture1 : register(t0);
//Texture2D source_texture2 : register(t1);
SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
	//float4 color = source_texture.Sample(samp, input.uv);

	//clip() : 인자로 받은 데이터가 0보다 작다면 해당 픽셀을 폐기
	//clip(color.a - 0.9f);

	//if (color.a < 0.1f)
	//	discard;	////호출되는 순간 픽셀을 폐기시키는 키워드
	//if (color.g < 0.5f)
	//	discard;

	//if (input.uv.x < 1.0f)
	//	color = source_texture1.Sample(samp, input.uv);
	//else
	//	color = source_texture2.Sample(samp, float2(input.uv.x - 1.0f, input.uv.y));
	float4 color = source_texture1.Sample(samp, input.uv);

	return color;
}