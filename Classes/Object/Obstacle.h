//
//  Obstacle.hpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#ifndef __OBSTACKLE_H__
#define __OBSTACKLE_H__

#include "cocos2d.h"

class Obstacle : public cocos2d::Node
{
private:
    cocos2d::Sprite* _skin;

public:
    CC_SYNTHESIZE(float, _width, Width);
    CC_SYNTHESIZE(float, _height, Height);
    CC_SYNTHESIZE(bool, _passed, Passed);
    
    ~Obstacle();
    Obstacle(float width);
    
    static Obstacle* create(float width);
    
    virtual bool init();
    
    cocos2d::Rect getBounding();
    cocos2d::Vec2 getPositionWorld();
};

#endif /* __OBSTACKLE_H__ */
