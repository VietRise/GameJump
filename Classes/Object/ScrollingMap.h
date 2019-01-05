//
//  ScrollingMap.hpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#ifndef __SCROOLING_MAP_H__
#define __SCROOLING_MAP_H__

#include "cocos2d.h"
#include <vector>
#include "Obstacle.h"

class ScrollingMap : public cocos2d::Node
{
private:
    cocos2d::Node** _bufferMap;
    std::vector<Obstacle*>* _listObstacleMap;
public:
    static float WIDTH_MAP;
    static float HEIGHT_MAP;
    static int BUFFER_MAP;
    
    ~ScrollingMap();
    ScrollingMap();
    
    std::vector<Obstacle*>* getListObstacleMap();
    
    static ScrollingMap* create();
    virtual bool init() override;
    void reset();
    virtual void update(float dt) override;
    
private:
    void generateObstacle(int index);
};

#endif /* __SCROOLING_MAP_H__ */
