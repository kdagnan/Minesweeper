//
// Created by Kyle Dagnan on 2019-04-07.
//

#include "Board.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

Board::Board() {
    if (!digits.loadFromFile("images/digits.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!debug.loadFromFile("images/debug.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!happyFace.loadFromFile("images/face_happy.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!loseFace.loadFromFile("images/face_lose.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!winFace.loadFromFile("images/face_win.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!flag.loadFromFile("images/flag.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!mine.loadFromFile("images/mine.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!number_1.loadFromFile("images/number_1.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!number_2.loadFromFile("images/number_2.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!number_3.loadFromFile("images/number_3.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!number_4.loadFromFile("images/number_4.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!number_5.loadFromFile("images/number_5.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!number_6.loadFromFile("images/number_6.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!number_7.loadFromFile("images/number_7.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!number_8.loadFromFile("images/number_8.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!test_1.loadFromFile("images/test_1.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!test_2.loadFromFile("images/test_2.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!test_3.loadFromFile("images/Test_3.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!hiddenTile.loadFromFile("images/tile_hidden.png"))
    {
        cout << "Error loading File..." << endl;
    }
    if (!revealedTile.loadFromFile("images/tile_revealed.png"))
    {
        cout << "Error loading File..." << endl;
    }

    faceSprite.setTexture(happyFace);
    faceSprite.move(sf::Vector2f(6*64, 32*16));
    debugSprite.setTexture(debug);
    debugSprite.move(sf::Vector2f(8*64, 32*16));
    test1Sprite.setTexture(test_1);
    test1Sprite.move(sf::Vector2f(9*64, 32*16));
    test2Sprite.setTexture(test_2);
    test2Sprite.move(sf::Vector2f(10*64, 32*16));
    test3Sprite.setTexture(test_3);
    test3Sprite.move(sf::Vector2f(11*64, 32*16));
    scoreSprite1.move(sf::Vector2f(0, 32*16));
    scoreSprite1.setTexture(digits);
    scoreSprite2.move(sf::Vector2f(21, 32*16));
    scoreSprite2.setTexture(digits);
    scoreSprite3.move(sf::Vector2f(42, 32*16));
    scoreSprite3.setTexture(digits);
    setupBoard();
}

Board::~Board() {
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            delete tiles[i][j];
        }
    }
}

void Board::drawBoard(sf::RenderWindow & window) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            Tile *tile = tiles[i][j];
            sf::Sprite *sprite = tile->getSprite();
            sf::Sprite *sprite2 = tile->getSprite2();
            if (lostGame) {
                if (tile->getIsRevealed()) {
                    window.draw(*sprite);
                    window.draw(*sprite2);
                }else{
                    if(tile->getIsMine()){
                        setSpriteText(sprite, revealedTile);
                        window.draw(*sprite);
                        window.draw(*sprite2);
                    }else{
                        window.draw(*sprite);
                    }
                }
            }else if(wonGame){
                if (tile->getIsRevealed()) {
                    window.draw(*sprite);
                    window.draw(*sprite2);
                }else{
                    if(tile->getIsMine()){
                        window.draw(*sprite);
                        window.draw(*tile->getFlagSprite());
                    }
                }
            } else {
                if (debugMode) {
                    window.draw(*sprite);
                    if (tile->getIsMine() || tile->getIsRevealed()) {
                        window.draw(*sprite2);
                    }
                    if (tile->getIsFlagged() && !tile->getIsRevealed()) {
                        window.draw(*tile->getFlagSprite());
                    }
                }else{
                    if (tile->getIsRevealed()) {
                        window.draw(*sprite);
                        window.draw(*sprite2);
                    } else {
                        window.draw(*sprite);
                        if (tile->getIsFlagged()) {
                            window.draw(*tile->getFlagSprite());
                        }
                    }
                }
            }
        }
    }
    updateScoreSprites();
    window.draw(faceSprite);
    window.draw(debugSprite);
    window.draw(test1Sprite);
    window.draw(test2Sprite);
    window.draw(test3Sprite);
    window.draw(scoreSprite1);
    window.draw(scoreSprite2);
    window.draw(scoreSprite3);
}

void Board::setupBoard() {
    lostGame = false;
    wonGame = false;
    remainingSafe = 400;
    setSpriteText(&faceSprite, happyFace);
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            if(!tiles[i][j]){
                delete tiles[i][j];
            }
            tiles[i][j] = new Tile(hiddenTile, flag);
            tiles[i][j]->moveSprites(j*32,i*32);
        }
    }
    mineCount = 0;
    generateMines();
    setTileAdjacents();
}

void Board::generateMines() {
    srand (time(NULL));
    while(mineCount < 50){
        //srand (time(NULL));
        int iRand = rand() % 16;
        int jRand = rand() % 25;
        Tile * tile = tiles[iRand][jRand];
        if(!tile->getIsMine()){
            tile->makeMine();
            setSpriteText(tile->getSprite2(), mine);
            mineCount++;
            remainingSafe-=1;
        }
     }
}

void Board::loadBoardFromFile(string fileLoc){
    char ch;
    fstream file(fileLoc, fstream::in);
    int i = 0;
    int j = 0;
    mineCount = 0;
    remainingSafe = 400;
    while (file >> ch) {
        Tile * tile = tiles[i][j];
        setSpriteText(tile->getSprite(), hiddenTile);
        if(ch == '0'){
            tile->setIsMine(false);
            tile->setIsRevealed(false);
            setSpriteText(tile->getSprite2(), revealedTile);
        }else if (ch == '1'){
            tile->setIsMine(true);
            remainingSafe-=1;
            tile->setIsRevealed(false);
            mineCount++;
            setSpriteText(tile->getSprite2(), mine);
        }
        j++;
        if(j > 24) {
            j = 0;
            i++;
        }
    }
    setTileAdjacents();
}

void Board::setTileAdjacents(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            vector<Tile*> adjTiles;
            if(i - 1 >= 0){
                if(j+1 < 25){
                    Tile * tile = tiles[i-1][j+1];
                    adjTiles.push_back(tile);
                }
                if(j-1 >= 0){
                    Tile * tile = tiles[i-1][j-1];
                    adjTiles.push_back(tile);
                }
                Tile * tile = tiles[i-1][j];
                adjTiles.push_back(tile);
            }
            if(i+1 < 16){
                if(j+1 < 25){
                    Tile * tile = tiles[i+1][j+1];
                    adjTiles.push_back(tile);
                }
                if(j-1 >= 0){
                    Tile * tile = tiles[i+1][j-1];
                    adjTiles.push_back(tile);
                }
                Tile * tile = tiles[i+1][j];
                adjTiles.push_back(tile);
            }
            if(j+1 < 25){
                Tile * tile = tiles[i][j+1];
                adjTiles.push_back(tile);
            }
            if(j-1 >= 0){
                Tile * tile = tiles[i][j-1];
                adjTiles.push_back(tile);
            }
            Tile * curTile = tiles[i][j];
            curTile->setAdjacentTiles(adjTiles);
            if(curTile->getIsMine()){
                setSpriteText(curTile->getSprite2(), mine);
            }else{
                int adjMineCount = curTile->getAdjMines();
                switch(adjMineCount){
                    case 0:
                        setSpriteText(curTile->getSprite2(), revealedTile);
                        break;
                    case 1:
                        setSpriteText(curTile->getSprite2(), number_1);
                        break;
                    case 2:
                        setSpriteText(curTile->getSprite2(), number_2);
                        break;
                    case 3:
                        setSpriteText(curTile->getSprite2(), number_3);
                        break;
                    case 4:
                        setSpriteText(curTile->getSprite2(), number_4);
                        break;
                    case 5:
                        setSpriteText(curTile->getSprite2(), number_5);
                        break;
                    case 6:
                        setSpriteText(curTile->getSprite2(), number_6);
                        break;
                    case 7:
                        setSpriteText(curTile->getSprite2(), number_7);
                        break;
                    case 8:
                        setSpriteText(curTile->getSprite2(), number_8);
                        break;
                }
            }
        }
    }
}

