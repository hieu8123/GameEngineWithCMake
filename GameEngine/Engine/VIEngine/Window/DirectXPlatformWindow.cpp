#include "Window.h"

#include "pch.h"
#include "Core/Logger/Logger.h"

namespace VIEngine {
#ifdef _WIN32

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

static LRESULT CALLBACK DXWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

DirectXPlatformWindow::DirectXPlatformWindow()
        : mHwnd(nullptr), mDevice(nullptr), mContext(nullptr),
          mSwapChain(nullptr), mRenderTarget(nullptr), mShouldClose(false) {}

DirectXPlatformWindow::~DirectXPlatformWindow() {
        Shutdown();
}

bool DirectXPlatformWindow::Init(const ApplicationConfiguration& config) {
        HINSTANCE instance = GetModuleHandle(nullptr);

        WNDCLASS wc{};
        wc.lpfnWndProc = DXWindowProc;
        wc.hInstance = instance;
        wc.lpszClassName = L"VIEngineWindow";
        if (!RegisterClass(&wc)) {
                CORE_LOG_CRITICAL("Failed to register window class");
                return false;
        }

        RECT rect{ 0,0,config.Width,config.Height };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
        mHwnd = CreateWindow(wc.lpszClassName, L"VIEngine", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT,
                rect.right - rect.left, rect.bottom - rect.top,
                nullptr, nullptr, instance, nullptr);
        if (!mHwnd) {
                CORE_LOG_CRITICAL("Failed to create window");
                return false;
        }
        SetWindowLongPtr(mHwnd, GWLP_USERDATA, (LONG_PTR)this);
        ShowWindow(mHwnd, SW_SHOW);

        DXGI_SWAP_CHAIN_DESC swapDesc{};
        swapDesc.BufferCount = 1;
        swapDesc.BufferDesc.Width = config.Width;
        swapDesc.BufferDesc.Height = config.Height;
        swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapDesc.OutputWindow = mHwnd;
        swapDesc.SampleDesc.Count = 1;
        swapDesc.Windowed = TRUE;

        HRESULT hr = D3D11CreateDeviceAndSwapChain(
                nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
                D3D11_SDK_VERSION, &swapDesc, &mSwapChain,
                &mDevice, nullptr, &mContext);
        if (FAILED(hr)) {
                CORE_LOG_CRITICAL("Failed to create D3D device");
                return false;
        }

        ID3D11Texture2D* backBuffer = nullptr;
        hr = mSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
        if (FAILED(hr)) {
                CORE_LOG_CRITICAL("Failed to get back buffer");
                return false;
        }
        hr = mDevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTarget);
        backBuffer->Release();
        if (FAILED(hr)) {
                CORE_LOG_CRITICAL("Failed to create render target");
                return false;
        }

        return true;
}

void DirectXPlatformWindow::Shutdown() {
        if (mRenderTarget) { mRenderTarget->Release(); mRenderTarget = nullptr; }
        if (mSwapChain) { mSwapChain->Release(); mSwapChain = nullptr; }
        if (mContext) { mContext->Release(); mContext = nullptr; }
        if (mDevice) { mDevice->Release(); mDevice = nullptr; }
        if (mHwnd) {
                DestroyWindow(mHwnd);
                mHwnd = nullptr;
        }
}

void DirectXPlatformWindow::Swapbuffers() {
        FLOAT clearColor[4]{ 1.0f,0.3f,0.8f,1.0f };
        mContext->OMSetRenderTargets(1, &mRenderTarget, nullptr);
        mContext->ClearRenderTargetView(mRenderTarget, clearColor);
        mSwapChain->Present(1, 0);
}

void DirectXPlatformWindow::PollsEvent() {
        MSG msg{};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }
}

bool DirectXPlatformWindow::ShouldClose() {
        return mShouldClose;
}

static LRESULT CALLBACK DXWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
        DirectXPlatformWindow* window = reinterpret_cast<DirectXPlatformWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        switch (msg) {
        case WM_DESTROY:
                if (window) window->mShouldClose = true;
                PostQuitMessage(0);
                return 0;
        default:
                return DefWindowProc(hwnd, msg, wparam, lparam);
        }
}

#else

DirectXPlatformWindow::DirectXPlatformWindow() {}
DirectXPlatformWindow::~DirectXPlatformWindow() {}
bool DirectXPlatformWindow::Init(const ApplicationConfiguration&) {
        CORE_LOG_CRITICAL("DirectX platform not supported on this platform");
        return false;
}
void DirectXPlatformWindow::Shutdown() {}
void DirectXPlatformWindow::Swapbuffers() {}
void DirectXPlatformWindow::PollsEvent() {}
bool DirectXPlatformWindow::ShouldClose() { return true; }

#endif
}
