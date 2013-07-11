//
//  CodeChecker.cpp
//  CrackCode
//
//  Created by Olga on 11.02.13.
//
//

#include "CodeChecker.h"
#include <time.h>

#define POSSIBLE_SYMBOLS    "0123456789"

std::map<int, LevelParams> CodeChecker::levels;
LevelParams CodeChecker::levelParams;
std::list<Attempt> CodeChecker::attempts;
CurrentState CodeChecker::currentState;

std::string CodeChecker::checkCode(std::string attempt, std::string code) {
    int* result = new int[2];
    std::string resultStr;

    if (code == attempt) {
        return "WIN";
    }
    
    result[0] = 0; // bulls
    result[1] = 0; // cows
    
    for (int i = 0; i < code.length(); i++) {
        for (int j = 0; j < attempt.length(); j++) {
            if (attempt[j] == code[i]) {
                if (i == j) {
                    result[0]++;
                    code[i] = '\n';
                    attempt[j] = '\r';
                    break;
                } else {
                    if ((j > i) && (attempt[j] == code[j])) {
                        result[0]++;
                        code[j] = '\n';
                        attempt[j] = '\r';
                        continue;
                    }
                    if ((j < i) && (attempt[i] == code[i])) {
                        result[0]++;
                        code[i] = '\n';
                        attempt[i] = '\r';
                        continue;
                    }
                    result[1]++;
                    code[i] = '\n';
                    attempt[j] = '\r';
                    break;
                }
            }
        }
    }
    for (int i=0; i<2; i++) {
        char c = '0' + result[i];
        resultStr.push_back(c);
    }
    return resultStr;
}

std::string CodeChecker::generateCode(int length, int minRepeats, int maxRepeats,  std::string possibleSymbols) {
    if ((minRepeats > maxRepeats) || ((int)(length - possibleSymbols.length()) > maxRepeats) ||
                (minRepeats > length) || (maxRepeats < 1)) {
        return "";
    }
    srand(time(NULL));
    std::string code = "";
    int repeats = 1;
    for(int i = 0; i < length; i++) {
        char c = possibleSymbols[rand() % possibleSymbols.length()];
        if (repeats == maxRepeats) {
            while (code.find(c) != std::string::npos) {
                c = possibleSymbols[rand() % possibleSymbols.length()];
            }
        } else {
            if (code.find(c) != std::string::npos) {
                repeats++;
            }
        }
        code.push_back(c);
    }
    while (minRepeats > repeats) {
        int i = rand() % code.length();
        char c = code[i];
        int j = rand() % code.length();
        while (i == j) {
            j = rand() % code.length();
        }
        code[j] = c;
        repeats++;
    }
    return code;
}

std::map<int,LevelParams> CodeChecker::initLevels() {
    CodeChecker::levels.clear();
    LevelParams params1;
    params1.length = 3;
    params1.minRepeats = 1;
    params1.maxRepeats = 1;
    params1.possibleSymbols = POSSIBLE_SYMBOLS;
    levels[1] = params1;
    
    LevelParams params2;
    params2.length = 4;
    params2.minRepeats = 1;
    params2.maxRepeats = 1;
    params2.possibleSymbols = POSSIBLE_SYMBOLS;
    levels[2] = params2;
    
    LevelParams params3;
    params3.length = 5;
    params3.minRepeats = 1;
    params3.maxRepeats = 1;
    params3.possibleSymbols = POSSIBLE_SYMBOLS;
    levels[3] = params3;
    
    LevelParams params4;
    params4.length = 5;
    params4.minRepeats = 2;
    params4.maxRepeats = 2;
    params4.possibleSymbols = POSSIBLE_SYMBOLS;
    levels[4] = params4;
    return levels;
}

int CodeChecker::getPositionOfSymbol(char c) {
    for (int i = 0; i < CodeChecker::levelParams.possibleSymbols.size(); i++) {
        if (c == CodeChecker::levelParams.possibleSymbols[i]) {
            return i;
        }
    }
    return 0;
}

