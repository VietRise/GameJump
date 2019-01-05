//
//  UserData.hpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#ifndef UserData_hpp
#define UserData_hpp

#include "cocos2d.h"

class UserData
{
private:
    int _bestScore;
    
    UserData();
public:
    static UserData* _instance;
    ~UserData();
    
    static UserData* getInstance();
    static void destroyInstance();
    
    void setBestScore(int bestScore);
    int getBestScore();
    
private:
    void setIntegerForKey(const char* pKey, int value);
    int getIntegerForKey(const char* pKey);
    void encode(const char* pKey, std::string value);
    std::string decode(const char* pKey);
};

#endif /* UserData_hpp */
