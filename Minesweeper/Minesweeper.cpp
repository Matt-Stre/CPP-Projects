#include "Minesweeper.h"
#include "Tile.h"
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


void Minesweeper::placebombs(int bombstoplace, int rows, int cols)
{
	int bombsplaced = 0;
	while (bombsplaced < bombstoplace)
	{
		int randomrows = Random::Int(0, rows-1);
		int randomcols = Random::Int(0, cols-1);
		if (board[randomcols][randomrows].hasbomb == false)
		{
			board[randomcols][randomrows].hasbomb = true;
			bombsplaced += 1;
			flagsleft += 1;
		}
	}
}


bool Minesweeper::checkifvictory()
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j].revealed == false && board[i][j].hasbomb == false)
			{
				return false;
			}
		}
	}
	if (gamelost == false && gamewon == false)
	{
		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[i].size(); j++)
			{
				if (board[i][j].hasbomb == true)
				{
					if (board[i][j].hasflag==false)
						flagsleft -= 1;
					board[i][j].hasflag=true;
					board[i][j].showbomb = false;
					
				}
			}
		}
	}
	flagsleft = 0; //ensuring flag count is at zero for any edge cases
	return true;
}

void Minesweeper::revealmines()
{
	if (gamelost == false && gamewon == false)
	{
		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[i].size(); j++)
			{
				if (board[i][j].hasbomb == true)
				{
					board[i][j].showbomb = !(board[i][j].showbomb);
				}
			}
		}
	}
	else if (gamelost = true && gamewon==false)
	{
		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[i].size(); j++)
			{
				if (board[i][j].hasbomb == true)
				{
					board[i][j].showbomb = true;
				}
			}
		}
	}
}



void Minesweeper::drawboard(int rows, int cols, sf::RenderWindow& window, vector<vector<Tile>>& board)
{
	for (int i = 0; i < cols; i++)
	{
		vector<Tile> tempvector;
		board.push_back(tempvector);
		for (int j = 0; j < rows; j++)
		{
			Tile tile;
			tile.SetPosition(i * 32, j * 32);
			tile.GetSprite(window);
			board[i].push_back(tile);
		}
	}
}

sf::Sprite& Minesweeper::editimage(sf::Sprite image, char digit)
{
	if (digit == 'z') {
		image.setTextureRect(sf::IntRect(210, 0, 21, 32));
	}
	else if (digit == '1'){
		image.setTextureRect(sf::IntRect(21, 0, 21, 32)); //1
	}
	else if (digit == '2') {
		image.setTextureRect(sf::IntRect(41, 0, 21, 32));
	}
	else if (digit == '3') {
		image.setTextureRect(sf::IntRect(63, 0, 21, 32));
	}
	else if (digit == '4') {
		image.setTextureRect(sf::IntRect(84, 0, 21, 32));
	}
	else if (digit == '5') {
		image.setTextureRect(sf::IntRect(105, 0, 21, 32));
	}
	else if (digit == '6') {
		image.setTextureRect(sf::IntRect(126, 0, 21, 32));
	}
	else if (digit == '7') {
		image.setTextureRect(sf::IntRect(147, 0, 21, 32));
	}
	else if (digit == '8') {
		image.setTextureRect(sf::IntRect(168, 0, 21, 32));
	}
	else if (digit == '9') {
		image.setTextureRect(sf::IntRect(189, 0, 21, 32));
	}
	else if (digit == '0') {
		image.setTextureRect(sf::IntRect(0, 0, 21, 32));
	}
		return image;

	// for reference
	//image.setTextureRect(sf::IntRect(0,0,21,32)); //0
	//image.setTextureRect(sf::IntRect(21, 0, 21, 32)); //1
	//image.setTextureRect(sf::IntRect(41, 0, 21, 32)); //2
	//image.setTextureRect(sf::IntRect(63, 0, 21, 32)); //3
	//image.setTextureRect(sf::IntRect(84, 0, 21, 32)); //4
	//image.setTextureRect(sf::IntRect(105, 0, 21, 32)); //5
	//image.setTextureRect(sf::IntRect(126, 0, 21, 32)); //6
	//image.setTextureRect(sf::IntRect(147, 0, 21, 32)); //7
	//image.setTextureRect(sf::IntRect(168, 0, 21, 32)); //8
	//image.setTextureRect(sf::IntRect(189, 0, 21, 32)); //9
	//image.setTextureRect(sf::IntRect(210, 0, 21, 32)); //-

	//return image;
}

