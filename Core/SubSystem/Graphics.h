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
    ID3D11Device* device = nullptr;            // DX���� ����� �ڿ� ����
    ID3D11DeviceContext* device_context = nullptr;      // ������ ���ο� ������ �� ���
    IDXGISwapChain* swap_chain = nullptr;         // ���� ���۸�, ����� ����
    ID3D11RenderTargetView* render_target_view = nullptr;   // ��ȭ��
    D3D11_Viewport         viewport;            // �׷��� ����
    D3DXCOLOR            clear_color = 0xff555566;
};

/*
   I�� ������ Com interface : ���� �޸𸮿� �Ҵ� �� �� ����. �Ҵ��� ��û�ϱ� ������ Desc(����)�� �ʿ��ϴ�,
   new�� delete�� ������� ���ϰ� �Լ��� ���� ��û�Ѵ�,

   DXGI : DX �׷��� �Ϻα���
    - �׷��� ī�尡 ������ ���� �ٸ��� ������ ���α׷��Ӱ� ���� ����� �� �ֵ��� ���ִ� ��

   SwapChain : ������۸��� ����ϸ� ����۸� �������ش�.

   Render TargetView : ��ȭ��, ������ ����� �Ǵ� ����

   VIEWPORT : ����ȭ�鿡�� �׸��� �׷��� ������ �����Ѵ�,

   COLOR : RGBA(����, ����), 0 ~ 255�� ������ 0 ~ 1�� ����ȭ�Ͽ� �����Ѵ�.
*/

// Rendering Pipeline : �������� �ϱ� ���� ���� �ܰ� 
// IA(Input Assembler) - VS(Vertex Shader) - RS(Rasterizer) - PS(Pixel Shader) - OM(output Merger) 


// DirectX : GPU�� �ٷ�� API, SDK 

/*
   CPU : ���л� 8 -> ��� �۾�
   GPU : �ʵ��л� 4000 -> ������ �۾��� ó���� �� ����(������)
*/

/*
    Vertex Shader Stage(VS) - ������ �����ϴ� �ܰ�
        - Shader : GPU�� ���۽�Ű�� �Լ����� ����, ���
        - HLSL : High Level Shader Language, DX���� ����ϴ� ���̴� ���
        - VS�ܰ迡�� �������� ���� ��ȯ(Transform)�� ����
        - IA, RS, OM �ܰ迡���� �ڵ��� �Ұ����� ���� ���ø� ���� �� ������
        VS, PS �ܰ�� ���̴��� �ڵ��� ����
*/