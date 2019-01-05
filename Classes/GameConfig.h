//
//  GameConfig.h
//  GameJump
//
//  Created by MacBook on 1/5/19.
//

#ifndef GameConfig_h
#define GameConfig_h

#include "cocos2d.h"

#define ACCEL_FALLING_FREE -9.8f // Meter
#define VELOC_CHARACTER 2.8f // Meter
#define JUMP_CHARACTER 5.4f // Meter
#define GROUND_HEGIHT 200.0f // Pixel
#define POSITION_CHARACTER cocos2d::Vec2(100.0f, GROUND_HEGIHT) // Pixel
#define CONVERT_METER_TO_PIXEL(m) m * 100.0f
#define rectCapHudBox cocos2d::Rect(10, 10, 10, 10)
#define SCORE_PASSED_OBSTACLE 10
#define USERDEFAULT_FILEEXIST "FileExist"
#define BEST_SCORE "BestScore"
#define URL_LEADERBOARD "http://server/leaderboard.php"

#endif /* GameConfig_h */
