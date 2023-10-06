/*
** EPITECH PROJECT, 2023
** ShellFileExplorer
** File description:
** clipBoard
*/

#include "my.hpp"

void copyToClipboard(const std::string& textToCopy)
{
    std::string command = "echo \"" + textToCopy + "\" | xclip -selection clipboard";
    if (system(command.c_str()) == -1)
        print_warning("Error: can't copy to clipboard");
}
