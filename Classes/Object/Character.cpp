//
//  Character.cpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#include "Character.h"
#include "GameConfig.h"

USING_NS_CC;

Character::~Character()
{
    
}

Character::Character()
{
    _width = 0;
    _height = 0;
    _state = State::kRun;
    _veloctiy = Vec2::ZERO;
    _accel = Vec2(0, ACCEL_FALLING_FREE);
}

Character* Character::create()
{
    Character* character = new Character();
    if (character != nullptr && character->init())
    {
        character->autorelease();
        return character;
    }
    CC_SAFE_DELETE(character);
    return nullptr;
}

bool Character::init()
{
    if (!Sprite::initWithFile("Character.png")) {
        return false;
    }
    return true;
}

void Character::reset()
{
    _veloctiy = Vec2::ZERO;
    _state = State::kRun;
    this->setPosition(POSITION_CHARACTER);
}

void Character::update(float dt)
{
    _veloctiy.x += _accel.x * dt;
    _veloctiy.y += _accel.y * dt;
    float disX = CONVERT_METER_TO_PIXEL(_veloctiy.x * dt);
    float disY = CONVERT_METER_TO_PIXEL(_veloctiy.y * dt);
    float posX = this->getPositionX() + disX;
    float posY = this->getPositionY() + disY;
    posY = (posY > GROUND_HEGIHT) ? posY : GROUND_HEGIHT;
    this->setPosition(Vec2(posX, posY));
    
    if(_state == State::kJump && getPositionY() <= GROUND_HEGIHT)
    {
        _state = State::kRun;
        _veloctiy.y = 0;
    }
}

void Character::jump()
{
    if (_state == State::kRun) {
        _state = State::kJump;
        _veloctiy.y = JUMP_CHARACTER;
    }
}

cocos2d::Rect Character::getBounding()
{
    float x = this->getPositionX() - _width * 0.5f;
    float y = this->getPositionY();
    return  Rect(x, y, _width ,_height);
}
