#pragma once

class GLFWwindow;

namespace VIEngine {
	enum class EWindowPlatformSpec {
		GLFW,
		SDL,
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

#ifndef VIENGINE_HEADLESS
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
#endif

	class NullPlatformWindow : public NativeWindow {
	public:
		NullPlatformWindow();
		~NullPlatformWindow();
		virtual bool Init(const struct ApplicationConfiguration&) override;
		virtual void Shutdown() override;
		virtual void Swapbuffers() override;
		virtual void PollsEvent() override;
		virtual bool ShouldClose() override;
	private:
		int mTickCount;
		int mMaxTicks;
		bool mShouldClose;
	};
}