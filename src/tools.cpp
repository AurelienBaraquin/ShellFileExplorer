/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** tools
*/

#include "my.hpp"

std::vector<std::string> split(std::string str, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delim)) {
        result.push_back(token);
    }
    return result;
}

std::string key_to_str(int key)
{
    switch (key) {
        case 27:
            return "ESC";
        case 127:
            return "BACKSPACE";
        case 10:
            return "ENTER";
        case 9:
            return "TAB";
        case 32:
            return "SPACE";
        case 330:
            return "DELETE";
        case 260:
            return "LEFT";
        case 261:
            return "RIGHT";
        case 259:
            return "UP";
        case 258:
            return "DOWN";
        default:
            return std::string(1, key);
    }
}