void Minesweeper::resetboard()
{
	for (int i = 0; i < board.size(); i++)
	{
		board.clear();
	}
	gamewon = false;
	gamelost = false;
	flagsleft = 0;
}

void Minesweeper::setadjacenttiles()
{
	for (int i = 0; i < colsize; i++)
	{
		for (int j = 0; j < rowsize; j++)
		{
			board[i][j].numberofadjacentbombs = 0;
			if (board[i][j].topleft!=nullptr && board[i][j].topleft->hasbomb == true)
				board[i][j].numberofadjacentbombs += 1;
			if (board[i][j].topcenter!=nullptr && board[i][j].topcenter->hasbomb == true)
				board[i][j].numberofadjacentbombs += 1;
			if (board[i][j].topright!=nullptr && board[i][j].topright->hasbomb == true)
				board[i][j].numberofadjacentbombs += 1;
			if (board[i][j].left!=nullptr && board[i][j].left->hasbomb == true)
				board[i][j].numberofadjacentbombs += 1;
			if (board[i][j].right!=nullptr && board[i][j].right->hasbomb == true)
				board[i][j].numberofadjacentbombs += 1;
			if (board[i][j].bottomleft!=nullptr && board[i][j].bottomleft->hasbomb == true)
				board[i][j].numberofadjacentbombs += 1;
			if (board[i][j].bottomcenter!=nullptr && board[i][j].bottomcenter->hasbomb == true)
				board[i][j].numberofadjacentbombs += 1;
			if (board[i][j].bottomright!=nullptr && board[i][j].bottomright->hasbomb == true)
				board[i][j].numberofadjacentbombs += 1;
		}
	}
}

void Minesweeper::setpointers()
{
	for (int i = 0; i < colsize; i++)
	{
		for (int j = 0; j < rowsize; j++)
		{
			if (i != 0)
				board[i][j].left = &board[i - 1][j];
			if (i != colsize-1)
				board[i][j].right = &board[i + 1][j];
			if (j != 0)
				board[i][j].topcenter = &board[i][j - 1];
			if (j != 0 && i != 0)
				board[i][j].topleft = &board[i - 1][j - 1];
			if (j != 0 && i != colsize-1)
				board[i][j].topright = &board[i + 1][j - 1];
			if (j != rowsize-1 && i != 0)
				board[i][j].bottomleft = &board[i - 1][j + 1];
			if (j != rowsize-1)
				board[i][j].bottomcenter = &board[i][j + 1];
			if (j != rowsize-1 && i != colsize-1)
				board[i][j].bottomright = &board[i + 1][j + 1];
		}
	}
}

void Minesweeper::testboard1(sf::RenderWindow& window)
{
	//load test file 1
	ifstream file;
	file.open("boards/testboard1.brd");
	string token;
	vector<string> stringvector;
	int rownumber1;
	int colnumber1;
	while (getline(file, token))
	{
		stringvector.push_back(token);
	}
	colnumber1 = stringvector[0].size();
	rownumber1 = stringvector.size();

	resetboard();
	drawboard(rownumber1, colnumber1, window, board);
	for (int i = 0; i < stringvector.size(); i++) // each row (16)
	{
		for (int j = 0; j < stringvector[0].size(); j++) // each col (25)
		{
			if (stringvector[i][j] == '1')
			{
				board[j][i].hasbomb = true;
				flagsleft += 1;
			}
		}
	}
	setpointers();
	setadjacenttiles();
}
void Minesweeper::testboard2(sf::RenderWindow& window)
{
	//load test file 2
	ifstream file;
	file.open("boards/testboard2.brd");
	string token;
	vector<string> stringvector;
	int rownumber1;
	int colnumber1;
	while (getline(file, token))
	{
		stringvector.push_back(token);
	}
	colnumber1 = stringvector[0].size();
	rownumber1 = stringvector.size();

	resetboard();
	drawboard(rownumber1, colnumber1, window, board);
	for (int i = 0; i < stringvector.size(); i++) // each row (16)
	{
		for (int j = 0; j < stringvector[0].size(); j++) // each col (25)
		{
			if (stringvector[i][j] == '1')
			{
				board[j][i].hasbomb = true;
				flagsleft += 1;
			}
		}
	}
	setpointers();
	setadjacenttiles();
}

