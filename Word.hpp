//
//  Word.hpp
//  BoggleSolver
//
//  Created by Ryan Heidema on 6/5/20.
//  Copyright © 2020 Ryan Heidema. All rights reserved.
//

#ifndef Word_hpp
#define Word_hpp

#include <iostream>

// ---------------------------------------------------------------------------------------------------------------
//                                                 Word Class
// ---------------------------------------------------------------------------------------------------------------

class Word {
    
private:
    std::string text;
    unsigned short score;
    
public:
    Word(const std::string text_in);
    
    std::string getText() const;
    
    unsigned short getScore() const;
    
};


#endif /* Word_hpp */
