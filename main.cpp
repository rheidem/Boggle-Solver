//
//  main.cpp
//  BoggleSolver
//
//  Created by Ryan Heidema on 6/5/20.
//  Copyright © 2020 Ryan Heidema. All rights reserved.
//

#include "xcode_redirect.hpp"
#include <iostream>
#include <getopt.h>
#include <sstream>
#include "Dictionary.hpp"
#include "Board.hpp"
#include "Word.hpp"
#include "Solutions.hpp"
#include <vector>
#include <chrono>
#include <random>

using namespace std;


// ---------------------------------------------------------------------------------------------------------------
//                                                   Helpers
// ---------------------------------------------------------------------------------------------------------------

vector<char> generateBoard() {
    vector<char> board;
    board.reserve(16);  // 4x4 board
    
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> distribution(0,25);
    
    for(size_t i = 0; i < 16; ++i) {
        board.push_back(97 + distribution(generator));
    }
    
    return board;
}

void printBoard(const vector<char> &board) {
    for(size_t i = 0; i < board.size(); ++i) {
        cout << " " << board[i];
        if(i % 4 == 3) {
            cout << "\n";
        }
    }
}


// ---------------------------------------------------------------------------------------------------------------
//                                                    Main
// ---------------------------------------------------------------------------------------------------------------

int main(int argc, char * argv[]) {
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    // ----------- Actual main to be implemented ----------
    
    unsigned short minSize = 3;
    vector<char> letters = generateBoard();
    
    cout << "***** BOARD *****\n\n";
    printBoard(letters);
    
    cout << "\n\n";

    Board b1(minSize, letters);
    Solutions s1 = b1.Solve();
    
    cout << "***** SOLUTIONS *****\n";
    cout << "Total Points: " << s1.getTotalScore() << "\n\n";
    s1.Print();
    
    
    // ----------------------------------------------------
    
    return 0;
}
