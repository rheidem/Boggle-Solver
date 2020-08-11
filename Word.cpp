//
//  Word.cpp
//  BoggleSolver
//
//  Created by Ryan Heidema on 6/5/20.
//  Copyright © 2020 Ryan Heidema. All rights reserved.
//

#include "Word.hpp"

// ---------------------------------------------------------------------------------------------------------------
//                                                 Word Class
// ---------------------------------------------------------------------------------------------------------------

Word::Word(const std::string text_in)
: text(text_in) {
    size_t len = text.length();
    if(len < 5) {
        score = 1;
    }
    else if(len == 5) {
        score = 2;
    }
    else if(len == 6) {
        score = 3;
    }
    else if(len == 7) {
        score = 5;
    }
    else {
        score = 11;
    }
}

std::string Word::getText() const {
    return text;
}

unsigned short Word::getScore() const{
    return score;
}
