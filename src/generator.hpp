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
#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <map>
#include <memory>
#include <queue>
#include <string>

struct CliArg
{
    int id;
    std::string longArg;
    std::string shortArg;
    std::string description;
};

class Generator
{
public:
    Generator(std::string name, std::string description);
    virtual ~Generator() = default;

    std::string getName() const;

    std::string getDescription() const;

    virtual void processArgs(std::queue<std::string> &args);

    virtual void handleArg(std::shared_ptr<CliArg> arg, std::queue<std::string> &args) = 0;

    virtual void generate() = 0;

private:
    std::string name;
    std::string description;
    std::map<std::string, std::shared_ptr<CliArg>> argsMap;
    std::vector<std::shared_ptr<CliArg>> argsList;

protected:
    void registerCliArg(CliArg arg);
    std::string getHelpString();

};

#endif // GENERATOR_HPP
