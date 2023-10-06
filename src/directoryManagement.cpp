/*
** EPITECH PROJECT, 2023
** ShellFileExplorer
** File description:
** directoryManagement
*/

#include "my.hpp"

commandReturn_t executeCommandInCurrentDirectory(const std::string& command)
{
    commandReturn_t result;
    std::stringstream output;
    FILE* pipe = popen(command.c_str(), "r");
    if (pipe) {
        char buffer[128];
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != nullptr)
                output << buffer;
        }
        result.returnValue = pclose(pipe);
    }
    result.output = output.str();
    return result;
}

void refresh_directory(std::filesystem::path path)
{
    if (!std::filesystem::is_directory(path)) {
        std::cout << "Error: Can't open directory" << std::endl;
        return;
    }
    if (chdir(path.c_str()) == -1) {
        print_warning("Error: Can't open directory");
        return;
    }
}
