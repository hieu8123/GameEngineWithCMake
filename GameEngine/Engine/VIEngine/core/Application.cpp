#include"Application.h"
#include<iostream>

#include"core/logger/logger.h"
#include <chrono>

namespace VIEngine {
	Application::Application(const ApplicationConfiguration& config) : mConfig(config) {
		mNativeWindow.reset(WindowPlatform::Create(config.WindowSpec));
	}

	bool Application::Init() {
		Logger::Init();

		if (!mNativeWindow->Init(mConfig)) {
			return false;
		}

		return true;
	}

	void Application::Run() {
		CORE_LOG_INFO("App is running: ({0}, {1}, {2})", mConfig.Width, mConfig.Height, mConfig.Title);

		OnInitClient();

		auto previousTime = std::chrono::high_resolution_clock::now();
		while (!mNativeWindow->ShouldClose()) {
			auto currentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> delta = currentTime - previousTime;
			previousTime = currentTime;

			OnUpdate(delta.count());

			mNativeWindow->Swapbuffers();
			mNativeWindow->PollsEvent();
		}

		OnShutdownClient();
	}

	void Application::Shutdown() {
		mNativeWindow->Shutdown();
	}
}