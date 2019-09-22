//
// Created by Kyle Dagnan on 2019-04-07.
//

#ifndef PROJECT3_BOARD_H
#define PROJECT3_BOARD_H

#include "Tile.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class Board {
    Tile *tiles[16][25];
    int mineCount = 0;
    bool debugMode = false;
    bool lostGame = false;
    bool wonGame = false;
    int remainingSafe = 400;
    sf::Texture digits;
    sf::Texture debug;
    sf::Texture happyFace;
    sf::Texture loseFace;
    sf::Texture winFace;
    sf::Texture flag;
    sf::Texture mine;
    sf::Texture number_1;
    sf::Texture number_2;
    sf::Texture number_3;
    sf::Texture number_4;
    sf::Texture number_5;
    sf::Texture number_6;
    sf::Texture number_7;
    sf::Texture number_8;
    sf::Texture test_1;
    sf::Texture test_2;
    sf::Texture test_3;
    sf::Texture hiddenTile;
    sf::Texture revealedTile;

    sf::Sprite faceSprite;
    sf::Sprite debugSprite;
    sf::Sprite test1Sprite;
    sf::Sprite test2Sprite;
    sf::Sprite test3Sprite;

    string score = "000";
    sf::Sprite scoreSprite1;
    sf::Sprite scoreSprite2;
    sf::Sprite scoreSprite3;
public:
    Board();

    ~Board();

    void drawBoard(sf::RenderWindow &window);

    Tile *getTile(int row, int col);

    void updateScoreSprites();

    void addScore(int addScore);


    void setTileAdjacents();

    void setSpriteText(sf::Sprite *sprite, sf::Texture &text);

    void generateMines();

    void setupBoard();

    void loadBoardFromFile(string file);

    void handleClick(int x, int y, string type);

    void handleReveal(Tile *tile);

    void flagTile(Tile *tile);

    void endGame();
    void winGame();
};

#endif //PROJECT3_BOARD_H
