//Color.hlsl

struct VertexInput
{
	/*
		POSITION0? -> Semantic
		Semantic
			- 데이터의 출처와 역할에 대한 의미를 부여하기 위한 키워드
			- POSITION0에서 POSITION은 이름, 0은 인덱스
	*/
	float4 position : POSITION0;
	float4 color : COLOR0;
};

struct PixelInput
{
	/*
	   System Value(SV)
		  - 시스템에서 사용할 값이라고 명시한 것
		  - SV_ 접두사를 통해 해당 값이 시스템에서 특별한 의미가 있다고 표현한 것이다.
		  - SV는 랜더링 파이프 라인의 단계에 따라 의미가 다를 수 있다.
		  - 해당 접두사로 시스템이 사용할 값을 지정해주거나, 시스템에서 어떠한 의미를 가진 값을 받을 수 있다.
		  - SV_가 붙는 다양한 키워드가 있고 이건 문서에서 확인
		  링크 : https://docs.microsoft.com/ko-kr/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics?redirectedfrom=MSDN
		  - VS단계에서의 SV_POSITION의 경우는 해당 SV를 가진 데이터를 첨부하여 출력할 경우,
		  해당 값은 RS단계에서 레스터 이미지화를 할 때 사용할, VS단계에서 최종 변환과정을 거쳐서
		  나온 정점이라는 의미를 시스템에게 전달할 수 있다.
		  - PS단계에서의 SV_POSITION의 경우는 VS단계에서 넘긴 SV_POSTION의 값을 PS 단계가 오기 전인
		  RS단계를 거치면서 완성된 래스터 이미지의 픽셀 좌표들을 받겠다는 의미이다.

		  ㅁ 래스터 이미지 : 픽셀로 이미지를 표현하는 자료구조, 비트맵이라고도 부른다.
	*/
	float4 position : SV_POSITION0;
	float4 color : COLOR0;
};

/*
	cbuffer : Constant Buffer의 약자
	register : 셰이더에 데이터를 연결시켜줌
	b : buffer
	0 : slot, 저장할 레지스터 슬롯의 번호, 0 ~ 13 범위를 가짐

	상수 버퍼는 16byte 단위로 정렬해야 함
	최대 4096 * 16byte만큼 받을 수 있음
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

//VS단계 : IA에서 받은 정점을 공간변환해주는 단계
PixelInput VS(VertexInput input)
{
	PixelInput output;

	/*
		1 x 4 * 4 x 4 = 1 x 4


	*/

	//받은 포지션 값에 SV_접두사를 붙여줌 -> RS단계에서 사용할 정점을 지정해줌
	//output.position = input.position;

	//행렬 곱을 통해 공간 이동을 시켜줌
	output.position = mul(input.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	output.color = input.color;

	return output;	//반환된 값은 RS단계를 거치게 됨
}

//SV_Target : 현재 세팅된 메인 렌더 타겟을 사용하라
float4 PS(PixelInput input) : SV_Target
{
	return input.color;
}