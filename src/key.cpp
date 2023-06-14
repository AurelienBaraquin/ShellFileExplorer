/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** key
*/

#include "my.hpp"

std::unordered_map<string, int> keyMappings = {
    {"Open", '\n'},
    {"Rename", 'R'},
    {"Delete", 'D'},
    {"New File", 'F'},
    {"Copy", 'C'},
    {"Paste", 'V'},
    // {"Cut", 'x'},
    {"Move", 'M'},
    // {"Help", 'h'},
    {"Up", KEY_UP},
    {"Down", KEY_DOWN},
    {"Select", KEY_RIGHT},
    {"Back", KEY_LEFT},
    {"Quit", 27},
    {"Settings", 'S'},
    {"Sort Files", 'T'},
    {"Search", 'K'},
};

int getKey(const string& action)
{
    if (keyMappings.count(action) > 0)
        return keyMappings[action];
    return -1;
}

void setKey(const string& action, int key)
{
    keyMappings[action] = key;
}

std::unordered_map<std::string, int> get_keys_Map(void)
{
    return keyMappings;
}

int getNbKeys(void)
{
    return keyMappings.size();
}

int getKey_second_byIndex(int index)
{
    int i = 0;
    for (auto it = keyMappings.begin(); it != keyMappings.end(); it++) {
        if (i == index)
            return it->second;
        i++;
    }
    return -1;
}

std::string getKey_byIndex(int index)
{
    int i = 0;
    for (auto it = keyMappings.begin(); it != keyMappings.end(); it++) {
        if (i == index)
            return it->first;
        i++;
    }
    return "";
}

void setDefaultKeys(void)
{
    static const std::unordered_map<string, int> keyMappingsDefault = keyMappings;
    keyMappings = keyMappingsDefault;
}

void setKeyFromFile(const std::string& filePath)
{
    FILE* file = popen(("cat " + filePath + " | awk -F: '$1!~/^\\s*$/{print}'").c_str(), "r");
    if (file == nullptr) {
        std::cerr << "Error: can't open " << filePath << std::endl;
        return;
    }
    const int bufferSize = 256;
    char buffer[bufferSize];
    while (fgets(buffer, bufferSize, file) != nullptr) {
        std::string line(buffer);
        line = line.substr(0, line.size() - 1); // Remove newline character
        std::vector<std::string> lineSplit = split(line, ':');
        if (lineSplit.size() != 2) {
            std::cerr << "Error: invalid line in " << filePath << std::endl;
            continue;
        }
        if (keyMappings.count(lineSplit[0]) == 0) {
            std::cerr << "Error: invalid key name in " << filePath << std::endl;
            continue;
        }
        keyMappings[lineSplit[0]] = std::stoi(lineSplit[1]);
    }
    pclose(file);
}


void saveKeyOnFile(const std::string& filePath)
{
    std::string command = "echo \"";
    std::unordered_map<std::string, int> key_map = get_keys_Map();
    for (const auto& pair : key_map)
        command += pair.first + ":" + std::to_string(pair.second) + "\n";
    command += "\" > " + filePath;
    if (system(command.c_str()) == -1) {
        std::cerr << "Error: can't open " << filePath << std::endl;
        return;
    }
}
