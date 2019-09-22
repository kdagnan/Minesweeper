//
// Created by Kyle Dagnan on 2019-04-07.
//
#include "Tile.h"
#include <iostream>

Tile::Tile(sf::Texture &texture, sf::Texture &flagTexture) {
    sprite->setTexture(texture);
    sprite2->setTexture(texture);
    flagSprite->setTexture(flagTexture);
}

void Tile::moveSprites(float y, float x) {
    sprite->move(sf::Vector2f(y, x));
    sprite2->move(sf::Vector2f(y, x));
    flagSprite->move(sf::Vector2f(y, x));
}

void Tile::makeMine() {
    isMine = true;
}

void Tile::setAdjacentTiles(vector<Tile *> &adjTiles){
    adjacentTiles = adjTiles;
    adjMines = 0;
    for(int i = 0; i < adjTiles.size(); i++){
        Tile * curTile = adjTiles.at(i)
;        if(curTile->getIsMine()){
            adjMines++;
        }
    }
}