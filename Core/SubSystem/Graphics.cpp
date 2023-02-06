#include "stdafx.h"
#include "Graphics.h"

Graphics::~Graphics()
{
    SAFE_RELEASE(render_target_view);
    SAFE_RELEASE(device);
    SAFE_RELEASE(device_context);
    SAFE_RELEASE(swap_chain);
}

bool Graphics::Initialize()
{
        // ����̽�, ����̽� ���ؽ�Ʈ, ����ü�� ����
        {
            // DXGI_SWAP_CHAIN_DESC : ���� ü���� ����� ���� ����
            DXGI_SWAP_CHAIN_DESC desc;
            ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

            // ����ü���� ������ ������ ũ��
            desc.BufferDesc.Width = 0;   // �ʺ�
            desc.BufferDesc.Height = 0;   // ����

            /*
               RefreshRate : ȭ�� �ֻ���, ȭ���� ����ֱ�� ������ ���ΰ�?
               Numerator : ����
               Denominator : �и�

               60/1 => �ʴ� 60�� ȭ���� �����Ѵ�.
            */
            desc.BufferDesc.RefreshRate.Numerator = 60;
            desc.BufferDesc.RefreshRate.Denominator = 1;

            /*
               RGBA : ���� ä���� �ǹ��Ѵ�. ������ ���� �����͸� ���� �ʿ�� ����.
               R8B8B8A8 : BPC, Color Depth��� �θ��� ������ ä���� 8��Ʈ�̴� �� ä�δ� 0~ 255 �� ������ ������.

               UNORM(Unsigned Normalize) : 0 ~ 1�� ����ȭ�� �����ͷ� ���ڴ�.
                - �� ä���� 8��Ʈ�� ��� 0 ~ 255�� ������ 0 ~ 1�� ����ȭ�Ͽ� ����Ѵٴ� ��

               DXGI_FORMAT_R8G8B8A8_UNORM : 4����Ʈũ�� (�� ä�δ� 8��Ʈ*4)�� ������ ����ȭ�� �����͸� ��ڴ�.
            */
            // ���۰� � ������ �����͸� ���� ���ΰ�?
            desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

            // ȭ���� ����� �� ��� ������� �� ���ΰ�?
            // Scanline : ȭ���� ����� �� ���پ� �׾ ����ϴ°�
            // UNSPECIFIED : �������� ����
            desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

            // ȭ���� ���/Ȯ���� �� � ȿ���� �ٰ��ΰ�?
            desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

            desc.BufferCount = 1; // ������ ����
            desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ������ �뵵

            /*
               Aliasing : �ȼ� ǥ������ ���� �ܰ����� ���ó�� ���̴� ����

               Anti Aliasing(AA) : ��������� �����ϴ� ���
                + Super Sampling AA (SSAA)
                  �� ���ø� �����ŭ �ػ󵵸� Ȯ���� �Ŀ� Down Sampling(�ػ󵵸� �ٿ� ���� ���´�.)�� �ϴ� ���
                  �� ���� ���귮�� �޸𸮰� �ʿ��ϴ�.
                + Multi Samplong AA (MSAA)
                  �� ���� ���귮�� �޷θ��� �䱸�ϴ� SSAA�� �跮�ؼ� ���� ���
                  �� ������(�̹��� ���)�� �����ڸ��� AA�� �����Ѵ�.
            */
            desc.SampleDesc.Count = 1; // ������ ����, ���
            desc.SampleDesc.Quality = 0; // ���ø��� ����Ƽ ����, 0�� �Ⱦ��ڴٴ� �ǹ�

            // ����� ������ �ڵ�
            desc.OutputWindow = Settings::Get().GetWindowhandle(); // ����� ������ �ڵ�
            desc.Windowed = TRUE; // â��� ����

            // ���ҽ� � ȿ���� �� ���ΰ�?
            // DISCARD : �����Ͽ� ���� �����͸� ����ϰڴ�.
            desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

            // FEATURE_LEVEL : ��� ����, DX �� ������ �� ���ΰ�?
            std::vector<D3D_FEATURE_LEVEL> feature_levels
            {
               D3D_FEATURE_LEVEL_11_1,
               D3D_FEATURE_LEVEL_11_0,
               D3D_FEATURE_LEVEL_10_1,
               D3D_FEATURE_LEVEL_10_0,
            };
            //HRESULT : �Լ� ����� �������θ� ��� �ڷ���
            //S_OK(����), S_FALSE(����)�� ����
            HRESULT hr = D3D11CreateDeviceAndSwapChain
            (
                nullptr,                    //���� ī�带 �����ؼ� ����� �� ��
                D3D_DRIVER_TYPE_HARDWARE,   //����̽� Ÿ��
                nullptr,                    //�ٸ� ����Ʈ��� �߰������� �������ΰ�?
                0,                          //����̽��� ���� �� � ����� �߰������� �������ΰ�?
                feature_levels.data(),      //��ó ���� �迭�� ���� �ּ�
                feature_levels.size(),      //��ó ���� ī��Ʈ
                D3D11_SDK_VERSION,          //����ϴ� SDK ����
                &desc,                      //����ü���� ���� �� ����� desc �ּ�
                &swap_chain,                //������ ����ü���� �Ҵ���� ������ ������ �ּ�
                &device,                    //������ ����̽��� �Ҵ���� ������ ������ �ּ�
                nullptr,                    //���õ� ��ó������ ��ȯ���� ������ �ּ�
                &device_context             //������ ����̽� ���ؽ�Ʈ�� �Ҵ���� ������ ������ �ּ�
            );
            assert(SUCCEEDED(hr));          //SUCCEEDED() : ������ true, ���� �� false�� ��ȯ���ִ� ��ũ��
        }

        return true;
}

