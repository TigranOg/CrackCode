//
//  UserInfoManager.cpp
//  CrackCode
//
//  Created by Olga on 20.03.13.
//
//

#include "UserInfoManager.h"
#include "CodeChecker.h"
#include <sstream>

void UserInfoManager::saveLevelInfo() {
    std::stringstream timeKey;
    timeKey << "time-" << CodeChecker::currentState.level;
    CCUserDefault::sharedUserDefault()->setIntegerForKey(timeKey.str().c_str(), CodeChecker::currentState.time);
    std::stringstream codeKey;
    codeKey << "code-" << CodeChecker::currentState.level;
    CCUserDefault::sharedUserDefault()->setStringForKey(codeKey.str().c_str(), CodeChecker::currentState.code);
    int i = 0;
    for (std::list<Attempt>::iterator it = CodeChecker::attempts.begin(); it != CodeChecker::attempts.end(); ++it) {
        Attempt a = *it;
        std::stringstream attemptKey;
        attemptKey << "attempt-" << CodeChecker::currentState.level << "-" << i;
        std::stringstream resultKey;
        resultKey << "results-" << CodeChecker::currentState.level << "-" << i;
        CCUserDefault::sharedUserDefault()->setStringForKey(attemptKey.str().c_str(), a.attempt);
        CCUserDefault::sharedUserDefault()->setStringForKey(resultKey.str().c_str(), a.results);
        i++;
    }
    
    for (; ; i++) {
        std::stringstream attemptKey;
        attemptKey << "attempt-" << CodeChecker::currentState.level << "-" << i;
        std::string attempt = CCUserDefault::sharedUserDefault()->getStringForKey(attemptKey.str().c_str());
        if (attempt == "") {
            break;
        }
        CCUserDefault::sharedUserDefault()->setStringForKey(attemptKey.str().c_str(), "");
        std::stringstream resultKey;
        resultKey << "results-" << CodeChecker::currentState.level << "-" << i;
        CCUserDefault::sharedUserDefault()->setStringForKey(resultKey.str().c_str(), "");
    }
    CCUserDefault::sharedUserDefault()->flush();
}

void UserInfoManager::loadLevelInfo(int level) {
    CodeChecker::currentState.level =  level;
    LevelParams params = CodeChecker::levels[CodeChecker::currentState.level];
    CodeChecker::levelParams = CodeChecker::levels[CodeChecker::currentState.level];
    std::stringstream timeKey;
    timeKey << "time-" << level;
    CodeChecker::currentState.time = CCUserDefault::sharedUserDefault()->getIntegerForKey(timeKey.str().c_str(), 0);
    std::stringstream codeKey;
    codeKey << "code-" << level;
    CodeChecker::currentState.code = CCUserDefault::sharedUserDefault()->getStringForKey(codeKey.str().c_str());
    
    CodeChecker::attempts.clear();
    for (int i=0; ; i++) {
        std::stringstream attemptKey;
        attemptKey << "attempt-" << level << "-" << i;
        Attempt a;
        a.attempt = CCUserDefault::sharedUserDefault()->getStringForKey(attemptKey.str().c_str());
        if (a.attempt == "") {
            break;
        }
        std::stringstream resultKey;
        resultKey << "results-" << level << "-" << i;
        a.results = CCUserDefault::sharedUserDefault()->getStringForKey(resultKey.str().c_str());
        CodeChecker::attempts.push_back(a);
    }
}
