
#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <queue>
#include <string>
#include <vector>

class Generator
{
public:
    Generator(std::string name);
    virtual ~Generator() = default; 

    std::string getCLIName() const;

    virtual void processArgs(std::queue<std::string> args) = 0;
private:
    std::string name;
};

#endif // GENERATOR_HPP
