#include "MenuScene.h"
#include "GameplayScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // Label title of scene
    auto label = Label::createWithTTF("Menu Scene", "fonts/Marker Felt.ttf", 60);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // Label Start
    auto labelStart = Label::createWithTTF("Start", "Marker Felt.ttf", 45);
    _menuItemLabelStart = MenuItemLabel::create(labelStart,CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
    _menuItemLabelStart->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _menuItemLabelStart->setPosition(Vec2(visibleSize.width * 0.5f ,visibleSize.height * 0.6f));
    
    // Label Exit
    auto labelExit = Label::createWithTTF("Exit", "Marker Felt.ttf", 45);
    _menuItemLabelExit = MenuItemLabel::create(labelExit,CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
    _menuItemLabelExit->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _menuItemLabelExit->setPosition(Vec2(visibleSize.width * 0.5f ,visibleSize.height * 0.4f));
    
    // Create menu
    auto menu = Menu::create(_menuItemLabelStart, _menuItemLabelExit, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    if (pSender == _menuItemLabelStart)
    {
        // Change to Gameplay Scene
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameplayScene::createScene()));
    }
    else if (pSender == _menuItemLabelExit)
    {
        Director::getInstance()->end();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
}
