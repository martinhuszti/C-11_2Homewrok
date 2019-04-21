#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
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
        std::map<std::string, int> regex_occurances;

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

        // int countMatchInRegex(std::string s, char c)
        // {

        //         std::regex words_regex(c);
        //         auto words_begin = std::sregex_iterator(
        //             s.begin(), s.end(), words_regex);
        //         auto words_end = std::sregex_iterator();

        //         return std::distance(words_begin, words_end);
        // }

        void SearchForMatch(char tippedchar)
        {
                for (auto &word : words)
                {
                        for (auto &c : word.string)
                        {
                                if (tippedchar == c)
                                {
                                        word.regex += c;
                                }
                                else
                                {
                                        word.regex += '.';
                                }
                        }

                        auto it = regex_occurances.find(word.regex);
                        if (it != regex_occurances.end())
                        {
                                it->second++;
                        }
                        else
                        {
                                regex_occurances.insert(std::make_pair(word.regex, 1));
                        }
                }
                for (auto r : regex_occurances)
                        std::cout << r.first << " darabja: " << r.second << std::endl;
        }

        void play()
        {
                WelcomePrintLn();                   //koszontő
                std::cout << words[0] << std::endl; //kiirjuk a bemntélvő szavakat
                char c = RequestCharacter();        //beolvasunk egy karaktert
                tippchars.push_back(c);             //hozzáadjuk a karakter a tippeltekhez
                SearchForMatch(std::move(c));       //megkeressuk a karaktert
        }
};
