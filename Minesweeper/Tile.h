#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "FileManager.h"
#include "Random.h"
using namespace std;

class Tile
{
public:
	sf::Sprite hiddensprite; // when block not pressed
	sf::Sprite revealedsprite; // when block pressed and no bomb
	sf::Sprite minesprite; // when block pressed and bomb = game over
	sf::Sprite flagsprite;
	sf::Sprite onesprite;
	sf::Sprite twosprite;
	sf::Sprite threesprite;
	sf::Sprite foursprite;
	sf::Sprite fivesprite;
	sf::Sprite sixsprite;
	sf::Sprite sevensprite;
	sf::Sprite eightsprite;


	bool hasbomb = false;
	bool hasflag=false;
	bool revealed = false;
	bool showbomb = false;
	int numberofadjacentbombs;

	//pointers
	Tile* topleft = nullptr;
	Tile* topcenter = nullptr;
	Tile* topright = nullptr;
	Tile* left = nullptr;
	Tile* right = nullptr;
	Tile* bottomleft = nullptr;
	Tile* bottomcenter = nullptr;
	Tile* bottomright = nullptr;


	Tile();
	void GetSprite(sf::RenderWindow& window);
	void SetPosition(float x, float y);
	void revealtile();
	void armtile();
	bool Contains(float x, float y);
	void flagtile();
	sf::Sprite& InitializeTile();
	void revealnearbytiles();


};
