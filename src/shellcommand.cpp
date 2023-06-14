/*
** EPITECH PROJECT, 2023
** ShellFileExplorer
** File description:
** shellcommand
*/

#include "my.hpp"

std::string executeCommand(const std::string& command)
{
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Error executing command");
    }
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
    }
    return result;
}