void Graphics::CreateBackBuffer(const uint& width, const uint& height)
{
    //RTV ����

    //ResizeBuffers : ���� ü���� ������ ���� ������ �����ϴ� �Լ�
    //������ ���� �־��ְ� �������� ���� ���� �ʱⰪ�� ������ ������ ���� ����
    HRESULT hr = swap_chain->ResizeBuffers
    (
        0,
        width,
        height,
        DXGI_FORMAT_UNKNOWN,
        0
    );
    assert(SUCCEEDED(hr));

    /*
        Interface Identifier(IID)
            - �������̽��� �����ϱ� ���� �ĺ���
            - GUID�� �� �� �ϳ�

        Globally Unique Identifier(GUID)
            - MS���� ����ϴ� ���� �׸��� �����ϱ� ���� �ĺ���
            - 16����Ʈ�� ũ�⸦ ����
            - UUID��� �ִµ� ū ���̴� ����

        ���� : GUID, UUID ����
    */

    ID3D11Texture2D* back_buffer = nullptr;

    hr = swap_chain->GetBuffer
    (
        0,                                      //�� ��° ���۸� �������ΰ�
        __uuidof(ID3D11Texture2D),              //�� ���۸� ���� �������̽� Ÿ��
        reinterpret_cast<void**>(&back_buffer)  //��ȯ�� �������̽��� ���� ���� ����
    );
    assert(SUCCEEDED(hr));

    hr = device->CreateRenderTargetView
    (
        back_buffer,        //�信�� ������ ���ҽ�
        nullptr,            //RTV�� desc, nullptr�� ��� ���ҽ��� ������ ����
        &render_target_view //RTV�� �޾ƿ� ����
    );
    assert(SUCCEEDED(hr));

    //����Ʈ ����
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(width);
    viewport.height = static_cast<float>(height);
    viewport.min_depth = 0.0f;
    viewport.max_depth = 1.0f;

    //����
    SAFE_RELEASE(back_buffer);

}

void Graphics::Begin()
{
    /*
        Output Merger Stage(OM) - ��� ���� �ܰ�
        - �׸��� �׸� ���� Ÿ���� �����ϰ�, ���� ��� ���� ���ΰ�(����)�� ��������
        - OM�� ���õ� �� �ִ� ���� Ÿ���� ������ 8���� -> 8���� ���ÿ� �׸� �� ����
    */
    device_context->OMSetRenderTargets(1, &render_target_view, nullptr);    //�׸��� �׸� ����Ÿ���� ����

    D3D11_VIEWPORT d3d11_viewport;

    d3d11_viewport.TopLeftX = viewport.x;
    d3d11_viewport.TopLeftY = viewport.y;
    d3d11_viewport.Width = viewport.width;
    d3d11_viewport.Height = viewport.height;
    d3d11_viewport.MinDepth = viewport.min_depth;
    d3d11_viewport.MaxDepth = viewport.max_depth;

    device_context->RSSetViewports(1, &d3d11_viewport);   //�׸� ���� ����
    device_context->ClearRenderTargetView(render_target_view, clear_color); //���� Ÿ�� �ʱ�ȭ
}

void Graphics::End()
{
    HRESULT hr = swap_chain->Present(1, 0);
    assert(SUCCEEDED(hr));
}

void Graphics::Update()
{
    return;
}
