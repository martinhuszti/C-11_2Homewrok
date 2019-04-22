#ifndef GONOSZAKASZTOFA_HEADER_FILE
#define GONOSZAKASZTOFA_HEADER_FILE

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
                                ReadedCharactersPrintLn(tippedChars);
                        }
                        else
                        {
                                tippedChars.insert(c);
                                return std::move(c);
                        }
                } while (true); //contains c++20-nál
        }

        void cleanArrayByRegex(std::string const &finalRegex)
        {
                words.erase(std::remove_if(words.begin(), words.end(),

                                           [&](const Word &w) {
                                                   return (finalRegex.compare(w.regex));
                                           }),

                            words.end());
        }

        void updateWordRegex(Word &word, const char &tippedchar)
        {
                word.regex = ""; //nullázuk a szó regexét
                for (auto &c : word.string)
                {
                        if (tippedchar == c) //ha benne van
                        {
                                word.regex += c; //beírom a karaktert
                        }
                        else //ha nincs benne
                        {
                                word.regex += '.'; // .-ot rakok
                        }
                }
        }

        void addOccurancesByRegex(std::map<std::string, int> &reg_occurs, const std::string &regex)
        {
                auto it = reg_occurs.find(regex);
                if (it != reg_occurs.end()) //ha már létezik a map-ben
                {
                        it->second++; // növelem az előfordulás számát
                }
                else //ha még nem létezik
                {
                        reg_occurs.insert(std::make_pair(regex, 1)); //hozzáadom
                }
        }

        std::string searchgMostOccurancesRegex(std::map<std::string, int> const &reg_occurs)
        {
                std::pair<std::string, int> regex_pair("", 0);
                for (auto it : reg_occurs)
                {
                        if (it.second > regex_pair.second)
                                regex_pair = it;
                }
                return std::move(regex_pair.first);
        }

        std::string GenerateValidRegex(char const tippedchar)
        {
                std::map<std::string, int> reg_occurs;

                for (auto &word : words)
                {
                        updateWordRegex(word, tippedchar); //frissítjük a szónak a regexét a tippelt karakter alapján

                        addOccurancesByRegex(reg_occurs, word.regex); //frissítjük a regex előfordulás számosságát
                }

                return searchgMostOccurancesRegex(reg_occurs);
        }

        bool isCorrectTip(const std::string &updateWordRegex, const char &c)
        {
                return (updateWordRegex.find(c) == std::string::npos) ? false : true;
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

                for (unsigned i = 0; i < regex.size(); i++)
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

                        ReadedCharactersPrintLn(tippedChars);

                        auto valid_regex = GenerateValidRegex(std::move(c)); //megkeressuk a karaktert

                        mergeWithTemplate(valid_regex); //mergeljük a kiirando szavakkal

                        cleanArrayByRegex(valid_regex); //Kitöröljük azokat a szavakat amik nem illenek a regexre

                        (isCorrectTip(valid_regex, c)) ? GoodTipp() : BadTipp(elet); //megnézzük hogy helyes-e a tipp

                        DisplayCurrentStringPrintLn(displayed_string);

                        endGame = isGameEnded(elet);
                }
        }

public:
        Gonoszakasztofa(std::string const filename)
        {
                std::ifstream infile(filename);

                std::string word;
                while (infile >> word)
                {
                        words.push_back(std::move(Word(word, "")));
                }
        }

        void play()
        {
                ClearScreen();
                WelcomePrintLn();
                gameLoop();
        }
};

#endif
