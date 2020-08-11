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
    
    // resize the 2D letters vector for a 4x4 board
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
} // Board::Board()


// Solves the game and returns the solutions
Solutions Board::Solve() {
    
    // Create a Dictionary and load in the words
    Dictionary d1(minWordSize);
    d1.Load(cin);
    
    Solutions s1;
    
    // For each square on the board, solve
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            SolveHelper(d1, s1, i, j, "");
        }
    }
    
    // return the solutions
    return s1;
} // Board::Solve()


// Recursive helper
void Board::SolveHelper(Dictionary &dict, Solutions &solns, int row, int col, std::string current) {
    if(dict.KeepGoing(current)) {
        
        // Get the new character and add on to the current path
        char newChar = letters[static_cast<size_t>(row)][static_cast<size_t>(col)];
        string newPath = current + newChar;
        
        if(newPath.length() >= minWordSize) {
            // If the word is in the Dictionary and not in the Solutions, add to Solutions
            if(dict.Contains(newPath) && !solns.Contains(newPath)) {
                solns.Add(newPath);
            }
        }
        
        // Check surrounding squares that have not yet been looked at
        for(int vert = -1; vert <= 1; vert++) {
            for(int hor = -1; hor <= 1; hor++) {
                if(row + vert >= 0 && row + vert < 4 && col + hor >= 0 && col + hor < 4 &&
                   !(vert == 0 && hor == 0) && letters[static_cast<size_t>(row + vert)][static_cast<size_t>(col + hor)] != '*') {
                    
                    // Put new letter in the solution path
                    letters[static_cast<size_t>(row)][static_cast<size_t>(col)] = '*';
                    
                    SolveHelper(dict, solns, row + vert, col + hor, newPath);
                    
                    // Effectively take new letter out of solution path
                    letters[static_cast<size_t>(row)][static_cast<size_t>(col)] = newChar;
                }
            }
        }
    }
} // Board::SolveHelper()
