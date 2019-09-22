#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Board.h"
#include "Tile.h"

using namespace std;

int main() {
   // generateTextures();
    sf::RenderWindow window(sf::VideoMode(800, 600), "KyleSweeper");
    // run the program as long as the window is open
    Board board;
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonReleased){
                if(event.mouseButton.button == sf::Mouse::Left){
                    board.handleClick(event.mouseButton.x, event.mouseButton.y, "left");
                }else if(event.mouseButton.button == sf::Mouse::Right){
                    board.handleClick(event.mouseButton.x, event.mouseButton.y, "right");
                }
            }
        }
        window.clear();
        board.drawBoard(window);
        window.display();
    }

    return 0;
}