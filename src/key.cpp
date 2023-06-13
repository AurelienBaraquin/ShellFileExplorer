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
    {"New File", 'f'},
    {"New Folder", 'F'},
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
