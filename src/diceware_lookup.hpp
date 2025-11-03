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

#ifndef DICEWARE_LOOKUP_HPP
#define DICEWARE_LOOKUP_HPP

#include <map>
#include <optional>
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

#endif // DICEWARE_LOOKUP_HPP
