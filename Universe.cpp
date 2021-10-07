#include "Universe.h"
#include "StarSystem.h"

Universe::Universe(std::string t)
{
	title = t;
	setupWindow(sf::Vector2u(800, 800), TOPLEFT_I + sf::Vector2i(100, 100), sf::Style::Default);
}

// called once before the game starts
bool Universe::onCreate()
{

	return true;
}


// first thing to be called every frame
bool Universe::onHandleEvent(GF::Event& event)
{
	

	return true;
}


// called every frame before draw
bool Universe::onUpdate(const float fElapsedTime, const float fTotalTime)
{
	int nSectorsX = SCREENWIDTH / SECTOR_SIZE;
	int nSectorsY = SCREENHEIGHT / SECTOR_SIZE;

	sf::Vector2f mouse = { (int)(GF::Mouse::getPosition(window).x / SECTOR_SIZE), (int)(GF::Mouse::getPosition(window).y / SECTOR_SIZE) };
	sf::Vector2f galaxy_mouse = mouse + galaxyOffset;
	sf::Vector2f screen_sector = sf::Vector2f(0, 0);


	for (screen_sector.x = 0; screen_sector.x < nSectorsX; screen_sector.x++) {
		for (screen_sector.y = 0; screen_sector.y < nSectorsY; screen_sector.y++) {
			uint32_t seed1 = (uint32_t)galaxyOffset.x + (uint32_t)screen_sector.x;
			uint32_t seed2 = (uint32_t)galaxyOffset.y + (uint32_t)screen_sector.y;

			cStarSystem star(seed1, seed2);

			if (star.starExists) {
				float x = screen_sector.x * SECTOR_SIZE + SECTOR_SIZE / 2;
				float y = screen_sector.y * SECTOR_SIZE + SECTOR_SIZE / 2;

				window.draw(GF::Circle((int)star.starDiameter / 8, sf::Vector2f(x, y), star.starColour));

				// For convenience highlight hovered star
				if (mouse.x == screen_sector.x && mouse.y == screen_sector.y)
					window.draw(GF::Circle(12, sf::Vector2f(x, y), TRANSPARENT, YELLOW));
			}
		}
	}


	static GF::ToggleKey RIGHT(sf::Keyboard::Right);
	static GF::ToggleKey LEFT(sf::Keyboard::Left);
	static GF::ToggleKey UP(sf::Keyboard::Up);
	static GF::ToggleKey DOWN(sf::Keyboard::Down);

	if (UP.isKeyPressed()) galaxyOffset.y -= 50.0f * fElapsedTime;
	if (DOWN.isKeyPressed()) galaxyOffset.y += 50.0f * fElapsedTime;
	if (LEFT.isKeyPressed()) galaxyOffset.x -= 50.0f * fElapsedTime;
	if (RIGHT.isKeyPressed()) galaxyOffset.x += 50.0f * fElapsedTime;

	return true;
};

// last thing to be called every frame
bool Universe::onDraw()
{

	return true;
};

void Universe::onDestroy()
{

}
