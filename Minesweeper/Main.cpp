#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "FileManager.h"
#include "Random.h"
#include "Tile.h"
#include "Minesweeper.h"

using namespace std;

int main()
{
    //reading in dimensions
    ifstream myfile;
    string token;
    myfile.open("boards/config.cfg");
    int colnumber;
    int rownumber;
    int minenumber;
    if (myfile.is_open())
    {
        istringstream stream(token);
        myfile >> colnumber;
        myfile >> rownumber;
        myfile >> minenumber;
    }
    myfile.close();
    int windowwidth = (32 * colnumber);
    int windowheight = (32 * rownumber);

    sf::RenderWindow window(sf::VideoMode(windowwidth, (windowheight)+100), "Minesweeper");
    Minesweeper game;
    game.flagsleft = minenumber;
    game.rowsize = rownumber;
    game.colsize = colnumber;
    game.resetboard();
    game.drawboard(rownumber, colnumber, window, game.board); 
    game.placebombs(minenumber,rownumber, colnumber);
    game.setpointers();
    game.setadjacenttiles();

    //setting buttons part 1
    sf::Sprite facebtn(TextureManager::GetTexture("face_happy"));
    facebtn.setPosition(windowwidth - 384, windowheight);
    sf::Sprite debugbtn(TextureManager::GetTexture("debug"));
    debugbtn.setPosition(windowwidth - 256, windowheight);
    sf::Sprite test1btn(TextureManager::GetTexture("test_1"));
    test1btn.setPosition(windowwidth - 192, windowheight);
    sf::Sprite test2btn(TextureManager::GetTexture("test_2"));
    test2btn.setPosition(windowwidth - 128, windowheight);
    sf::Sprite test3btn(TextureManager::GetTexture("test_3"));
    test3btn.setPosition(windowwidth-64, windowheight);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    auto mouseposition = sf::Mouse::getPosition(window);
                    for (int i = 0; i < colnumber; i++)
                    {
                        for (int j = 0; j < rownumber; j++)
                        {
                            if (game.board[i][j].Contains(mouseposition.x, mouseposition.y))
                            {
                                if (game.gamelost == false && game.gamewon == false)
                                {
                                    if (game.board[i][j].hasbomb == false && game.board[i][j].hasflag == false && game.board[i][j].numberofadjacentbombs == 0)
                                    {
                                        game.board[i][j].revealtile();
                                        game.board[i][j].revealnearbytiles();
                                    }
                                    if (game.board[i][j].hasbomb == true && game.board[i][j].hasflag == false)
                                    {
                                        game.gamelost = true;
                                        game.revealmines();
                                    }
                                    if (game.board[i][j].hasflag == false)
                                        game.board[i][j].revealtile();
                                    if (game.checkifvictory())
                                        game.gamewon = true;
                                }
                            }
                        }
                    }
                    if (facebtn.getGlobalBounds().contains(mouseposition.x, mouseposition.y))
                    {
                        game.resetboard();
                        game.drawboard(rownumber, colnumber, window, game.board);
                        game.placebombs(minenumber, rownumber, colnumber);
                        game.setpointers();
                        game.setadjacenttiles();
                    }
                    if (debugbtn.getGlobalBounds().contains(mouseposition.x, mouseposition.y))
                    {
                        game.revealmines();
                    }
                    if (test1btn.getGlobalBounds().contains(mouseposition.x, mouseposition.y))
                    {
                        game.testboard1(window);
                    }
                    if (test2btn.getGlobalBounds().contains(mouseposition.x, mouseposition.y))
                    {
                        game.testboard2(window);
                    }
                    if (test3btn.getGlobalBounds().contains(mouseposition.x, mouseposition.y))
                    {
                        game.testboard3(window);
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    auto mouseposition2 = sf::Mouse::getPosition(window);
                    for (int i = 0; i < colnumber; i++)
                    {
                        for (int j = 0; j < rownumber; j++)
                        {
                            if (game.board[i][j].Contains(mouseposition2.x, mouseposition2.y) && game.board[i][j].revealed == false)
                            {
                                if (game.gamewon == false && game.gamelost == false)
                                {
                                    if (game.board[i][j].hasflag == true)
                                        game.flagsleft += 1;
                                    if (game.board[i][j].hasflag == false)
                                        game.flagsleft -= 1;

                                    game.board[i][j].flagtile();
                                }
                            }     
                        }
                    }
                }
            }
            window.clear(); 
            
            //redrawing tile sprites
            for (int i = 0; i < colnumber; i++)
            {
                for (int j = 0; j < rownumber; j++)
                {
                    game.board[i][j].GetSprite(window);
                }
            }
            
            game.drawflagcounter(window, windowwidth, windowheight);
            
            //setting buttons part 2
            window.draw(facebtn);
            game.drawfacebutton(window, windowwidth, windowheight);
            window.draw(debugbtn);
            window.draw(test1btn);
            window.draw(test2btn);
            window.draw(test3btn);
            
            window.display(); 
        }
    }
    TextureManager::clear(); 
    return 0;
}