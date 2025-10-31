
#include "generator.hpp"

Generator::Generator(std::string name) : name(name)
{
}

std::string Generator::getCLIName() const
{
    return name;
}
