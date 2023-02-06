//Color.hlsl

struct VertexInput
{
	/*
		POSITION0? -> Semantic
		Semantic
			- �������� ��ó�� ���ҿ� ���� �ǹ̸� �ο��ϱ� ���� Ű����
			- POSITION0���� POSITION�� �̸�, 0�� �ε���
	*/
	float4 position : POSITION0;
	float4 color : COLOR0;
};

struct PixelInput
{
	/*
	   System Value(SV)
		  - �ý��ۿ��� ����� ���̶�� ����� ��
		  - SV_ ���λ縦 ���� �ش� ���� �ý��ۿ��� Ư���� �ǹ̰� �ִٰ� ǥ���� ���̴�.
		  - SV�� ������ ������ ������ �ܰ迡 ���� �ǹ̰� �ٸ� �� �ִ�.
		  - �ش� ���λ�� �ý����� ����� ���� �������ְų�, �ý��ۿ��� ��� �ǹ̸� ���� ���� ���� �� �ִ�.
		  - SV_�� �ٴ� �پ��� Ű���尡 �ְ� �̰� �������� Ȯ��
		  ��ũ : https://docs.microsoft.com/ko-kr/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics?redirectedfrom=MSDN
		  - VS�ܰ迡���� SV_POSITION�� ���� �ش� SV�� ���� �����͸� ÷���Ͽ� ����� ���,
		  �ش� ���� RS�ܰ迡�� ������ �̹���ȭ�� �� �� �����, VS�ܰ迡�� ���� ��ȯ������ ���ļ�
		  ���� �����̶�� �ǹ̸� �ý��ۿ��� ������ �� �ִ�.
		  - PS�ܰ迡���� SV_POSITION�� ���� VS�ܰ迡�� �ѱ� SV_POSTION�� ���� PS �ܰ谡 ���� ����
		  RS�ܰ踦 ��ġ�鼭 �ϼ��� ������ �̹����� �ȼ� ��ǥ���� �ްڴٴ� �ǹ��̴�.

		  �� ������ �̹��� : �ȼ��� �̹����� ǥ���ϴ� �ڷᱸ��, ��Ʈ���̶�� �θ���.
	*/
	float4 position : SV_POSITION0;
	float4 color : COLOR0;
};

/*
	cbuffer : Constant Buffer�� ����
	register : ���̴��� �����͸� ���������
	b : buffer
	0 : slot, ������ �������� ������ ��ȣ, 0 ~ 13 ������ ����

	��� ���۴� 16byte ������ �����ؾ� ��
	�ִ� 4096 * 16byte��ŭ ���� �� ����
*/

cbuffer CameraBuffer : register(b0)
{
	matrix view;
	matrix projection;
}

cbuffer TransformBuffer : register(b1)
{
	matrix world;
}

cbuffer ColorBuffer : register(b2)
{
	float4 color;
}

//VS�ܰ� : IA���� ���� ������ ������ȯ���ִ� �ܰ�
PixelInput VS(VertexInput input)
{
	PixelInput output;

	/*
		1 x 4 * 4 x 4 = 1 x 4


	*/

	//���� ������ ���� SV_���λ縦 �ٿ��� -> RS�ܰ迡�� ����� ������ ��������
	//output.position = input.position;

	//��� ���� ���� ���� �̵��� ������
	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	output.color = input.color;

	return output;	//��ȯ�� ���� RS�ܰ踦 ��ġ�� ��
}

//SV_Target : ���� ���õ� ���� ���� Ÿ���� ����϶�
float4 PS(PixelInput input) : SV_Target
{
	return input.color;
}