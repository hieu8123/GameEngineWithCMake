#pragma once

class GLFWwindow;

#ifdef _WIN32
#include <windows.h>
struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
#endif

namespace VIEngine {
        enum class EWindowPlatformSpec {
                GLFW,
                SDL,
                DirectX,
                None
        };

	class NativeWindow {
	public:
		virtual ~NativeWindow() = default;
		virtual bool Init(const struct ApplicationConfiguration&) = 0;
		virtual void Shutdown() = 0;
		virtual void Swapbuffers() = 0;
		virtual void PollsEvent() = 0;
		virtual bool ShouldClose() = 0;
	protected:
		NativeWindow() = default;
		NativeWindow(NativeWindow&) = default;
	};

        class GLFWPlatformWindow : public NativeWindow {
        public:
                GLFWPlatformWindow();
                ~GLFWPlatformWindow();
                virtual bool Init(const struct ApplicationConfiguration&) override;
                virtual void Shutdown() override;
                virtual void Swapbuffers() override;
                virtual void PollsEvent() override;
                virtual bool ShouldClose() override;
        private:
                GLFWwindow* mWindow;
        };

        class DirectXPlatformWindow : public NativeWindow {
        public:
                DirectXPlatformWindow();
                ~DirectXPlatformWindow();
                virtual bool Init(const struct ApplicationConfiguration&) override;
                virtual void Shutdown() override;
                virtual void Swapbuffers() override;
                virtual void PollsEvent() override;
                virtual bool ShouldClose() override;
        private:
#ifdef _WIN32
                friend LRESULT CALLBACK DXWindowProc(HWND, UINT, WPARAM, LPARAM);
                HWND mHwnd;
                ID3D11Device* mDevice;
                ID3D11DeviceContext* mContext;
                IDXGISwapChain* mSwapChain;
                ID3D11RenderTargetView* mRenderTarget;
                bool mShouldClose;
#endif
        };
}
