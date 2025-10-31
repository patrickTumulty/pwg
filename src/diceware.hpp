
#ifndef DICEWARE_WORDS_H
#define DICEWARE_WORDS_H

#include "generator.hpp"
#include <map>
#include <optional>
#include <string>

class DicewareLookup
{
public:
    DicewareLookup();
    ~DicewareLookup();

    std::optional<std::string> lookupWord(int number);

private:

    std::map<int, std::string> wordMap;
};

class DicewareGenerator : public Generator
{
public:
    DicewareGenerator();

    void processArgs(std::queue<std::string> args) override; 

private:
    std::string dicewareString(int len);

    DicewareLookup dicewareLookup;

};


#endif // DICEWARE_WORDS_H
