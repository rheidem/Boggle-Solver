//
//  Solutions.hpp
//  BoggleSolver
//
//  Created by Ryan Heidema on 6/5/20.
//  Copyright © 2020 Ryan Heidema. All rights reserved.
//

#ifndef Solutions_hpp
#define Solutions_hpp

#include <iostream>
#include <vector>
#include <set>
#include "Word.hpp"

// ---------------------------------------------------------------------------------------------------------------
//                                              Solutions Class
// ---------------------------------------------------------------------------------------------------------------

class Solutions {
    
private:
    struct Comp {
        // TODO: fix warnings
        bool operator()(Word const& w1, Word const& w2) {
            if(w1.getScore() != w2.getScore()) {
                return (w1.getScore() < w2.getScore());
            }
            else {
                return (w1.getText() < w2.getText());
            }
        }
    };
    
    unsigned short totalScore;
    std::set<Word, Comp> wordsSet;

    
public:
    // Default constructor, sets totalScore to 0
    Solutions();
    
    unsigned short getTotalScore() const;
    
    // Adds a new word into wordsList and updates totalScore
    void Add(std::string text);
    
    // Returns true if wordsList contains the string text
    bool Contains(std::string text);
    
    // Sort the wordsList according to Comp c and print to cout
    void Print();
    
};

#endif /* Solutions_hpp */
