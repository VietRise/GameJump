//
//  PausePopup.cpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#include "PausePopup.h"
#include "MenuScene.h"
#include "GameConfig.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;

PausePopup::~PausePopup()
{
    
}

PausePopup::PausePopup()
{
    _callback = nullptr;
}

void PausePopup::setCallback(ResumeCallBack callback)
{
    _callback = callback;
}

bool PausePopup::init()
{
    if (!InterfacePopup::init()) {
        return false;
    }
    
    // BG
    _bg = cocos2d::ui::ImageView::create("board.png", cocos2d::ui::Widget::TextureResType::LOCAL);
    _bg->setPosition(Vec2(_layoutRoot->getContentSize().width * 0.5f, _layoutRoot->getContentSize().height * 0.5f));
    _bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _bg->setScale9Enabled(true);
    _bg->setCapInsets(rectCapHudBox);
    _bg->setContentSize(Size(600, 300));
    _layoutRoot->addChild(_bg);
    
    // Text Title
    _title = Text::create("Pause Game", "Marker Felt.ttf", 60);
    _title->setPosition(Vec2(_bg->getContentSize().width * 0.5f, _bg->getContentSize().height * 0.8f));
    _bg->addChild(_title);
    
    // Button Resume
    _btnResume = Button::create("board.png", "board.png", "board.png", TextureResType::LOCAL);
    _btnResume->setScale9Enabled(true);
    _btnResume->setContentSize(Size(250, 100));
    _btnResume->setTitleText("Resume");
    _btnResume->setTitleFontSize(30);
    _btnResume->setPosition(Vec2(_bg->getContentSize().width * 0.35f, _bg->getContentSize().height * 0.3f));
    _btnResume->addClickEventListener(CC_CALLBACK_1(PausePopup::onButtonClick, this));
    _bg->addChild(_btnResume);
    
    // Button Quit
    _btnQuit = Button::create("board.png", "board.png", "board.png", TextureResType::LOCAL);
    _btnQuit->setScale9Enabled(true);
    _btnQuit->setContentSize(Size(250, 100));
    _btnQuit->setTitleText("Quit");
    _btnQuit->setTitleFontSize(30);
    _btnQuit->setPosition(Vec2(_bg->getContentSize().width * 0.65f, _bg->getContentSize().height * 0.3f));
    _btnQuit->addClickEventListener(CC_CALLBACK_1(PausePopup::onButtonClick, this));
    _bg->addChild(_btnQuit);
    
    return true;
}

bool PausePopup::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Vec2 location = touch->getLocation();
    if (!_bg->getBoundingBox().containsPoint(location))
    {
        if (_callback) {
            _callback();
        }
        this->close();
    }
    return true;
}

void PausePopup::onButtonClick(cocos2d::Ref* pSender)
{
    if (pSender == _btnResume)
    {
        if (_callback) {
            _callback();
        }
        this->close();
    }
    else if (pSender == _btnQuit)
    {
        // Change to Menu Scene
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MenuScene::createScene()));
    }
}
