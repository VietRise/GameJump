//
//  InterfacePopup.cpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#include "InterfacePopup.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

InterfacePopup::~InterfacePopup()
{
    
}

InterfacePopup::InterfacePopup()
{
    _screenSize = Director::getInstance()->getWinSize();
    _color = Color4B(0, 0, 0, 150);
    _width = _screenSize.width;
    _height = _screenSize.height;
    
    this->setTouchEnabled(true);
    this->setKeyboardEnabled(true);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(InterfacePopup::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(InterfacePopup::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(InterfacePopup::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(InterfacePopup::onTouchCancelled, this);
    touchListener->setSwallowTouches(true);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool InterfacePopup::init()
{
    if (!LayerColor::initWithColor(_color, _width, _height))
    {
        return false;
    }
    
    this->_layoutRoot = cocos2d::ui::Layout::create();
    _layoutRoot->setContentSize(_screenSize);
    _layoutRoot->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _layoutRoot->setPosition(_screenSize * 0.5f);
    _layoutRoot->setCascadeColorEnabled(true);
    _layoutRoot->setCascadeOpacityEnabled(true);
    this->addChild(_layoutRoot);
    
    return true;
}

void InterfacePopup::onEnter()
{
    LayerColor::onEnter();
    this->open();
}

void InterfacePopup::onExit()
{
    LayerColor::onExit();
}

void InterfacePopup::open()
{
    auto actScaleUp = EaseBackOut::create(ScaleTo::create(0.2f, 1.0f));
    _layoutRoot->setOpacity(0);
    _layoutRoot->setScale(0.5f);
    auto actOpen = Spawn::create(actScaleUp, cocos2d::FadeIn::create(0.1f), nullptr);
    _layoutRoot->runAction(actOpen);
}

void InterfacePopup::close()
{
    this->removeFromParent();
}

cocos2d::Color4B InterfacePopup::getColor()
{
    return _color;
}

void InterfacePopup::setColor(cocos2d::Color4B color)
{
    if (_color != color)
    {
        _color = color;
        this->initWithColor(_color, _width, _height);
    }
}

// Event callback touch
bool InterfacePopup::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}

void InterfacePopup::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void InterfacePopup::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void InterfacePopup::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void InterfacePopup::onKeyBack()
{
    this->close();
}
