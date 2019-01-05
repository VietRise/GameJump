//
//  InterfacePopup.hpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#ifndef InterfacePopup_hpp
#define InterfacePopup_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class InterfacePopup : public cocos2d::LayerColor
{
protected:
    cocos2d::Size _screenSize;
    cocos2d::Color4B _color;
    GLfloat _width;
    GLfloat _height;
    
    cocos2d::ui::Layout* _layoutRoot;

public:
    virtual ~InterfacePopup();
    InterfacePopup();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void open();
    virtual void close();
    
    cocos2d::Color4B getColor();
    void setColor(cocos2d::Color4B color);
    
    // Event callback touch
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    virtual void onKeyBack();
};

#endif /* InterfacePopup_hpp */
