//
//  GameOverPopup.hpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#ifndef GameOverPopup_hpp
#define GameOverPopup_hpp

#include "InterfacePopup.h"

typedef std::function<void()> PlayAgainCallBack;
#define PLAYAGAIN_CALLBACK(_SELECTOR, _TARGET) std::bind(&_SELECTOR, _TARGET)

class GameOverPopup : public InterfacePopup
{
private:
    cocos2d::ui::ImageView* _bg;
    cocos2d::ui::Text* _title;
    cocos2d::ui::Text* _score;
    cocos2d::ui::Button* _btnPlayAgain;
    cocos2d::ui::Button* _btnQuit;
    
    PlayAgainCallBack _callback;
public:
    ~GameOverPopup();
    GameOverPopup();
    CREATE_FUNC(GameOverPopup);
    void setCallback(PlayAgainCallBack callback);
    void setScore(int score);
    virtual bool init() override;
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    void onButtonClick(cocos2d::Ref* pSender);
};

#endif /* GameOverPopup_hpp */
