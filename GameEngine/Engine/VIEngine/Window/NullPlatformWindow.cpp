#include "Window.h"
#include "pch.h"

namespace VIEngine {
	NullPlatformWindow::NullPlatformWindow()
		: mTickCount(0), mMaxTicks(300), mShouldClose(false) {}

	NullPlatformWindow::~NullPlatformWindow() {}

	bool NullPlatformWindow::Init(const ApplicationConfiguration&) {
		mTickCount = 0;
		mShouldClose = false;
		return true;
	}

	void NullPlatformWindow::Shutdown() {
		mShouldClose = true;
	}

	void NullPlatformWindow::Swapbuffers() {
		// No-op in headless mode
	}

	void NullPlatformWindow::PollsEvent() {
		// Simulate progress
		++mTickCount;
		if (mTickCount >= mMaxTicks) {
			mShouldClose = true;
		}
	}

	bool NullPlatformWindow::ShouldClose() {
		return mShouldClose;
	}
}