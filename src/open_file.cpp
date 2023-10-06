/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** open_file
*/

#include "my.hpp"

void processRegFile(const std::string file)
{
    std::string command = "xdg-open " + file;
    if (system(command.c_str()) == -1) {
        print_warning("Error: can't open file");
        return;
    }
}

void open_file(global_t *global, std::filesystem::path filePath)
{
    struct stat fileStat;
    if (stat(filePath.c_str(), &fileStat) == 0) {
        if (S_ISREG(fileStat.st_mode)) {
            processRegFile(filePath);
            return;
        }
        if (S_ISDIR(fileStat.st_mode)) {
            global->path = filePath;
            global->pos_stack.push_back(global->pos);
            //compare if the last element of the stack is the same as the current path
            if (global->file_stack.size() > 0 && global->file_stack.back().path == global->path) {
                global->pos = global->file_stack.back().position;
                global->file_stack.pop_back();
            } else {
                global->pos = 0;
            }
            refresh_directory(global->path);
            return;
        }
    }
    print_warning("Error: can't open file");
}
