/*
 * Copyright 2025 Patrick Tumulty
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "diceware.hpp"
#include "diceware_eff_wordlist.hpp"
#include "diceware_wordlist.hpp"
#include "generator.hpp"
#include <cstdint>
#include <iostream>
#include <optional>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <sys/types.h>

enum DicewareCliArg
{
    DW_CLI_LEN = 0,
    DW_CLI_WORDLIST = 1,
};


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

static std::string desc = "Randomly generator a diceware passphrase.\nFor more information visit the website.\nhttps://diceware.dmuth.org\n";

DicewareGenerator::DicewareGenerator() : gen(rd()), dist(1, 6), Generator("diceware", desc)
{
    dicewarePasswordLen = 1;
    wordlist = DW_WORDLIST_ORIGINAL;

    registerCliArg((CliArg) {
        .id = DW_CLI_LEN,
        .longArg = "len",
        .shortArg = "l",
        .description = "Length of diceware passphrase in words. (default = 1)",
    });

    registerCliArg((CliArg) {
        .id = DW_CLI_WORDLIST,
        .longArg = "wordlist",
        .shortArg = "wl",
        .description = "Diceware wordlist. 'original' or 'eff' (default = 'original')",
    });
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

void DicewareGenerator::generate()
{
    std::cout << rollDicewarePassword(dicewarePasswordLen, wordlist) << "\n";
}

void DicewareGenerator::handleArg(std::shared_ptr<CliArg> arg, std::queue<std::string> &args)
{
    switch (arg->id)
    {
        case DW_CLI_LEN:
            dicewarePasswordLen = std::stoi(args.front());
            args.pop();
            break;
        case DW_CLI_WORDLIST:
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
            break;
    }
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
