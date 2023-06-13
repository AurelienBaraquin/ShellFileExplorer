/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** get_files
*/

#include "my.hpp"

void get_files(global_t *global)
{
    std::filesystem::directory_iterator end;
    std::filesystem::directory_iterator dir(global->path);
    global->files.clear();
    for (auto &file : dir) {
        if (file.path().filename().string()[0] != '.')
            global->files.push_back(file.path().filename());
    }
    switch (global->sort_type) {
        case SORT_BY_NAME:
            std::sort(global->files.begin(), global->files.end());
            break;
        case SORT_BY_NAME_REVERSE:
            std::sort(global->files.begin(), global->files.end(), std::greater<std::string>());
            break;
        default:
            break;
    }
}

int get_max_str_size_from_vector(std::vector<std::string> files)
{
    int max = 0;
    for (auto &file : files) {
        if ((int)file.size() > max)
            max = file.size();
    }
    return max;
}
