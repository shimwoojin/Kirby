#pragma once
//Windows.h
#include "stdafx.h"


namespace Window
{
    static HINSTANCE global_instance; // 인스턴스 정보 
    static HWND global_handle;        // 핸들의 정보

    // CALLBACK : __stdcall
    inline LRESULT CALLBACK WndProc // inline : 컴파일타임 때 정보를 불러온다. (빠르다, 무겁다)
                            // CALLBACK : 함수 호출 규약이 다르기에 CALLBACK 으로 처리 // 사용자가 호출하는 것이 아니라 프로그램이 알아서 처리(맨 뒤에서 호출해준다)
                            // cdecl : caller -> C // stdcall: callee -> API
                            (
                                HWND handle,
                                UINT message,
                                WPARAM wParam,
                                LPARAM lParam
                            )
    {
        switch (message) // 메세지 내용 switch
        {
        case WM_CLOSE:   // 윈도우가 닫혔을 때
        case WM_DESTROY: // 윈도우가 파괴됐을 때
            PostQuitMessage(0); // WM_QUIT 메시지 발생 -> 종료 
            break;

        default:
            // 위에서 원하는 내용을 처리하고, 남은 것을 처리해주는 기본 값
            return DefWindowProc(handle, message, wParam, lParam);
        }

        return 0;
    }

    // 윈도우 생성
    inline void Create(HINSTANCE hInstance, const UINT& width, const UINT& height)
    {
        // 윈도우를 만들기 위한 설명서 작성
        WNDCLASSEX wnd_class;
        wnd_class.cbClsExtra = 0;
        wnd_class.cbWndExtra = 0;
        wnd_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
        wnd_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wnd_class.hIcon = LoadIcon(nullptr, IDI_INFORMATION);
        wnd_class.hIconSm = LoadIcon(nullptr, IDI_INFORMATION);
        wnd_class.hInstance = hInstance;
        wnd_class.lpfnWndProc = WndProc;
        wnd_class.lpszClassName = L"D2D11Game";
        wnd_class.lpszMenuName = nullptr;
        wnd_class.style = CS_HREDRAW | CS_VREDRAW;
        wnd_class.cbSize = sizeof(WNDCLASSEX);

        // 클래스 등록
        auto check = RegisterClassEx(&wnd_class);
        assert(check != 0); // 등록 확인

        // 윈도우 생성
        global_handle = CreateWindowExW
        (
            WS_EX_APPWINDOW,
            L"D2D11Game",
            L"D2D11Game",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<int>(width),
            static_cast<int>(height),
            nullptr,
            nullptr,
            hInstance,
            nullptr
        );

        global_instance = hInstance;

        // 생성 체크 
        assert(global_handle != nullptr);
    }

    // 윈도우 출력
    inline void Show()
    {
        SetForegroundWindow(global_handle);
        SetFocus(global_handle);
        ShowCursor(TRUE);
        ShowWindow(global_handle, SW_NORMAL);
        UpdateWindow(global_handle);
    }

    // 메시지 루프
    inline const bool Update()
    {
        MSG msg;
        ZeroMemory(&msg, sizeof(MSG));

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // WM_QUIT 메시지를 반환하기 전까지 true 리턴
        return msg.message != WM_QUIT;
    }

    // 윈도우 파괴
    inline void Destroy()
    {
        DestroyWindow(global_handle);
        UnregisterClass(L"D2D11Game", global_instance);
    }

    // 윈도우 가로 구하기
    inline const UINT GetWidth()
    {
        RECT rect;
        GetClientRect(global_handle, &rect);

        return static_cast<UINT>(rect.right - rect.left);
    }

    // 윈도우 세로 구하기
    inline const UINT GetHeight()
    {
        RECT rect;
        GetClientRect(global_handle, &rect);

        return static_cast<UINT>(rect.bottom - rect.top);
    }
}