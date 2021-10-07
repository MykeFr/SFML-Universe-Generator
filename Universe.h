#pragma once

#include "GraphicsFramework/main.h"

#include "Lehmer32.hpp"

#define SECTOR_SIZE 16.f

class Universe : public GF::App
{
public:

	Universe(std::string t = "The Universe");

	// called once before the game starts
	bool onCreate() override;

	// first thing to be called every frame
	bool onHandleEvent(GF::Event& event) override;

	// called every frame before draw
	bool onUpdate(const float fElapsedTime, const float fTotalTime) override;

	// last thing to be called every frame
	bool onDraw() override;

	void onDestroy();

	void onSwitch(std::string) override {}

private:

private:
	sf::Vector2f galaxyOffset = sf::Vector2f(0, 0);

};
