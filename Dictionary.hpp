//
//  Dictionary.hpp
//  BoggleSolver
//
//  Created by Ryan Heidema on 6/5/20.
//  Copyright © 2020 Ryan Heidema. All rights reserved.
//

#ifndef Dictionary_hpp
#define Dictionary_hpp

#include <iostream>
#include <vector>
#include <istream>
#include <unordered_map>

// ---------------------------------------------------------------------------------------------------------------
//                                               Dictionary Class
// ---------------------------------------------------------------------------------------------------------------

class Dictionary {
private:
    unsigned short minWordSize;
    std::unordered_map<std::string, std::vector<std::string>> dict;
    
public:
    Dictionary(unsigned short minWordSize_in);
    
    // Load the words in and process into the dict
    void Load(std::istream &input);
    
    // Returns whether or not the dict contains a word
    bool Contains(std::string input);
    
    // Returns true if you should keep searching
    bool KeepGoing(std::string input);
};

#endif /* Dictionary_hpp */
