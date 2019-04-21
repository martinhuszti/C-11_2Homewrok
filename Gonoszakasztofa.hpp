#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include "Console_Write.hpp"

class Word
{
public:
        std::string string;
        std::string regex;

        Word(std::string s, std::string r) : string(s), regex(r){};
};

std::ostream &
operator<<(std::ostream &os, const Word &w)
{
        os << w.string;
        return os;
}

class Gonoszakasztofa
{
private:
        std::vector<Word> words;
        std::vector<char> tippchars;
        std::map<std::string, int> reg_occurs;

public:
        Gonoszakasztofa(std::string const &filename)
        {
                std::ifstream infile("szavak.txt");

                std::string word;
                while (infile >> word)
                {
                        words.push_back(std::move(Word(word, "")));
                }
        }

        char RequestCharacter()
        {
                AskForCharacterPrintLn();
                char character;
                std::cin >> character;
                return character;
        }

        void SearchForMatch(char tippedchar)
        {
                for (auto &word : words)
                {
                        for (auto &c : word.string)
                        {
                                if (tippedchar == c)
                                {
                                        word.regex += 'x';
                                }
                                else
                                {
                                        word.regex += '.';
                                }
                        }

                        auto it = reg_occurs.find(word.regex);
                        if (it != reg_occurs.end())
                        {
                                it->second++;
                        }
                        else
                        {
                                reg_occurs.insert(std::make_pair(word.regex, 1));
                        }
                }

                std::pair<std::string, int> valid_regex("", 0);
                for (auto r : reg_occurs)
                {
                        if (r.second > valid_regex.second)
                                valid_regex = r;
                }
                std::cout << "Megfelelő regex: " << valid_regex.first << " darabja: " << valid_regex.second << std::endl;
        }

        void play()
        {
                WelcomePrintLn(); //koszontő
                //std::cout << words[0] << std::endl; //kiirjuk a bemntélvő szavakat
                char c = RequestCharacter();  //beolvasunk egy karaktert
                tippchars.push_back(c);       //hozzáadjuk a karakter a tippeltekhez
                SearchForMatch(std::move(c)); //megkeressuk a karaktert
        }
};
