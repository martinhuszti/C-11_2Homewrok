#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
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
        std::set<char> tippedChars;
        std::string displayed_string = "";

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
                char c;
                do
                {
                        AskForCharacterPrintLn();
                        std::cin >> c;
                        c = tolower(c);
                        if (tippedChars.count(c) != 0)
                        {
                                AlreadyTippedPrintLn();
                                ReadedCharacters(tippedChars);
                        }
                        else
                        {
                                tippedChars.insert(c);
                                return std::move(c);
                        }
                } while (true); //contains c++20-nál
        }

        void cleanArrayByRegex(std::pair<std::string, int> &finalRegex)
        {
                words.erase(std::remove_if(words.begin(), words.end(), [&](const Word &w) {
                                    return (finalRegex.first.compare(w.regex));
                            }),
                            words.end());
        }

        std::pair<std::string, int> GetValidRegex(char tippedchar)
        {
                std::map<std::string, int> reg_occurs;

                for (auto &word : words)
                {
                        word.regex = ""; //nullázuk a szó regexét
                        for (auto &c : word.string)
                        {
                                if (tippedchar == c)
                                {
                                        word.regex += c; //ha benne van x-el jelölöm
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

                return valid_regex;
        }

        bool isCorrectTip(const std::pair<std::string, int> &valid_regex, const char &c)
        {
                return (valid_regex.first.find(c) == std::string::npos) ? false : true;
        }

        void play()
        {
                ClearScreen();
                WelcomePrintLn();
                gameLoop();
        }

        bool isGameEnded(const int &elet)
        {
                if (elet == 0)
                {
                        YouLosePrintLn();
                        return true;
                }

                if (displayed_string.find('.') == std::string::npos)
                {
                        YouWinPrintLn();
                        return true;
                }

                return false;
        }

        void mergeWithTemplate(const std::string &regex)
        {
                if (displayed_string.empty())
                {
                        displayed_string = regex;
                        return;
                }

                for (int i = 0; i < regex.size(); i++)
                {
                        if (displayed_string[i] != '.')
                                continue;
                        else
                                displayed_string[i] = regex[i];
                }
        }

        void gameLoop()
        {
                bool endGame = false;
                int elet = 10;
                while (!endGame)
                {

                        ShowOpportunitiesPrintLn(); //felsoroljuk a lehetőségeket
                        for (auto &w : words)
                                WordPrintLn(w.string);

                        char c = RequestCharacter(); //beolvasunk egy karaktert

                        ClearScreen();

                        ReadedCharacters(tippedChars);

                        auto valid_regex = GetValidRegex(std::move(c)); //megkeressuk a karaktert

                        mergeWithTemplate(valid_regex.first); //mergeljük a kiirando szavakkal

                        cleanArrayByRegex(valid_regex); //Kitöröljük azokat a szavakat amik nem illenek a regexre

                        (isCorrectTip(valid_regex, c)) ? GoodTipp() : BadTipp(elet); //megnézzük hogy helyes-e a tipp

                        DisplayCurrentStringPrintLn(displayed_string);

                        endGame = isGameEnded(elet);
                }
        }
};
