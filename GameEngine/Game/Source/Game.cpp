#include <VIEngine/core/entry.h>
#include <iostream>
#include "Core/logger/logger.h"

class Game : public VIEngine::Application {
public:
	Game(const VIEngine::ApplicationConfiguration& config) : VIEngine::Application(config) {
		
		LOG_TRACE("TRACE WORKS");
		LOG_DEBUG("DEBUG WORKS");
		LOG_INFO("INFO WORKS");
		LOG_WARN("WARN WORKS");
		LOG_ERROR("ERROR WORKS");
		LOG_CRITICAL("CRITICAL WORKS");
	}

	virtual bool Init() override{
		std::cout << "Game is init\n";
		return  true;
	}

	virtual void Shutdown() override {
		std::cout << "Game is shutdown\n";
	}
};


VIEngine::Application* VIEngine::CreateApplication() {
	using namespace  VIEngine;

	ApplicationConfiguration  appConfig;
	appConfig.Width = 800;
	appConfig.Height = 600;
	appConfig.Title = "VIEngin fist version!";

	return new Game(appConfig);
}
