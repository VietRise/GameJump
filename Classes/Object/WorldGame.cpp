//
//  WorldGame.cpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#include "WorldGame.h"
#include "GameConfig.h"
#include "GameplayScene.h"

USING_NS_CC;
using namespace std;

WorldGame::~WorldGame()
{
    
}

WorldGame::WorldGame(GameplayScene* gameplayScene)
{
    _gameplayScene = gameplayScene;
    _state = State::kReady;
    _mainCharacter = nullptr;
    _scrollingMap = nullptr;
}

WorldGame* WorldGame::create(GameplayScene* gameplayScene)
{
    WorldGame* worldGame = new WorldGame(gameplayScene);
    if (worldGame != nullptr && worldGame->init()) {
        worldGame->autorelease();
        return worldGame;
    }
    CC_SAFE_DELETE(worldGame);
    return nullptr;
}

bool WorldGame::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // Create ground
    Size screenSize = Director::getInstance()->getWinSize();
    _ground = Sprite::create("Ground.png");
    float scaleX = screenSize.width/_ground->getContentSize().width;
    float scaleY = GROUND_HEGIHT/_ground->getContentSize().height;
    _ground->setAnchorPoint(Vec2(0.5f, 0.0f));
    _ground->setScale(scaleX, scaleY);
    _ground->setPosition(Vec2(screenSize.width * 0.5f, 0));
    this->addChild(_ground);
    
    // Create main character
    _mainCharacter = Character::create();
    _mainCharacter->setAnchorPoint(Vec2(0.5f, 0.0f));
    _mainCharacter->reset();
    this->addChild(_mainCharacter);
    
    // Create scrolling map which contain obstacle
    _scrollingMap = ScrollingMap::create();
    _scrollingMap->reset();
    this->addChild(_scrollingMap);
    
    return true;
}

void WorldGame::resetGame()
{
    std::srand ((unsigned)time(nullptr));
    _state = State::kReady;
    _mainCharacter->reset();
    _scrollingMap->reset();
    // Run schedule update
    this->scheduleUpdate();
}

void WorldGame::startGame()
{
    if(_state == State::kReady)
    {
        _gameplayScene->startGame();
        _state = State::kPlaying;
    }
}

void WorldGame::pauseGame()
{
    if(_state == State::kPlaying)
    {
        _state = State::kPause;
    }
}

void WorldGame::resumeGame()
{
    if(_state == State::kPause)
    {
        _state = State::kPlaying;
    }
}

void WorldGame::touchOnScreen()
{
    if (_state == State::kReady)
    {
        this->startGame();
    }
    else if (_state == State::kPlaying)
    {
        this->controlCharacterJump();
    }
}
void WorldGame::update(float dt)
{
    if (_state == State::kPlaying) {
        _mainCharacter->update(dt);
        _scrollingMap->update(dt);
        this->checkCollision();
    }
}

void WorldGame::controlCharacterJump()
{
    if (_state == State::kPlaying) {
        _mainCharacter->jump();
    }
}

void WorldGame::checkCollision()
{
    std::vector<Obstacle*>* listObstacleMap = _scrollingMap->getListObstacleMap();
    for (int i = 0; i < ScrollingMap::BUFFER_MAP; i++) {
        for (int j = 0; j < listObstacleMap[i].size(); j++) {
            // Check game over
            Obstacle* obstacle = listObstacleMap[i].at(j);
            if (_mainCharacter->getBounding().intersectsRect(obstacle->getBounding()))
            {
                this->gameOver();
            }
            // Check main character jump over obstacle
            if (!obstacle->getPassed()) {
                if (_mainCharacter->getPosition().x > obstacle->getPositionWorld().x + obstacle->getWidth()*0.5f) {
                    obstacle->setPassed(true);
                    _gameplayScene->increaseSocre();
                }
            }
        }
    }
}

void WorldGame::gameOver()
{
    if (_state == State::kPlaying) {
        _state = State::kGameOver;
        this->unscheduleUpdate();
        _gameplayScene->gameOver();
    }
}
