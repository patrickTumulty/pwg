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
#include "generator.hpp"
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <memory>
#include <sstream>

Generator::Generator(std::string name, std::string description) : name(name), description(description)
{
}

std::string Generator::getName() const
{
    return name;
}

std::string Generator::getDescription() const
{
    return description;
}

void Generator::processArgs(std::queue<std::string> &args)
{
    while (!args.empty())
    {
        std::string argStr = args.front();
        args.pop();
        if (argStr == "--help")
        {
            std::cout << getHelpString() << "\n";
            return;
        }

        int argStrLen = argStr.length();
        if (argStrLen < 2)
        {
            continue;
        }

        if (argStr[0] == '-' && argStr[1] == '-')
        {
            std::shared_ptr<CliArg> arg = argsMap[argStr.substr(2, argStrLen - 2)];
            if (arg == nullptr)
            {
                continue;
            }

            handleArg(arg, args);
            continue;
        }

        if (argStr[0] == '-')
        {
            std::shared_ptr<CliArg> arg = argsMap[argStr.substr(1, argStrLen - 1)];
            if (arg == nullptr)
            {
                continue;
            }

            handleArg(arg, args);
            continue;
        }
    }

    generate();
}

void Generator::registerCliArg(CliArg arg)
{
    std::shared_ptr<CliArg> cliArgPtr = std::make_shared<CliArg>(arg);

    bool added = false;
    if (!arg.longArg.empty())
    {
        argsMap[arg.longArg] = cliArgPtr;
        added = true;
    }

    if (!arg.shortArg.empty())
    {
        argsMap[arg.shortArg] = cliArgPtr;
        added = true;
    }

    if (added)
    {
        argsList.push_back(cliArgPtr);
    }
}

std::string Generator::getHelpString()
{
    char lineBuffer[128];
    std::ostringstream oss;

    oss << "Usage: " << getName() << " [OPTIONS]\n";
    oss << "\n";
    oss << getDescription() << "\n";

    oss << "Options:\n";
    for (auto entry : argsList)
    {
        std::shared_ptr<CliArg> arg = entry;
        oss << "  ";
        if (!arg->shortArg.empty())
        {
            snprintf(lineBuffer, sizeof(lineBuffer), "%3s,", ("-" + arg->shortArg).c_str());
            oss << lineBuffer;
        }
        else
        {
            oss << "    ";
        }

        if (!arg->longArg.empty())
        {
            snprintf(lineBuffer, sizeof(lineBuffer), "--%-10s", arg->longArg.c_str());
            oss << lineBuffer;
        }
        else
        {
            oss << "            ";
        }

        oss << ": " << arg->description << "\n";
    }

    return oss.str();
}
