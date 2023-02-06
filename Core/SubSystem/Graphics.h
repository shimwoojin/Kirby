#pragma once
#include "Core/D3D11/Rasterizer/D3D11_Viewport.h"
#include "ISubSystem.h"

class Graphics final : public ISubSystem
{
public:
    using ISubSystem::ISubSystem;
    ~Graphics();

    virtual bool Initialize() override;
    virtual void Update() override;

    void CreateBackBuffer(const uint& width, const uint& height);

    ID3D11Device* GetDevice() { return device; }
    ID3D11DeviceContext* GetDeviceContext() { return device_context; }

    void Begin();
    void End();

private:
    ID3D11Device* device = nullptr;            // DX에서 사용할 자원 생성
    ID3D11DeviceContext* device_context = nullptr;      // 파이프 라인에 연결할 때 사용
    IDXGISwapChain* swap_chain = nullptr;         // 더블 버퍼링, 백버퍼 관리
    ID3D11RenderTargetView* render_target_view = nullptr;   // 도화지
    D3D11_Viewport         viewport;            // 그려질 영역
    D3DXCOLOR            clear_color = 0xff555566;
};

/*
   I가 붙으면 Com interface : 직접 메모리에 할당 할 수 없다. 할당을 요청하기 때문에 Desc(설명서)가 필요하다,
   new나 delete를 사용하지 못하고 함수를 통해 요청한다,

   DXGI : DX 그래픽 하부구조
    - 그래픽 카드가 제조사 마다 다르기 떄문에 프로그래머가 쉽게 사용할 수 있도록 해주는 것

   SwapChain : 더블버퍼링에 사용하며 백버퍼를 관리해준다.

   Render TargetView : 도화지, 렌더링 대상이 되는 버퍼

   VIEWPORT : 게임화면에서 그림이 그려질 영역을 지정한다,

   COLOR : RGBA(투명도, 선명도), 0 ~ 255의 범위를 0 ~ 1로 정규화하여 관리한다.
*/

// Rendering Pipeline : 렌더링을 하기 위한 수행 단계 
// IA(Input Assembler) - VS(Vertex Shader) - RS(Rasterizer) - PS(Pixel Shader) - OM(output Merger) 


// DirectX : GPU를 다루는 API, SDK 

/*
   CPU : 대학생 8 -> 고급 작업
   GPU : 초등학생 4000 -> 간단한 작업을 처리할 때 유리(렌더링)
*/

/*
    Vertex Shader Stage(VS) - 정점을 가공하는 단계
        - Shader : GPU를 동작시키는 함수들의 집합, 언어
        - HLSL : High Level Shader Language, DX에서 사용하는 쉐이더 언어
        - VS단계에서 정점들의 공간 변환(Transform)을 해줌
        - IA, RS, OM 단계에서는 코딩이 불가능해 값을 세팅만 해줄 수 있지만
        VS, PS 단계는 쉐이더로 코딩이 가능
*/