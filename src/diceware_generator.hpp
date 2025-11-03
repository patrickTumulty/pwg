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
#ifndef DICEWARE_WORDS_H
#define DICEWARE_WORDS_H

#include "diceware_lookup.hpp"
#include "generator.hpp"
#include <cstdint>
#include <random>
#include <string>


class DicewareGenerator : public Generator
{
public:
    DicewareGenerator();

    void handleArg(std::shared_ptr<CliArg> arg, std::queue<std::string> &args) override;

    void generate() override;

private:
    std::string rollDicewarePassword(int len, DicewareWordlist wordlist);
    uint8_t diceroll();
    int rollDicewareID();

    int dicewarePasswordLen;
    DicewareWordlist wordlist;

    std::vector<CliArg> args;

    DicewareLookup dicewareLookup;

    // Create a random device and a generator
    std::random_device rd; // non-deterministic seed
    std::mt19937 gen;      // Mersenne Twister generator

    // Define the range [1, 6]
    std::uniform_int_distribution<int> dist;
};


#endif // DICEWARE_WORDS_H
