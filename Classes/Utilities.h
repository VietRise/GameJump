//
//  Utilities.h
//  GameJump
//
//  Created by MacBook on 1/5/19.
//

#ifndef Utilities_h
#define Utilities_h

#include "cocos2d.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"

class Utilities
{
public:
    static int randomInt(int min, int max);
    static void submitToLeaderBoard(std::string url, std::string userName, int score);
};


#endif /* Utilities_h */
