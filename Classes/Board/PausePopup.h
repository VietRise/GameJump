//
//  PausePopup.hpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#ifndef PausePopup_hpp
#define PausePopup_hpp

#include "InterfacePopup.h"

typedef std::function<void()> ResumeCallBack;
#define RESUME_CALLBACK(_SELECTOR, _TARGET) std::bind(&_SELECTOR, _TARGET)

class PausePopup : public InterfacePopup
{
private:
    cocos2d::ui::ImageView* _bg;
    cocos2d::ui::Text* _title;
    cocos2d::ui::Button* _btnResume;
    cocos2d::ui::Button* _btnQuit;
    
    ResumeCallBack _callback;
public:
    ~PausePopup();
    PausePopup();
    CREATE_FUNC(PausePopup);
    void setCallback(ResumeCallBack callback);
    virtual bool init() override;
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
    void onButtonClick(cocos2d::Ref* pSender);
};

#endif /* PausePopup_hpp */
