//
//  Board.hpp
//  BoggleSolver
//
//  Created by Ryan Heidema on 6/5/20.
//  Copyright © 2020 Ryan Heidema. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <iostream>
#include <vector>
#include "Solutions.hpp"
#include "Word.hpp"
#include "Dictionary.hpp"

// ---------------------------------------------------------------------------------------------------------------
//                                                  Board Class
// ---------------------------------------------------------------------------------------------------------------

class Board{
    
private:
    unsigned short minWordSize;
    std::vector<std::vector<char>> letters;
    
    // Recursive helper
    void SolveHelper(Dictionary &dict, Solutions &solns, int row, int col, std::string current);
    
public:
    // Constructor
    Board(unsigned short min_in, std::vector<char> letters_in);
    
    // Solves the game and returns the solutions
    Solutions Solve();
    
};

#endif /* Board_hpp */
