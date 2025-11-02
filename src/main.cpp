#include "diceware.hpp"
#include "generator.hpp"
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
        std::cout << "Try 'pwg help' for more information.\n";
        return 0;
    }

    std::string firstArg = argsQueue.front();
    argsQueue.pop();

    for (auto &generator : generators)
    {
        if (generator->getCLIName() == firstArg)
        {
            generator->processArgs(argsQueue);
            break;
        }
    }

    if (firstArg == "help")
    {
        std::cout << "Help!\n";
        return 0;
    }

    if (firstArg == "version")
    {
        std::cout << "Version\n";
        return 0;
    }

    return 0;
}
