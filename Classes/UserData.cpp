//
//  UserData.cpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#include "UserData.h"
#include "GameConfig.h"

USING_NS_CC;
using namespace std;

UserData* UserData::_instance = nullptr;

UserData::~UserData()
{
    
}

UserData::UserData()
{
    if (!UserDefault::getInstance()->getBoolForKey(USERDEFAULT_FILEEXIST))
    {
        _bestScore = 0;
        this->setBestScore(_bestScore);
        UserDefault::getInstance()->setBoolForKey(USERDEFAULT_FILEEXIST, true);
    }
    else
    {
        _bestScore = this->getIntegerForKey(BEST_SCORE);
    }
}

UserData* UserData::getInstance()
{
    if (_instance == nullptr) {
        _instance = new UserData();
    }
    return _instance;
}

void UserData::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
}

void UserData::setBestScore(int bestScore)
{
    _bestScore = bestScore;
    this->setIntegerForKey(BEST_SCORE, _bestScore);
}

int UserData::getBestScore()
{
    return _bestScore;
}

void UserData::setIntegerForKey(const char* pKey, int value)
{
    char szName[50] = { 0 };
    sprintf(szName, "%i", value);
    string valueString = string(szName);
    encode(pKey, valueString);
}

int UserData::getIntegerForKey(const char* pKey)
{
    string valueString = decode(pKey);
    int value = atoi(valueString.c_str());
    return value;
}

void UserData::encode(const char* pKey, std::string value)
{
    char* valueEncode;
    base64Encode(reinterpret_cast<const unsigned char*>(value.c_str()), strlen(value.c_str()) + 1, &valueEncode);
    UserDefault::getInstance()->setStringForKey(pKey, valueEncode);
}

std::string UserData::decode(const char* pKey)
{
    string valueEncode = UserDefault::getInstance()->getStringForKey(pKey);
    unsigned char* value;
    base64Decode(reinterpret_cast<const unsigned char*>(valueEncode.c_str()), strlen(valueEncode.c_str()) + 1, &value);
    return string(reinterpret_cast<char*>(value));
}
