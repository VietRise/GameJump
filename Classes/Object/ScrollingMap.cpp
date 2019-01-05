//
//  ScrollingMap.cpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#include "ScrollingMap.h"
#include "Utilities.h"
#include "GameConfig.h"

USING_NS_CC;
using namespace std;

float ScrollingMap::WIDTH_MAP = 1136.0f;
float ScrollingMap::HEIGHT_MAP = 640.0f;
int ScrollingMap::BUFFER_MAP = 3;

ScrollingMap::~ScrollingMap()
{
    CC_SAFE_DELETE(_bufferMap);
}

ScrollingMap::ScrollingMap()
{
    _bufferMap = new Node*[BUFFER_MAP];
    for (int i = 0; i < BUFFER_MAP; i++)
    {
        _bufferMap[i] = nullptr;
    }
    _listObstacleMap = new std::vector<Obstacle*>[BUFFER_MAP];
}

std::vector<Obstacle*>* ScrollingMap::getListObstacleMap()
{
    return _listObstacleMap;
}

ScrollingMap* ScrollingMap::create()
{
    ScrollingMap* scrollingMap = new ScrollingMap();
    if (scrollingMap != nullptr && scrollingMap->init()) {
        scrollingMap->autorelease();
        return scrollingMap;
    }
    CC_SAFE_DELETE(scrollingMap);
    return nullptr;
}

bool ScrollingMap::init()
{
    if (!Node::init()) {
        return false;
    }
    
    for (int i = 0; i < BUFFER_MAP; i++)
    {
        Node* map = Node::create();
        map->setPosition(Vec2(i * WIDTH_MAP, 0));
        _bufferMap[i] = map;
        this->addChild(map);
    }
    
    return true;
}

void ScrollingMap::reset()
{
    // Reset position and clear obstacle of each buffer map
    for (int i = 0; i < BUFFER_MAP; i++)
    {
        Node* map = _bufferMap[i];
        map->setPosition(Vec2(i * WIDTH_MAP, 0));
        
        map->removeAllChildren();
        _listObstacleMap[i].clear();
    }
    // Reset position map
    this->setPosition(Vec2::ZERO);
}

void ScrollingMap::update(float dt)
{
    // Auto scoll this map
    float disX = CONVERT_METER_TO_PIXEL(VELOC_CHARACTER) * dt;
    this->setPosition(this->getPosition() - Vec2(disX, 0));
    
    // Update each of child map
    for (int i = 0; i < BUFFER_MAP; i++) {
        Node* map = _bufferMap[i];
        Vec2 posWorld = this->convertToWorldSpace(map->getPosition());
        if (posWorld.x < -WIDTH_MAP)
        {
            // Set position map to end of buffer
            map->setPosition(map->getPosition() + Vec2(3 * WIDTH_MAP, 0));
            // Generate object
            this->generateObstacle(i);
        }
    }
}

void ScrollingMap::generateObstacle(int index)
{
    _listObstacleMap[index].clear();
    _bufferMap[index]->removeAllChildren();
    
    int numberObstacle = Utilities::randomInt(2, 3);
    for (int i = 0; i < numberObstacle; i++) {
        int widthObstacle = Utilities::randomInt(60, 100);
        Vec2 position = Vec2(i * (WIDTH_MAP/numberObstacle) +  Utilities::randomInt(-100, 100), GROUND_HEGIHT + widthObstacle * 0.5f);
        Obstacle* obstacle = Obstacle::create(widthObstacle);
        obstacle->setPosition(position);
        _bufferMap[index]->addChild(obstacle);
        _listObstacleMap[index].push_back(obstacle);
    }
}
