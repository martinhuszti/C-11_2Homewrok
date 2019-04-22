#ifndef GONOSZAKASZTOFA_HEADER_FILE
#define GONOSZAKASZTOFA_HEADER_FILE

#include <string>
#include <vector>
#include <map>
#include <set>

class Word
{
public:
        std::string string;
        std::string regex;

        Word(std::string s, std::string r) : string(s), regex(r){};
};

class Gonoszakasztofa
{
private:
        std::vector<Word> words;           //lehetséges szavak
        std::set<char> tippedChars;        //eddig tippelt karakterek
        std::string displayed_string = ""; //eddig tippelt szó "templétje"

        char RequestCharacter();

        void cleanArrayByRegex(std::string const &finalRegex);

        void updateWordRegex(Word &word, const char &tippedchar);

        void addOccurancesByRegex(std::map<std::string, int> &reg_occurs, const std::string &regex);

        std::string MostOccurancesRegex(std::map<std::string, int> const &reg_occurs);

        std::string GenerateValidRegex(char const tippedchar);

        bool isCorrectTip(const std::string &updateWordRegex, const char &c) const;

        bool isGameEnded(const int &elet);

        void updateDisplayStringByRegex(const std::string &regex);

        void gameLoop();

public:
        Gonoszakasztofa(std::string const filename);

        void Play();
};

#endif
