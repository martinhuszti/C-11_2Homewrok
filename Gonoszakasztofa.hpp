#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cctype>

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

public:
        Gonoszakasztofa(std::string const &filename)
        {
                std::ifstream infile(filename);

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

        void cleanArrayByRegex(std::pair<std::string, int> &finalRegex)
        {
                words.erase(std::remove_if(words.begin(), words.end(), [&](const Word &w) {
                                    return (finalRegex.first.compare(w.regex));
                            }),
                            words.end());
        }

        bool GetRegexMap(char tippedchar)
        {
                std::map<std::string, int> reg_occurs;

                for (auto &word : words)
                {
                        for (auto &c : word.string)
                        {
                                if (tippedchar == c)
                                {
                                        word.regex += 'x'; //ha benne van x-el jelölöm
                                }
                                else
                                {
                                        word.regex += '.'; //ha nincs benne .-al
                                }
                        }

                        auto it = reg_occurs.find(word.regex);
                        if (it != reg_occurs.end())
                        {
                                it->second++; // növelem az előfordulás számát
                        }
                        else
                        {
                                reg_occurs.insert(std::make_pair(word.regex, 1)); //hozzáadom ha még nincs
                        }
                }

                std::pair<std::string, int> valid_regex("", 0);
                for (auto r : reg_occurs)
                {
                        if (r.second > valid_regex.second)
                                valid_regex = r;
                }
                //std::cout << "Megfelelő regex: " << valid_regex.first << " darabja: " << valid_regex.second << std::endl;

                cleanArrayByRegex(valid_regex);

                return (valid_regex.first.find('x') == std::string::npos) ? false : true;
        }

        void play()
        {
                WelcomePrintLn(); //koszontő
                gameLoop();
        }

        void gameLoop()
        {
                bool endGame = false;
                while (!endGame)
                {
                        for (auto w : words)
                        {
                                std::cout << w.string << std::endl;
                        }

                        char c = RequestCharacter();        //beolvasunk egy karaktert
                        tippchars.push_back(c);             //hozzáadjuk a karakter a tippeltekhez
                        bool a = GetRegexMap(std::move(c)); //megkeressuk a karaktert
                        if (words.size() == 1)
                        {
                                YouWinPrintLn();
                        }
                }
        }
};
