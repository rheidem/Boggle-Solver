<!-- TITLE -->
# Boggle Solver



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
* [Algorithm](#algorithm)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
  * [Input](#input)
  * [Ouput](#output)
* [Contact](#contact)


<!-- ABOUT THE PROJECT -->
## About The Project

As with the other projects I have worked on, this one is not without reason. My family plays a lot of Boggle and was wondering how difficult it would be to make an app that uses AI and can take a picture of the board and instantly convert it to all of the possible answers. The first step in this process for myself was to first implement an efficient algorithm to find such solutions. But before I get into that, a bit of background.

[Boggle](https://en.wikipedia.org/wiki/Boggle) is a pretty straightforward game. It is played on an NxN board, with each tile consisting of one letter. After the letters are determined at random, each player writes down each word they can find on the board in however much time is alotted. The game is traditionally played on a 4x4 board, and my project was modelled after this. To be a bit more specific, each word that is found is made by connecting adjacent non-overlapping letters on the grid.

When I initially was thinking of a solution to this problem it was apparent that this could be solved a number of ways. After brainstorming a brute-force solution and several more advanced ones, I finally decided on one that I detail in the [Algorithm](#algorithm) section below.

As with other projects I have worked on, I opted for C++ as the language as it provides an efficient medium to solve complex problems.



<!-- ALGORITHM -->
## Algorithm

As with most constraint satisfaction problems, my first thought was to use some form of backtracking to find each word in the board. 

This in itself isn't terribly hard, but to do it well I knew I would have to find a good way to look up if a sequence of characters is worth the extra time to keep looking into and whether or not a sequence of characters is in fact a word.

First let me detail the main algorithm, which I will include below.

Solves the game and returns the solutions:
```
Solutions Board::Solve() {
    
    Dictionary d1(minWordSize);
    d1.Load(cin);
    
    Solutions s1;
    
    // For each square on the board, solve
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            SolveHelper(d1, s1, i, j, "");
        }
    }
    
    return s1;
}
```

In the function above, we first create a Dictionary containing all of the words in an actual dictionary. In this case, we load in a text file of ~84,000 words. We also specify the minimum word size (which by default is set to 3). Then for each word in the dictionary.txt file, we take the substring(0, minWordSize) and put this in an std::unordered_map<string, vector<string>> where the vector contains all words that start with this substring prefix.
Then we initialize a Solutions object containing an std::set<> of the words found, first sorted by score and then alphabetically. This allows for easy output later. 
Finally, we call the SolveHelper() on each tile of the 4x4 board to find solutions that start with the corresponding letter.


Recursive Helper:
```
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
} 
```

In the recursive helper above, we first ask the Dictionary object if this string is worth it to keep looking at. This is (basically) determined by whether or not the prefix (of minWordSize letters) of the string is a key in the Dictionary. If it is worth it to keep going we add the next letter onto the current string, and ask the Dictionary if this string is a word that is in the Dictionary and not yet found in our Solutions. If so, we write it to the Solutions. 
Finally, in the double for loop, we look at all of the surrounding letters that have not yet been checked.

As confusing as that might be, the algorithm simply says this: does the current string of n characters match the first n characters of any words in the dictionary. If so, we keep looking down this path until there are no more paths with actual words to look down.



<!-- GETTING STARTED -->
## Getting Started

As this project is written 100% in C++, there is very little setup, however there are future plans to extend this to a web application.

### Prerequisites

The project includes a Makefile, so the only thing needed is a working version of g++.
* g++
```sh
$ sudo apt install build-essential
```
This installs g++ for Ubuntu 20.04 by installation of the development package build-essential.

### Installation

1. Clone the repo
```sh
git clone https://github.com/rheidem/Boggle-Solver.git
```


<!-- USAGE EXAMPLES -->
## Usage

To use this application, first compile:
```sh
make
```
Next, you are ready to run with the dictionary.txt file
```sh
./solver < dictionary.txt
```
To clear executables:
```sh
make clean
```

### Input

The input for this project is simply the dictionary.txt file containing the English dictionary (or close to it). 

You may be wondering what 4x4 board we are using as input, and that is determined by random, as in it contains 16 completely random letters.

### Output

The output for this project will mimic the follwing:

```
***** BOARD *****

 l v u m
 m g m l
 j w m a
 g d s a


***** SOLUTIONS *****
Total Points: 25

alma: 1 point
alms: 1 point
alum: 1 point
asa: 1 point
dsm: 1 point
gum: 1 point
lam: 1 point
lama: 1 point
lams: 1 point
las: 1 point
lug: 1 point
mal: 1 point
mama: 1 point
mug: 1 point
mum: 1 point
sam: 1 point
lamas: 2 points
malum: 2 points
mamas: 2 points
lammas: 3 points
```

At the top of the output, we have the 4x4 randomly generated board.
Next we have the total number of points that this board can have, in this case 25.
Following this, is a list of all words that can be found on the board, sorted first by points and second alphabetically (which is why we used the std::set<> earlier).



<!-- CONTACT -->
## Contact

Ryan Heidema - [@ryan-heidema](https://www.linkedin.com/in/ryan-heidema/) - rheidem@umich.edu

Project Link: [https://github.com/rheidem/Boggle-Solver](https://github.com/rheidem/Boggle-Solver)
