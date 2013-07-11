//
//  UserInfoManager.h
//  CrackCode
//
//  Created by Olga on 20.03.13.
//
//

#ifndef __CrackCode__UserInfoManager__
#define __CrackCode__UserInfoManager__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class UserInfoManager
{
public:
    static void saveLevelInfo();
    static void loadLevelInfo(int level);
};
#endif /* defined(__CrackCode__UserInfoManager__) */
