//
//  GamePlayScene.h
//  GameJump
//
//  Created by MacBook on 1/5/19.
//

#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "WorldGame.h"

class GameplayScene : public cocos2d::Layer
{
private:
    WorldGame* _worldGame;
    
    // UI
    cocos2d::Size _screenSize;
    cocos2d::ui::Text* _lableStartGame;
    cocos2d::ui::Text* _lableScore;
    cocos2d::ui::Button* _btnPause;
    
public:
    CC_SYNTHESIZE(int, _score, Score);
    
    ~GameplayScene();
    GameplayScene();
    
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameplayScene);
    
    virtual bool init();
    void initScreen();
    virtual void onEnter();
    virtual void onExit();
    
    // Event callback touch
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    // Reset
    void resetGame();
    // Start
    void startGame();
    // Pause
    void pauseGame();
    // Resume
    void resumeGame();
    // Game over
    void gameOver();
    // Increase score
    void increaseSocre();
    
    void onButtonClick(cocos2d::Ref* pSender);
};

#endif /* __GAMEPLAY_SCENE_H__ */
