//
//  Character.hpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

class Character : public cocos2d::Sprite
{
public:
    enum State
    {
        kRun,
        kJump
    };
private:
    float _height, _width;
    State _state;
    cocos2d::Vec2 _veloctiy;
    cocos2d::Vec2 _accel;
public:
    ~Character();
    Character();
    
    static Character* create();
    
    virtual bool init() override;
    void reset();
    virtual void update(float dt) override;
    
    void jump();
    
    cocos2d::Rect getBounding();
};

#endif /* __OBSTACKLE_H__ */
