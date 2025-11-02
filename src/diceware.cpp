
#include "diceware.hpp"
#include "diceware_eff_wordlist.hpp"
#include "diceware_wordlist.hpp"
#include "generator.hpp"
#include <cstdint>
#include <iostream>
#include <iterator>
#include <optional>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <sys/types.h>


static void populateWordMap(std::map<int, std::string> &map, const uint8_t *wordlist, uint32_t wordlistLen)
{
    std::string *words = new std::string(reinterpret_cast<const char *>(wordlist), wordlistLen);

    std::istringstream iss(*words);
    std::string line;

    while (std::getline(iss, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::istringstream lineStream(line);
        int number;
        std::string word;

        if (lineStream >> number >> word)
        {
            map.insert({number, word});
        }
    }

    delete words;
}

DicewareLookup::DicewareLookup()
{
    populateWordMap(originalWordMap, diceware_wordlist_txt, diceware_wordlist_txt_len);
    populateWordMap(effWordMap, diceware_eff_wordlist_txt, diceware_eff_wordlist_txt_len);
}

DicewareLookup::~DicewareLookup()
{
    originalWordMap.clear();
    effWordMap.clear();
}

std::optional<std::string> DicewareLookup::lookupWord(int number, DicewareWordlist wordlist)
{
    switch (wordlist)
    {
        case DW_WORDLIST_ORIGINAL:
            return std::optional(originalWordMap[number]);
        case DW_WORDLIST_EFF:
            return std::optional(effWordMap[number]);
        default:
            return std::nullopt;
    }
}

DicewareGenerator::DicewareGenerator() : gen(rd()), dist(1, 6), Generator("diceware")
{
}

void DicewareGenerator::processArgs(std::queue<std::string> args)
{
    int dicewarePasswordLen = 1;
    DicewareWordlist wordlist = DW_WORDLIST_ORIGINAL;

    while (!args.empty())
    {
        std::string arg = args.front();
        args.pop();

        if (arg == "-len")
        {
            dicewarePasswordLen = std::stoi(args.front());
            args.pop();
        }
        else if (arg == "-wordlist")
        {
            std::string wordlist = args.front();
            args.pop();

            if (wordlist == "eff")
            {
                wordlist = DW_WORDLIST_EFF;
            }
            else if (wordlist == "original")
            {
                wordlist = DW_WORDLIST_ORIGINAL;
            }
        }
    }

    std::cout << rollDicewarePassword(dicewarePasswordLen, wordlist) << "\n";
}

std::string DicewareGenerator::rollDicewarePassword(int len, DicewareWordlist wordlist)
{
    std::ostringstream oss;

    for (int i = 0; i < len; i++)
    {
        int number = rollDicewareID();
        auto word = dicewareLookup.lookupWord(number, wordlist);
        if (word.has_value())
        {
            oss << word.value();
            if (i < len - 1)
            {
                oss << " ";
            }
        }
    }

    return oss.str();
}

uint8_t DicewareGenerator::diceroll()
{
    return dist(gen);
}

int DicewareGenerator::rollDicewareID()
{
    char sequence[6];
    sequence[5] = '\0';
    for (int i = 0; i < 5; i++)
    {
        sequence[i] = diceroll() + '0';
    }
    return std::stoi(sequence);
}
