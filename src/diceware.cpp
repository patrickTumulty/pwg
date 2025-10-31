
#include "diceware.hpp"
#include "diceware_wordlist.hpp"
#include "generator.hpp"
#include <execution>
#include <iostream>
#include <optional>
#include <queue>
#include <random>
#include <sstream>
#include <string>

typedef enum {
    DW_WORDLIST_ORIGINAL,
    DW_WORDLIST_EFF
} DicewareWordlist;

DicewareLookup::DicewareLookup()
{
    std::string *words = new std::string(reinterpret_cast<const char *>(diceware_wordlist_txt), diceware_wordlist_txt_len);

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
            wordMap.insert({number, word});
        }
    }

    delete words;
}

DicewareLookup::~DicewareLookup()
{
    wordMap.clear();
}

std::optional<std::string> DicewareLookup::lookupWord(int number)
{
    return std::optional(wordMap[number]);
}

DicewareGenerator::DicewareGenerator() : Generator("diceware")
{
}

void DicewareGenerator::processArgs(std::queue<std::string> args)
{
    int dicewarePasswordLen = 0;
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

    std::cout << dicewareString(dicewarePasswordLen) << "\n";
}

std::string DicewareGenerator::dicewareString(int len)
{
    // Create a random device and a generator
    std::random_device rd;  // non-deterministic seed
    std::mt19937 gen(rd()); // Mersenne Twister generator

    // Define the range [1, 6]
    std::uniform_int_distribution<int> dist(1, 6);

    std::string s;

    for (int i = 0; i < len; i++)
    {
        std::string sequence;
        for (int j = 0; j < 5; j++)
        {
            int diceRoll = dist(gen);
            sequence += std::to_string(diceRoll);
        }
        int number = std::stoi(sequence);

        auto word = dicewareLookup.lookupWord(number);
        if (word.has_value())
        {
            s += word.value();
            if (i < len - 1)
            {
                s += " ";
            }
        }
    }

    return s;
}
