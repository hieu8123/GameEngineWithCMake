#include"WindowPlatform.h"

#include"pch.h"

namespace VIEngine {
	NativeWindow* WindowPlatform::Create(EWindowPlatformSpec spec) {
		NativeWindow* window = nullptr;

		switch (spec)
		{
#ifndef VIENGINE_HEADLESS
		case EWindowPlatformSpec::GLFW:
			return new GLFWPlatformWindow();
#endif
		case EWindowPlatformSpec::SDL:
			VI_ASSERT(false && "SDL Window not supported");
			return nullptr;
		case EWindowPlatformSpec::None:
			return new NullPlatformWindow();
		default:
			return new NullPlatformWindow();
		}

		return nullptr;
	}
}