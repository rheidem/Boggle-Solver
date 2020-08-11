//
//  Solutions.cpp
//  BoggleSolver
//
//  Created by Ryan Heidema on 6/5/20.
//  Copyright © 2020 Ryan Heidema. All rights reserved.
//

#include "Solutions.hpp"
#include <vector>
#include <set>
#include <algorithm>
#include "Word.hpp"

using namespace std;

// ---------------------------------------------------------------------------------------------------------------
//                                              Solutions Class
// ---------------------------------------------------------------------------------------------------------------

Solutions::Solutions()
: totalScore(0) {}

unsigned short Solutions::getTotalScore() const {
    return totalScore;
}

// Adds a new word into wordsList and updates totalScore
void Solutions::Add(std::string text) {
    Word temp(text);
    wordsSet.insert(temp);
    totalScore += temp.getScore();
}

// Returns true if wordsList contains the string text
bool Solutions::Contains(std::string text) {
    if(wordsSet.find(Word(text)) != wordsSet.end()) {
        return true;
    }
    else {
        return false;
    }
}

// Sort the wordsList according to Comp c and print to cout
void Solutions::Print() {
    for (Word const& word : wordsSet) {
        if(word.getScore() == 1) {
            cout << word.getText() << ": " << word.getScore() << " point\n";
        }
        else {
            cout << word.getText() << ": " << word.getScore() << " points\n";
        }
    }
}