void Minesweeper::testboard3(sf::RenderWindow& window)
{
	//load test file 3
	ifstream file;
	file.open("boards/testboard3.brd");
	string token;
	vector<string> stringvector;
	int rownumber1;
	int colnumber1;
	while (getline(file, token))
	{
		stringvector.push_back(token);
	}
	colnumber1 = stringvector[0].size();
	rownumber1 = stringvector.size();

	resetboard();
	drawboard(rownumber1, colnumber1, window, board);
	for (int i = 0; i < stringvector.size(); i++) // each row (16)
	{
		for (int j = 0; j < stringvector[0].size(); j++) // each col (25)
		{
			if (stringvector[i][j] == '1')
			{
				board[j][i].hasbomb = true;
				flagsleft += 1;
			}
		}
	}
	setpointers();
	setadjacenttiles();
}

void Minesweeper::drawfacebutton(sf::RenderWindow& window, int windowwidth, int windowheight)
{
	if (gamewon == true)
	{
		sf::Sprite facebtn(TextureManager::GetTexture("face_win"));
		facebtn.setPosition(windowwidth - 384, windowheight);
		window.draw(facebtn);
	}
	else if (gamelost == true)
	{
		sf::Sprite facebtn(TextureManager::GetTexture("face_lose"));
		facebtn.setPosition(windowwidth - 384, windowheight);
		window.draw(facebtn);
	}
}

void Minesweeper::drawflagcounter(sf::RenderWindow& window, int windowwidth, int windowheight)
{
	//setting buttons part 2
	sf::Sprite bombcounterbtn2(TextureManager::GetTexture("digits"));
	bombcounterbtn2.setPosition(21, windowheight);
	sf::Sprite bombcounterbtn3(TextureManager::GetTexture("digits"));
	bombcounterbtn3.setPosition(42, windowheight);
	sf::Sprite bombcounterbtn4(TextureManager::GetTexture("digits"));
	bombcounterbtn4.setPosition(63, windowheight);

	string digit = to_string(flagsleft);
	if (flagsleft < 0)
	{
		sf::Sprite bombcounterbtn1(TextureManager::GetTexture("digits"));
		bombcounterbtn1.setPosition(0, windowheight);
		sf::Sprite test = editimage(bombcounterbtn1, 'z');
		window.draw(test);
		digit.erase(0, 1); //removes the -

	}
	else
	{
		string digit = to_string(flagsleft);
	}
	if (digit.size() == 1)
	{
		sf::Sprite bombcounterbtn2(TextureManager::GetTexture("digits"));
		bombcounterbtn2.setPosition(21, windowheight);
		sf::Sprite test = editimage(bombcounterbtn2, '0');
		window.draw(test);
		sf::Sprite bombcounterbtn3(TextureManager::GetTexture("digits"));
		bombcounterbtn3.setPosition(42, windowheight);
		sf::Sprite test2 = editimage(bombcounterbtn3, '0');
		window.draw(test2);

		char input = digit[0];
		sf::Sprite bombcounterbtn4(TextureManager::GetTexture("digits"));
		bombcounterbtn4.setPosition(63, windowheight);
		sf::Sprite test3 = editimage(bombcounterbtn4, input);
		window.draw(test3);
	}
	else if (digit.size() == 2)
	{
		sf::Sprite bombcounterbtn2(TextureManager::GetTexture("digits"));
		bombcounterbtn2.setPosition(21, windowheight);
		sf::Sprite test = editimage(bombcounterbtn2, '0');
		window.draw(test);

		char input = digit[0];
		sf::Sprite bombcounterbtn3(TextureManager::GetTexture("digits"));
		bombcounterbtn3.setPosition(42, windowheight);
		sf::Sprite test2 = editimage(bombcounterbtn3, input);
		window.draw(test2);

		char input2 = digit[1];
		sf::Sprite bombcounterbtn4(TextureManager::GetTexture("digits"));
		bombcounterbtn4.setPosition(63, windowheight);
		sf::Sprite test3 = editimage(bombcounterbtn4, input2);
		window.draw(test3);
	}
	else if (digit.size() == 3)
	{
		char input = digit[0];
		sf::Sprite bombcounterbtn2(TextureManager::GetTexture("digits"));
		bombcounterbtn2.setPosition(21, windowheight);
		sf::Sprite test = editimage(bombcounterbtn2, input);
		window.draw(test);

		char input2 = digit[1];
		sf::Sprite bombcounterbtn3(TextureManager::GetTexture("digits"));
		bombcounterbtn3.setPosition(42, windowheight);
		sf::Sprite test2 = editimage(bombcounterbtn3, input2);
		window.draw(test2);

		char input3 = digit[2];
		sf::Sprite bombcounterbtn4(TextureManager::GetTexture("digits"));
		bombcounterbtn4.setPosition(63, windowheight);
		sf::Sprite test3 = editimage(bombcounterbtn4, input3);
		window.draw(test3);
	}
}

