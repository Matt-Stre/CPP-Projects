#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "FileManager.h"
#include "Random.h"
#include "Tile.h"
using namespace std;

class Minesweeper
{
	
public:
	vector<vector<Tile>> board;
	int rowsize;
	int colsize;
	bool gamewon = false;
	bool gamelost = false;
	int flagsleft;

	//void minesweeper();
	void placebombs(int bombstoplace, int rows, int cols); 
	void facebtn();
	bool checkifvictory();
	void revealmines();
	void drawboard(int rows, int cols, sf::RenderWindow& window, vector<vector<Tile>>& board);
	sf::Sprite& editimage(sf::Sprite image, char digit);
	void resetboard();
	void setadjacenttiles();
	void setpointers();
	void testboard1(sf::RenderWindow& window);
	void testboard2(sf::RenderWindow& window);
	void testboard3(sf::RenderWindow& window);
	void drawfacebutton(sf::RenderWindow& window, int windowwidth, int windowheight);
	void drawflagcounter(sf::RenderWindow& window, int windowwidth, int windowheight);

};



