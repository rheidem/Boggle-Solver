//
//  Board.cpp
//  BoggleSolver
//
//  Created by Ryan Heidema on 6/5/20.
//  Copyright © 2020 Ryan Heidema. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Solutions.hpp"
#include "Word.hpp"
#include "Dictionary.hpp"
#include "Board.hpp"

using namespace std;

// ---------------------------------------------------------------------------------------------------------------
//                                                  Board Class
// ---------------------------------------------------------------------------------------------------------------

// Constructor
Board::Board(unsigned short min_in, std::vector<char> letters_in)
: minWordSize(min_in) {
    // resize the 2D letters vector
    letters.reserve(4);
    while(letters.size() < 4) {
        std::vector<char> temp(4,'.');
        letters.push_back(temp);
    }
    
    // fill in the letters vector with incoming letters
    size_t index = 0;
    for(size_t i = 0; i < 4; ++i) {
        for(size_t j = 0; j < 4; ++j) {
            letters[i][j] = letters_in[index++];
        }
    }
}

// Solves the game and returns the solutions
Solutions Board::Solve() {
    Dictionary d1(minWordSize);
    d1.Load(cin);
    
    Solutions s1;
    
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            SolveHelper(d1, s1, i, j, "");
        }
    }
    
    return s1;
}

// Recursive helper
void Board::SolveHelper(Dictionary &dict, Solutions &solns, int row, int col, std::string current) {
    if(dict.KeepGoing(current)) {
        char newChar = letters[row][col];
        string newPath = current + newChar;
        
        if(newPath.length() >= minWordSize) {
            if(dict.Contains(newPath) && !solns.Contains(newPath)) {
                solns.Add(newPath);
            }
        }
        
        for(int vert = -1; vert <= 1; vert++) {
            for(int hor = -1; hor <= 1; hor++) {
                if(row + vert >= 0 && row + vert < 4 &&
                   col + hor >= 0 && col + hor < 4 &&
                   !(vert == 0 && hor == 0) &&
                   letters[row + vert][col + hor] != '*') {
                    letters[row][col] = '*';
                    SolveHelper(dict, solns, row + vert, col + hor, newPath);
                    letters[row][col] = newChar;
                }
            }
        }
    }
}
