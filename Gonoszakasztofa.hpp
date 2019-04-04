#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Gonoszakasztofa
{
private:
  std::vector<std::string> words;

public:
  Gonoszakasztofa(std::string &filename)
  {
    std::ifstream infile("thefile.txt");

    std::string word while (infile >> word)
    {
      words.push_back(word);
    }
  }
};