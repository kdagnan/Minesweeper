//
// Created by Kyle Dagnan on 2019-04-07.
//

#ifndef PROJECT3_TILE_H
#define PROJECT3_TILE_H
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

class Tile{
    bool revealed = false;
    bool isMine = false;
    bool isFlagged = false;
    int adjMines = 0;
    vector<Tile *> adjacentTiles;
    sf::Sprite * sprite = new sf::Sprite;
    sf::Sprite * sprite2 = new sf::Sprite;
    sf::Sprite * flagSprite = new sf::Sprite;
public:
    Tile(sf::Texture &texture, sf::Texture &flagTexture);
    sf::Sprite * getSprite() { return sprite; }
    sf::Sprite * getSprite2() { return sprite2; }
    sf::Sprite * getFlagSprite() { return flagSprite; }
    bool getIsMine(){ return isMine; }
    bool getIsRevealed(){ return revealed; }
    bool getIsFlagged(){ return isFlagged; }
    int getAdjMines(){ return adjMines; }
    vector<Tile*> * getAdjTiles(){ return &adjacentTiles; }
    void setAdjacentTiles(vector<Tile *> &adjTiles);
    void setIsMine(bool set){ isMine = set; }
    void setIsRevealed(bool set){ revealed = set; }
    void setIsFlagged(bool set){ isFlagged = set; }
    void moveSprites(float x, float y);
    void makeMine();
};

#endif //PROJECT3_TILE_H
