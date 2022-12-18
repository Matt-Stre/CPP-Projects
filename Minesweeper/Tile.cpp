#include "Tile.h"



//tile functions
Tile::Tile()
{
	hiddensprite.setTexture(TextureManager::GetTexture("tile_hidden"));
	revealedsprite.setTexture(TextureManager::GetTexture("tile_revealed"));
	minesprite.setTexture(TextureManager::GetTexture("mine"));
	flagsprite.setTexture(TextureManager::GetTexture("flag"));
	onesprite.setTexture(TextureManager::GetTexture("number_1"));
	twosprite.setTexture(TextureManager::GetTexture("number_2"));
	threesprite.setTexture(TextureManager::GetTexture("number_3"));
	foursprite.setTexture(TextureManager::GetTexture("number_4"));
	fivesprite.setTexture(TextureManager::GetTexture("number_5"));
	sixsprite.setTexture(TextureManager::GetTexture("number_6"));
	sevensprite.setTexture(TextureManager::GetTexture("number_7"));
	eightsprite.setTexture(TextureManager::GetTexture("number_8"));


}

void Tile::GetSprite(sf::RenderWindow& window)
{
	window.draw(revealedsprite);
	if (hasbomb == true)
		window.draw(minesprite);
	if (numberofadjacentbombs == 1 && hasbomb==false)
		window.draw(onesprite);
	if (numberofadjacentbombs == 2 && hasbomb == false)
		window.draw(twosprite);
	if (numberofadjacentbombs == 3 && hasbomb == false)
		window.draw(threesprite);
	if (numberofadjacentbombs == 4 && hasbomb == false)
		window.draw(foursprite);
	if (numberofadjacentbombs == 5 && hasbomb == false)
		window.draw(fivesprite);
	if (numberofadjacentbombs == 6 && hasbomb == false)
		window.draw(sixsprite);
	if (numberofadjacentbombs == 7 && hasbomb == false)
		window.draw(sevensprite);
	if (numberofadjacentbombs == 8 && hasbomb == false)
		window.draw(eightsprite);

	if (revealed == false)
		window.draw(hiddensprite);
	if (hasflag == true)
		window.draw(flagsprite);
	if (showbomb == true)
		window.draw(minesprite);
	

}


void Tile::SetPosition(float x, float y)
{
	hiddensprite.setPosition(x, y);
	revealedsprite.setPosition(x, y);
	minesprite.setPosition(x, y);
	flagsprite.setPosition(x, y);

	onesprite.setPosition(x, y);
	twosprite.setPosition(x, y);
	threesprite.setPosition(x, y);
	foursprite.setPosition(x, y);
	fivesprite.setPosition(x, y);
	sixsprite.setPosition(x, y);
	sevensprite.setPosition(x, y);
	eightsprite.setPosition(x, y);
}

void Tile::revealtile()
{
	
	if (this->hasflag==false)
		this->revealed = true;
}

void Tile::armtile()
{
	this->hasbomb = true;
}

bool Tile::Contains(float x, float y)
{
	return hiddensprite.getGlobalBounds().contains(x,y);
}

void Tile::flagtile()
{
	this->hasflag = !(this->hasflag);
}

sf::Sprite& Tile::InitializeTile()
{
	return revealedsprite;
}

void Tile::revealnearbytiles()
{
	if (topleft!=nullptr && topleft->revealed==false && topleft->hasflag == false)
	{
		topleft->revealtile();
		if (topleft->numberofadjacentbombs == 0)
			topleft->revealnearbytiles();
	}
	if (topcenter !=nullptr && topcenter->revealed==false && topcenter->hasflag == false)
	{
		topcenter->revealtile();
		if (topcenter->numberofadjacentbombs == 0)
				topcenter->revealnearbytiles();
	}
	if (topright !=nullptr && topright->revealed == false && topright->hasflag == false)
	{
		topright->revealtile();
		if (topright->numberofadjacentbombs == 0)
			topright->revealnearbytiles();
	}
	if (left !=nullptr  && left->revealed == false && left->hasflag == false) {
		left->revealtile();
		if (left->numberofadjacentbombs == 0)
			left->revealnearbytiles();
	}
	if (right !=nullptr && right->revealed == false && right->hasflag == false) {
		right->revealtile();
		if (right->numberofadjacentbombs == 0)
			right->revealnearbytiles();
	}
	if (bottomleft !=nullptr && bottomleft->revealed == false && bottomleft->hasflag == false) {
		bottomleft->revealtile();
		if (bottomleft->numberofadjacentbombs == 0)
			bottomleft->revealnearbytiles();
	}
	if (bottomcenter !=nullptr && bottomcenter->revealed == false && bottomcenter->hasflag == false) {
		bottomcenter->revealtile();
		if (bottomcenter->numberofadjacentbombs == 0)
			bottomcenter->revealnearbytiles();
	}
	if (bottomright !=nullptr  && bottomright->revealed == false && bottomright->hasflag == false) {
		bottomright->revealtile();
		if(bottomright->numberofadjacentbombs == 0)
			bottomright->revealnearbytiles();
	}
}