void Board::updateScoreSprites() {
    int flaggedMines = 0;
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            Tile * curTile = tiles[i][j];
            if(curTile->getIsFlagged()){
                flaggedMines++;
            }
        }
    }
    int curScore = mineCount - flaggedMines;
    score = to_string(curScore) + "";
    char digit1 = score[0];
    if(digit1 == '-'){
        scoreSprite1.setTextureRect(sf::IntRect(21*10,0,21,32));
    }else{
        int dig1 = digit1 - 48;
        scoreSprite1.setTextureRect(sf::IntRect(21*dig1,0,21,32));
    }
    char digit2 = score[1];
    int dig2 = digit2 - 48;
    scoreSprite2.setTextureRect(sf::IntRect(21*dig2,0,21,32));
    char digit3 = score[2];
    int dig3 = digit3 - 48;
    scoreSprite3.setTextureRect(sf::IntRect(21*dig3,0,21,32));
}

void Board::addScore(int addScore){
    int curScore = stoi(score);
    curScore = curScore + addScore;
    score = "" +  to_string(curScore);
}

Tile * Board::getTile(int row, int col){
    return tiles[row][col];
}

void Board::setSpriteText(sf::Sprite * sprite, sf::Texture & text){
    sprite->setTexture(text);
}


void Board::handleClick(int x, int y, string type){
    if(y > 512 && y < 578){
        //Below tiles. Process extra options
        if(x >= (64*6) && x <= (64*7)){
            setupBoard();
        }else if(x >= (64*8) && x < (64*9) && !lostGame && !wonGame){
            if(debugMode){ debugMode = false; }else{debugMode = true; }
        }
        else if(x >= (64*9) && x < (64*10) && !lostGame && !wonGame){
            loadBoardFromFile("boards/testboard1.brd");
        }
        else if(x >= (64*10) && x < (64*11) && !lostGame && !wonGame){
            loadBoardFromFile("boards/testboard2.brd");
        }
        else if(x >= (64*11) && x < (64*12) && !lostGame && !wonGame){
            loadBoardFromFile("boards/testboard3.brd");
        }
    }else if(!lostGame && !wonGame) {
        //Game Board. Work on revealing
        int row = y / 32;
        int col = x / 32;
        Tile *curTile = tiles[row][col];
        if(type == "left"){
            if(!curTile->getIsFlagged() && !curTile->getIsRevealed()){
                handleReveal(curTile);
            }
        }else if(type == "right"){
            flagTile(curTile);
        }else{
            cout << "Wrong click type given" << endl;
        }
    }

}

