/*
** EPITECH PROJECT, 2023
** ShellFileExplorer
** File description:
** config_folder
*/

#include "my.hpp"

#define PARENT_PATH "~/.config/SFE"

int init_config_folder(void)
{
    std::cout << "Initializing config folder..." << std::endl;
    if (system(("mkdir -p " + std::string(PARENT_PATH)).c_str()) == -1)
        return 84;
    if (system(("touch " + std::string(PARENT_PATH) + "/checkpoints").c_str()) == -1)
        return 84;
    if (system(("mkdir " + std::string(PARENT_PATH) + "/cutted_file").c_str()) == -1)
        return 84;
    if (system(("touch " + std::string(PARENT_PATH) + "/key_settings").c_str()) == -1)
        return 84;
    saveKeyOnFile(std::string(PARENT_PATH) + "/key_settings");
    std::string binPath = executeCommand("find ~/ -name \"SFE\" -not -path \"*/.*\"");
    if (system(std::string("echo \"" + binPath + "\" >> ~/.bashrc").c_str()) == -1)
        return 84;
    std::cout << "Done, now you can do the command \"bash\" in your term or just open a new terminal !" << std::endl;
    return 0;
}
