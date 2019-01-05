//
//  Utilities.cpp
//  GameJump-mobile
//
//  Created by MacBook on 1/5/19.
//

#include "Utilities.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::network;

int Utilities::randomInt(int min, int max)
{
    if (min >= max)
    {
        return min;
    }
    return std::rand() % (max - min) + min;
}

void Utilities::submitToLeaderBoard(std::string url, std::string userName, int score)
{
    HttpRequest* request = new HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::POST);
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json; charset=utf-8");
    request->setHeaders(headers);
    std::string postData = StringUtils::format("name=%s&score=%d", userName.c_str(), score);
    request->setRequestData(postData.c_str(), postData.length());
    request->setResponseCallback([=](HttpClient* client, HttpResponse* response)
                                 {
                                     long statusCode = response->getResponseCode();
                                     if (statusCode == 404)
                                     {
                                         CCLOG("Username not found (user has not registered with the leaderboard service)");
                                     }
                                     else if (statusCode == 405)
                                     {
                                         CCLOG("Invalid Username supplied");
                                     }
                                     else if (statusCode == 200)
                                     {
                                         CCLOG("Ok");
                                     }
                                 });
    HttpClient::getInstance()->send(request);
    request->release();
}
