#pragma once

#include "Lehmer32.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Color g_starColours[8] = {
	sf::Color::Black,
	sf::Color::White,
	sf::Color::Red,
	sf::Color::Green,
	sf::Color::Blue,
	sf::Color::Yellow,
	sf::Color::Magenta,
	sf::Color::Cyan,
};

struct sPlanet {
	double distance = 0.0;
	double diameter = 0.0;
	double foliage = 0.0;
	double minerals = 0.0;
	double water = 0.0;
	double gases = 0.0;
	double temperature = 0.0;
	double population = 0.0;
	bool ring = false;
	std::vector<double> vMoons;
};

class cStarSystem
{
public:
	cStarSystem(uint32_t x, uint32_t y, bool bGenerateFullSystem = false)
	{
		// Set seed based on location of star system
		Lehmer32.setSeed((x & 0xFFFF) << 16 | (y & 0xFFFF));

		// Not all locations contain a system
		starExists = (Lehmer32.getI(0, 20) == 1);

		if (!starExists) return;

		// Generate Star
		starDiameter = Lehmer32.getD(10.0, 40.0);
		starColour = g_starColours[Lehmer32.getI(0, 8)];;

		// When viewing the galaxy map, we only care about the star
		// so abort early
		if (!bGenerateFullSystem) return;

		// If we are viewing the system map, we need to generate the
		// full system

		// Generate Planets
		double dDistanceFromStar = Lehmer32.getD(60.0, 200.0);
		int nPlanets = Lehmer32.getI(0, 10);

		for (int i = 0; i < nPlanets; i++) {
			sPlanet p;
			p.distance = dDistanceFromStar;
			dDistanceFromStar += Lehmer32.getD(20.0, 200.0);
			p.diameter = Lehmer32.getD(4.0, 20.0);

			// Could make temeprature a function of distance from star
			p.temperature = Lehmer32.getD(-200.0, 300.0);

			// Composition of planet
			p.foliage = Lehmer32.getD(0.0, 1.0);
			p.minerals = Lehmer32.getD(0.0, 1.0);
			p.gases = Lehmer32.getD(0.0, 1.0);
			p.water = Lehmer32.getD(0.0, 1.0);

			// Normalise to 100%
			double dSum = 1.0 / (p.foliage + p.minerals + p.gases + p.water);
			p.foliage *= dSum;
			p.minerals *= dSum;
			p.gases *= dSum;
			p.water *= dSum;

			// Population could be a function of other habitat encouraging
			// properties, such as temperature and water
			p.population = std::max(Lehmer32.getI(-5000000, 20000000), 0);

			// 10% of planets have a ring
			p.ring = Lehmer32.getI(0, 10) == 1;

			// Satellites (Moons)
			int nMoons = std::max(Lehmer32.getI(-5, 5), 0);

			for (int n = 0; n < nMoons; n++) {
				// A moon is just a diameter for now, but it could be
				// whatever you want!
				p.vMoons.push_back(Lehmer32.getD(1.0, 5.0));
			}

			// Add planet to vector
			vPlanets.push_back(p);
		}
	}

	~cStarSystem()
	{

	}

public:
	std::vector<sPlanet> vPlanets;

public:
	bool		starExists = false;
	double		starDiameter = 0.0f;
	sf::Color	starColour = WHITE;
};