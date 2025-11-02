
#ifndef DICEWARE_WORDS_H
#define DICEWARE_WORDS_H

#include "generator.hpp"
#include <cstdint>
#include <map>
#include <optional>
#include <random>
#include <string>


enum DicewareWordlist
{
    DW_WORDLIST_ORIGINAL,
    DW_WORDLIST_EFF
};

class DicewareLookup
{
public:
    DicewareLookup();
    ~DicewareLookup();

    std::optional<std::string> lookupWord(int number, DicewareWordlist wordlist);

private:
    std::map<int, std::string> originalWordMap;
    std::map<int, std::string> effWordMap;
};

class DicewareGenerator : public Generator
{
public:
    DicewareGenerator();

    void processArgs(std::queue<std::string> args) override;

private:
    std::string rollDicewarePassword(int len, DicewareWordlist wordlist);
    uint8_t diceroll();
    int rollDicewareID();

    DicewareLookup dicewareLookup;

    // Create a random device and a generator
    std::random_device rd; // non-deterministic seed
    std::mt19937 gen;      // Mersenne Twister generator

    // Define the range [1, 6]
    std::uniform_int_distribution<int> dist;
};


#endif // DICEWARE_WORDS_H