void Board::flagTile(Tile* tile) {
    if(tile->getIsFlagged()){
        tile->setIsFlagged(false);
    }else {
        tile->setIsFlagged(true);
    }
}

void Board::handleReveal(Tile* tile){
    tile->setIsRevealed(true);
    setSpriteText(tile->getSprite(), revealedTile);
    if(tile->getIsMine()){
        endGame();
    }else{
        remainingSafe-=1;
        if(remainingSafe <= 0){
            winGame();
        }
        if(tile->getAdjMines() == 0){
            vector<Tile*> * adjTiles = tile->getAdjTiles();
            int size = adjTiles->size();
            for(int i = 0; i < size; i++){
                Tile * adjTile = adjTiles->at(i);
                if(!adjTile->getIsRevealed()) {
                    handleReveal(adjTile);
                }
            }
        }
    }
}

void Board::endGame() {
    lostGame = true;
    debugMode = false;
    setSpriteText(&faceSprite, loseFace);
}

void Board::winGame(){
    wonGame = true;
    debugMode = false;
    setSpriteText(&faceSprite, winFace);
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            Tile * tile = tiles[i][j];
            if(tile->getIsRevealed()){
                tile->setIsFlagged(false);
            }else{
                tile->setIsFlagged(true);
            }
        }
    }
}

