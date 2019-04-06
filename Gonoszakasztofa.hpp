#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Console_Write.hpp"

class Gonoszakasztofa
{
private:
std::vector<std::string> words;

public:
Gonoszakasztofa(std::string const &filename)
{
        std::ifstream infile("szavak.txt");

        std::string word;
        while (infile >> word)
        {
                words.push_back(word);
        }
}

char RequestCharacter(){
        AskForCharacter();
        char character;
        std::cin >> character;
        return character
}

void SearchForMatch(){
    
}

void play(){
        Welcome();
        std::cout << words[0];
        char c = RequestCharacter();
        SearchForMatch(c);
}

};
