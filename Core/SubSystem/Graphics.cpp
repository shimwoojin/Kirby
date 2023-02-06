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
        // 디바이스, 디바이스 컨텍스트, 스왑체인 생성
        {
            // DXGI_SWAP_CHAIN_DESC : 스왑 체인을 만들기 위한 설명서
            DXGI_SWAP_CHAIN_DESC desc;
            ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

            // 스왑체인이 관리할 버퍼의 크기
            desc.BufferDesc.Width = 0;   // 너비
            desc.BufferDesc.Height = 0;   // 높이

            /*
               RefreshRate : 화면 주사율, 화면을 어느주기로 갱신할 것인가?
               Numerator : 분자
               Denominator : 분모

               60/1 => 초당 60번 화면을 갱신한다.
            */
            desc.BufferDesc.RefreshRate.Numerator = 60;
            desc.BufferDesc.RefreshRate.Denominator = 1;

            /*
               RGBA : 색상 채널을 의미한다. 무조건 색상 데이터를 담을 필요는 없다.
               R8B8B8A8 : BPC, Color Depth라고 부르며 각각의 채널이 8비트이니 각 채널당 0~ 255 의 범위를 가진다.

               UNORM(Unsigned Normalize) : 0 ~ 1의 정규화된 데이터로 쓰겠다.
                - 각 채널이 8비트일 경우 0 ~ 255의 범위를 0 ~ 1로 정규화하여 사용한다는 뜻

               DXGI_FORMAT_R8G8B8A8_UNORM : 4바이트크기 (각 채널당 8비트*4)를 가지는 정규화된 데이터를 담겠다.
            */
            // 버퍼가 어떤 형식의 데이터를 담을 것인가?
            desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

            // 화면을 출력할 때 어떠한 방식으로 할 것인가?
            // Scanline : 화면을 출력할 떄 한줄씩 그어서 출력하는것
            // UNSPECIFIED : 지정하지 않음
            desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

            // 화면을 축소/확대할 때 어떤 효과를 줄것인가?
            desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

            desc.BufferCount = 1; // 버퍼의 갯수
            desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 버퍼의 용도

            /*
               Aliasing : 픽셀 표현으로 인해 외곽선이 계단처럼 보이는 현상

               Anti Aliasing(AA) : 계단형상을 제거하는 방법
                + Super Sampling AA (SSAA)
                  ㄴ 샘플링 배수만큼 해상도를 확대한 후에 Down Sampling(해상도를 줄여 색을 섞는다.)을 하는 방식
                  ㄴ 많은 연산량과 메모리가 필요하다.
                + Multi Samplong AA (MSAA)
                  ㄴ 많은 연산량과 메로리를 요구하는 SSAA를 계량해서 만든 방법
                  ㄴ 폴리곤(이미지 덩어리)의 가장자리만 AA를 진행한다.
            */
            desc.SampleDesc.Count = 1; // 샘플의 갯수, 배수
            desc.SampleDesc.Quality = 0; // 샘플링의 퀄리티 수준, 0은 안쓰겠다는 의미

            // 출력할 윈도우 핸들
            desc.OutputWindow = Settings::Get().GetWindowhandle(); // 출력할 윈도우 핸들
            desc.Windowed = TRUE; // 창모드 여부

            // 스왑시 어떤 효과를 줄 것인가?
            // DISCARD : 스왑하여 나온 데이터를 폐기하겠다.
            desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

            // FEATURE_LEVEL : 기능 수준, DX 몇 버전을 쓸 것인가?
            std::vector<D3D_FEATURE_LEVEL> feature_levels
            {
               D3D_FEATURE_LEVEL_11_1,
               D3D_FEATURE_LEVEL_11_0,
               D3D_FEATURE_LEVEL_10_1,
               D3D_FEATURE_LEVEL_10_0,
            };
            //HRESULT : 함수 결과의 성공여부를 담는 자료형
            //S_OK(성공), S_FALSE(실패)를 가짐
            HRESULT hr = D3D11CreateDeviceAndSwapChain
            (
                nullptr,                    //비디오 카드를 지정해서 사용할 때 씀
                D3D_DRIVER_TYPE_HARDWARE,   //디바이스 타입
                nullptr,                    //다른 소프트웨어를 추가적으로 넣을것인가?
                0,                          //디바이스를 만들 때 어떤 기능을 추가적으로 넣을것인가?
                feature_levels.data(),      //피처 레벨 배열의 시작 주소
                feature_levels.size(),      //피처 레벨 카운트
                D3D11_SDK_VERSION,          //사용하는 SDK 버전
                &desc,                      //스왑체인을 만들 때 사용할 desc 주소
                &swap_chain,                //생성된 스왑체인을 할당받을 포인터 변수의 주소
                &device,                    //생성된 디바이스를 할당받을 포인터 변수의 주소
                nullptr,                    //선택된 피처레벨을 반환받을 변수의 주소
                &device_context             //생성된 디바이스 컨텍스트를 할당받을 포인터 변수의 주소
            );
            assert(SUCCEEDED(hr));          //SUCCEEDED() : 성공시 true, 실패 시 false를 반환해주는 매크로
        }

        return true;
}

