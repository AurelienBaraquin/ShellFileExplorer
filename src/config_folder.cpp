/*
** EPITECH PROJECT, 2023
** ShellFileExplorer
** File description:
** config_folder
*/

#include "my.hpp"

// #define PARENT_PATH "~/.config/ShellFileExplorer"
#define PARENT_PATH "~/.config/SFE"

int init_config_folder(void)
{
    if (system(("mkdir -p " + std::string(PARENT_PATH)).c_str()) == -1)
        return 84;
    if (system(("touch " + std::string(PARENT_PATH) + "/checkpoints").c_str()) == -1)
        return 84;
    if (system(("mkdir " + std::string(PARENT_PATH) + "/cutted_file").c_str()) == -1)
        return 84;
    if (system(("touch " + std::string(PARENT_PATH) + "/key_settings").c_str()) == -1)
        return 84;
    saveKeyOnFile(std::string(PARENT_PATH) + "/key_settings");
    return 0;
}
