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
#include "diceware_generator.hpp"
#include "generator.hpp"
#include "version.h"
#include <iostream>
#include <memory>
#include <queue>

int main(int argc, char *argv[])
{
    std::vector<std::unique_ptr<Generator>> generators;

    generators.emplace_back(std::make_unique<DicewareGenerator>());

    std::queue<std::string> argsQueue;

    for (int i = 1; i < argc; i++)
    {
        argsQueue.emplace(argv[i]);
    }

    if (argsQueue.empty())
    {
        std::cout << "No parameters specified.\n";
        std::cout << "Try 'pwg --help' for more information.\n";
        return 0;
    }

    std::string firstArg = argsQueue.front();
    argsQueue.pop();

    for (auto &generator : generators)
    {
        if (generator->getName() == firstArg)
        {
            generator->processArgs(argsQueue);
            break;
        }
    }

    if (firstArg == "--help")
    {
        std::cout << "Usage: pwg [GENERATOR] [OPTIONS]\n";
        std::cout << "Quickly and easily generator new passwords!\n\n";

        std::cout << "Options:\n";
        std::cout << "  --version : display version information and exit.\n";
        std::cout << "  --help    : display this help text and exit.\n";
        std::cout << "\n";

        std::cout << "The following generators can be used: Try <generator> --help for more info.\n\n";
        for (auto &generator : generators)
        {
            std::cout << "  * " << generator->getName() << "\n";
        }

        std::cout << "\n";
        std::cout << "License:\n";
        std::cout << "  Licensed under the Apache License, Version 2.0.\n";
        std::cout << "  See https://www.apache.org/licenses/LICENSE-2.0 for details.\n";
        return 0;
    }

    if (firstArg == "--version")
    {
        std::cout << "pwg - v" << PROJECT_VERSION_STRING << "\n";
        std::cout << "Licensed under the Apache License, Version 2.0.\n";
        std::cout << "See https://www.apache.org/licenses/LICENSE-2.0 for details.\n";
        return 0;
    }

    return 0;
}
