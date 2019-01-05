//
//  WorldGame.hpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#ifndef WorldGame_hpp
#define WorldGame_hpp

#include "cocos2d.h"
#include "Character.h"
#include "ScrollingMap.h"

class GameplayScene;
class WorldGame : public cocos2d::Layer
{
public:
    enum State
    {
        kReady,
        kPlaying,
        kPause,
        kGameOver
    };
    
private:
    State _state;
    Character* _mainCharacter;
    ScrollingMap* _scrollingMap;
    cocos2d::Sprite* _ground;
    GameplayScene* _gameplayScene;
public:
    ~WorldGame();
    WorldGame(GameplayScene* gameplayScene);
    
    static WorldGame* create(GameplayScene* gameplayScene);
    virtual bool init() override;
    void resetGame();
    void startGame();
    void pauseGame();
    void resumeGame();
    void touchOnScreen();
    virtual void update(float dt) override;
    void controlCharacterJump();
    void checkCollision();
    void gameOver();
};

#endif /* WorldGame_hpp */