void Graphics::CreateBackBuffer(const uint& width, const uint& height)
{
    //RTV 생성

    //ResizeBuffers : 스왑 체인이 가지는 버퍼 정보를 변경하는 함수
    //변경할 값만 넣어주고 변경하지 않을 값을 초기값을 넣으면 변경이 되지 않음
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
            - 인터페이스를 구분하기 위한 식별자
            - GUID의 값 중 하나

        Globally Unique Identifier(GUID)
            - MS에서 사용하는 여러 항목을 구분하기 위한 식별자
            - 16바이트의 크기를 가짐
            - UUID라고도 있는데 큰 차이는 없음

        과제 : GUID, UUID 조사
    */

    ID3D11Texture2D* back_buffer = nullptr;

    hr = swap_chain->GetBuffer
    (
        0,                                      //몇 번째 버퍼를 꺼낼것인가
        __uuidof(ID3D11Texture2D),              //백 버퍼를 받은 인터페이스 타입
        reinterpret_cast<void**>(&back_buffer)  //반환된 인터페이스를 받을 저장 공간
    );
    assert(SUCCEEDED(hr));

    hr = device->CreateRenderTargetView
    (
        back_buffer,        //뷰에서 접근할 리소스
        nullptr,            //RTV의 desc, nullptr인 경우 리소스의 형식을 따름
        &render_target_view //RTV를 받아올 변수
    );
    assert(SUCCEEDED(hr));

    //뷰포트 세팅
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(width);
    viewport.height = static_cast<float>(height);
    viewport.min_depth = 0.0f;
    viewport.max_depth = 1.0f;

    //해제
    SAFE_RELEASE(back_buffer);

}

void Graphics::Begin()
{
    /*
        Output Merger Stage(OM) - 출력 병합 단계
        - 그림을 그릴 렌더 타겟을 지정하고, 색을 어떻게 섞을 것인가(블렌딩)을 지정해줌
        - OM에 세팅될 수 있는 렌더 타겟의 개수는 8개임 -> 8장을 동시에 그릴 수 있음
    */
    device_context->OMSetRenderTargets(1, &render_target_view, nullptr);    //그림을 그릴 렌더타겟을 지정

    D3D11_VIEWPORT d3d11_viewport;

    d3d11_viewport.TopLeftX = viewport.x;
    d3d11_viewport.TopLeftY = viewport.y;
    d3d11_viewport.Width = viewport.width;
    d3d11_viewport.Height = viewport.height;
    d3d11_viewport.MinDepth = viewport.min_depth;
    d3d11_viewport.MaxDepth = viewport.max_depth;

    device_context->RSSetViewports(1, &d3d11_viewport);   //그릴 영역 선택
    device_context->ClearRenderTargetView(render_target_view, clear_color); //렌더 타겟 초기화
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
