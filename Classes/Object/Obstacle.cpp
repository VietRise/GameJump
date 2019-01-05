//
//  Obstacle.cpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#include "Obstacle.h"

USING_NS_CC;

Obstacle::~Obstacle()
{
}

Obstacle::Obstacle(float width)
{
    _width = width;
    _height = width;
    _passed = false;
}

Obstacle* Obstacle::create(float width)
{
    Obstacle* obstacle = new Obstacle(width);
    if (obstacle != nullptr && obstacle->init())
    {
        obstacle->autorelease();
        return obstacle;
    }
    CC_SAFE_DELETE(obstacle);
    return nullptr;
}

bool Obstacle::init()
{
    if (!Node::init()) {
        return false;
    }
    
    _skin = Sprite::create("Obstacle.png");
    float scaleX  = _width/_skin->getContentSize().width;
    float scaleY  = _height/_skin->getContentSize().height;
    _skin->setScale(scaleX, scaleY);
    this->addChild(_skin);
    
    return true;
}

cocos2d::Rect Obstacle::getBounding()
{
    Vec2 posInWorld = this->getParent()->convertToWorldSpace(this->getPosition());
    float x = posInWorld.x - _width * 0.5f;
    float y = posInWorld.y - _height * 0.5f;
    return Rect(x, y, _width, _height);
}

cocos2d::Vec2 Obstacle::getPositionWorld()
{
     Vec2 posInWorld = this->getParent()->convertToWorldSpace(this->getPosition());
    return posInWorld;
}
