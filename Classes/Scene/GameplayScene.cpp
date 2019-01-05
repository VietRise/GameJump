//
//  GamePlayScene.cpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#include "GameplayScene.h"
#include "PausePopup.h"
#include "GameOverPopup.h"
#include "GameConfig.h"
#include "UserData.h"
#include "Utilities.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

GameplayScene::~GameplayScene()
{
    
}

GameplayScene::GameplayScene()
{
    _worldGame = nullptr;
    _score = 0;
    
    this->setTouchEnabled(true);
    this->setKeypadEnabled(true);
    cocos2d::EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameplayScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameplayScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameplayScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameplayScene::onTouchCancelled, this);
    touchListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

cocos2d::Scene* GameplayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameplayScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameplayScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    this->initScreen();
    this->resetGame();
    return true;
}

void GameplayScene::initScreen()
{
    _screenSize = Director::getInstance()->getWinSize();
    
    // Init world game
    _worldGame = WorldGame::create(this);
    this->addChild(_worldGame);
    
    // Init ui
    // -- Label score
    _lableScore = Text::create("0", "Marker Felt.ttf", 24);
    _lableScore->setPosition(Vec2(_screenSize.width * 0.5f, _screenSize.height * 0.85f));
    this->addChild(_lableScore);
    
    // -- Button pause
    _btnPause = Button::create("btnPauseNormal.png", "btnPausePress.png", "btnPausePress.png", TextureResType::LOCAL);
    _btnPause->setPosition(Vec2(_screenSize.width - _btnPause->getContentSize().width*0.5f - 10, _screenSize.height - _btnPause->getContentSize().height*0.5f - 10));
    _btnPause->addClickEventListener(CC_CALLBACK_1(GameplayScene::onButtonClick, this));
    this->addChild(_btnPause);
    
    // -- Lable start game
    _lableStartGame = Text::create("Touch on Screen to start Game", "Marker Felt.ttf", 60);
    _lableStartGame->setVisible(false);
    _lableStartGame->setPosition(Vec2(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(_lableStartGame);
}

void GameplayScene::onEnter()
{
    Layer::onEnter();
}

void GameplayScene::onExit()
{
    Layer::onExit();
}

// Event callback touch
bool GameplayScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    _worldGame->touchOnScreen();
    return true;
}

void GameplayScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}
void GameplayScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void GameplayScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

// Reset
void GameplayScene::resetGame()
{
    _score = 0;
    _lableScore->setString("0");
    _lableStartGame->setVisible(true);
    _worldGame->resetGame();
}

// Start
void GameplayScene::startGame()
{
    _lableStartGame->setVisible(false);
}

// Pause
void GameplayScene::pauseGame()
{
    _worldGame->pauseGame();
}

// Resume
void GameplayScene::resumeGame()
{
    _worldGame->resumeGame();
}

// Game over
void GameplayScene::gameOver()
{
    // Show popup game over
    GameOverPopup* gameOverPopup = GameOverPopup::create();
    gameOverPopup->setCallback(PLAYAGAIN_CALLBACK(GameplayScene::resetGame, this));
    gameOverPopup->setScore(_score);
    this->addChild(gameOverPopup);
    gameOverPopup->open();
    // Save best score
    if(_score > UserData::getInstance()->getBestScore())
    {
        UserData::getInstance()->setBestScore(_score);
        // post to leaderboard
        Utilities::submitToLeaderBoard(URL_LEADERBOARD, "User", _score);
    }
}

// Increase score
void GameplayScene::increaseSocre()
{
    _score += SCORE_PASSED_OBSTACLE;
    _lableScore->setString(StringUtils::format("%d", _score));
}

void GameplayScene::onButtonClick(cocos2d::Ref* pSender)
{
    if(pSender == _btnPause)
    {
        this->pauseGame();
        // Show popup pause game
        PausePopup* pausePopup = PausePopup::create();
        pausePopup->setCallback(RESUME_CALLBACK(GameplayScene::resumeGame, this));
        this->addChild(pausePopup);
        pausePopup->open();
    }
}
