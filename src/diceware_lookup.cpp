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
#include "diceware_lookup.hpp"
#include "diceware_wordlist.hpp"
#include "diceware_eff_wordlist.hpp"
#include <cstdint>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>


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

