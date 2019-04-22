#ifndef CONSOLEWRITE_HEADER_FILE
#define CONSOLEWRITE_HEADER_FILE

#include <iostream>
#include <vector>
#include <string>
#include <set>

#include "Gonoszakasztofa.hpp"

static void WelcomePrintLn()
{
        std::cout << "Köszöntelek a Gonosz akasztófában! 10 életed van.\n\n";
}

static void AskForCharacterPrintLn()
{
        std::cout << "\nTippelj egy betűt: ";
}

static void YouWinPrintLn()
{
        std::cout << "Gratulálok, nyertél!\n";
}

static void YouLosePrintLn()
{
        std::cout << "Sajnos vesztettél!\n";
}

static void ShowOpportunitiesPrintLn()
{
        std::cout << "A szavak amikre gondolhattam:\n";
}

static void WordPrintLn(const std::string &s)
{
        std::cout << "\t" << s << std::endl;
}

static void GoodTipp()
{
        std::cout << "Helyes tipp!";
}

static void BadTipp(int &elet)
{
        std::cout << "Rossz tipp! " << --elet << " életed maradt.";
}

static void AlreadyTippedPrintLn()
{
        std::cout << "Ezt a betűt már egyszer tippelted. Adj meg egy másikat!\n";
}

static void DisplayCurrentStringPrintLn(const std::string &s)
{
        std::cout << "\n\t\t" << s << "\n\n";
}

static void ClearScreen()
{
        std::cout << "\033[2J\033[1;1H";
}

static void ReadedCharactersPrintLn(const std::set<char> &tippchars)
{
        std::cout << "Eddig tippelt karakterek: ";
        for (auto &c : tippchars)
        {
                std::cout << c << " ";
        }
        std::cout << "\n\n";
}

#endif
