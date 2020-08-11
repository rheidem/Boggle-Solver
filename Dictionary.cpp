//
//  Dictionary.cpp
//  BoggleSolver
//
//  Created by Ryan Heidema on 6/5/20.
//  Copyright © 2020 Ryan Heidema. All rights reserved.
//

#include "Dictionary.hpp"
#include <vector>
#include <istream>
#include <unordered_map>
#include <algorithm>

using namespace std;

// ---------------------------------------------------------------------------------------------------------------
//                                               Dictionary Class
// ---------------------------------------------------------------------------------------------------------------

Dictionary::Dictionary(unsigned short minWordSize_in)
: minWordSize(minWordSize_in) {}


// Load the words in and process into the dict
void Dictionary::Load(std::istream &input) {
    string word;
    
    while(input >> word) {
        
        // If string's length is in acceptable size range
        if(word.length() >= minWordSize && word.length() <= 16){
            
            // Look for prefix in the dict
            string prefix = word.substr(0,minWordSize);
            auto found_it = dict.find(prefix);
            
            // if not found, create vector and add to the dict
            if(found_it == dict.end()){
                vector<string> v;
                v.emplace_back(word);
                dict.insert({prefix,v});
            }
            else { // if found, add to value in u_map
                found_it->second.emplace_back(word);
            }
        }
    }
} // Dictionary::Load()


// Returns whether or not the dict contains a word
bool Dictionary::Contains(std::string input) {
    
    // If the length of the input is less than min size, return false
    if(input.length() < minWordSize) {
        return false;
    }
    
    // Search dict for prefix
    string prefix = input.substr(0, minWordSize);
    if(dict.find(prefix) == dict.end()) {
        return false; // if not found, return false
    }
    else {
        vector<string> &v = dict[prefix];
        
        // Looks through u_map's value for the string, returning if found
        if(find(v.begin(), v.end(), input) != v.end()) {
            return true;
        }
        else {
            return false;
        }
    }
} // Dictionary::Contains()


// Returns true if you should keep searching
bool Dictionary::KeepGoing(std::string input) {
    
    // Always keep going if length is less than the minimum size
    if(input.length() < minWordSize) {
        return true;
    }
    
    // Ask dict if the prefix is found
    string prefix = input.substr(0, minWordSize);
    if(dict.find(prefix) == dict.end()) {
        return false;
    }
    else {
        vector<string> &v = dict[prefix];
        for(size_t i = 0; i < v.size(); ++i) {
            // if word in v starts with prefix of 'input' return true
            if(v[i].substr(0,input.length()) == input) {
                return true;
            }
        }
        
        return false;
    }
} // Dictionary::KeepGoing()
