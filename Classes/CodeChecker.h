//
//  CodeChecker.h
//  CrackCode
//
//  Created by Olga on 11.02.13.
//
//

#ifndef __CrackCode__CodeChecker__
#define __CrackCode__CodeChecker__

#include <iostream>
#include "cocos2d.h"

typedef struct {
    int length;
    int minRepeats;
    int maxRepeats;
    std::string possibleSymbols;
} LevelParams;

typedef struct {
    std::string attempt;
    std::string results;
    
} Attempt;

typedef struct {
    int level;
    std::string code;
    int time;
} CurrentState;

class CodeChecker
{
public:
    static std::string checkCode(std::string attempt, std::string code);

    static std::string generateCode(int length, int minRepeats, int maxRepeats,  std::string possibleSymbols);
    
    static LevelParams levelParams;
    
    static std::list<Attempt> attempts;
    
    static std::map<int, LevelParams> initLevels();
    
    static std::map<int, LevelParams> levels;

    static CurrentState currentState;
    
    static int getPositionOfSymbol(char c);
};

#endif /* defined(__CrackCode__CodeChecker__) */
