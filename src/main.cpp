#include "diceware.hpp"
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
    std::vector<std::unique_ptr<Generator>> generators;

    generators.emplace_back(std::make_unique<DicewareGenerator>());

    std::queue<std::string> argsQueue;

    for (int i = 1; i < argc; i++)
    {
        argsQueue.emplace(std::string(argv[i]));
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
