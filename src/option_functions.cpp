/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** option_functions
*/

#include "my.hpp"

// to upgrade later with a good interface to get the new path (move_to)
void move_file(global_t *global)
{
    string move_to = get_input("Enter the new path:", global->path.string());
    if (move_to == "")
        return;
    std::string command = "mv " + (std::string)(global->path / global->files[global->pos]) + " " + move_to;
    if (system(command.c_str()) == -1)
        print_warning("Error: can't move file");
}

void paste_file(global_t *global)
{
    if (global->copy_path == "")
        return;
    std::string command = "cp " + (std::string)global->copy_path + " " + (std::string)global->path;
    if (system(command.c_str()) == -1)
        print_warning("Error: can't copy file");
}

void copy_file(global_t *global)
{
    global->copy_path = global->path / global->files[global->pos];
}

void delete_file(global_t *global)
{
    int sure = get_choice("Are you sure? (y/n)", {"n", "y"});
    if (sure == 0)
        return;
    std::string command = "rm " + (std::string)(global->path / global->files[global->pos]);
    if (system(command.c_str()) == -1)
        print_warning("Error: can't remove file");
}

void rename_file(global_t *global)
{
    std::string new_name = get_input("Enter the new name:", global->files[global->pos]);
    if (new_name == "")
        return;
    int sure = get_choice("Are you sure? (y/n)", {"n", "y"});
    if (sure == 1) {
        std::string command = "mv " + (std::string)(global->path / global->files[global->pos]) + " " + (std::string)(global->path / new_name);
        if (system(command.c_str()) == -1)
            print_warning("Error: can't rename file");
    }
}

void new_file(global_t *global)
{
    std::string new_name = get_input("Enter the new name:", "");
    if (new_name == "")
        return;
    int sure = get_choice("Are you sure? (y/n)", {"n", "y"});
    if (sure == 1) {
        std::string command = "touch " + (std::string)(global->path / new_name);
        if (system(command.c_str()) == -1)
            print_warning("Error: can't create file");
    }
}

void new_folder(global_t *global)
{
    std::string new_name = get_input("Enter the new name:", "");
    if (new_name == "")
        return;
    int sure = get_choice("Are you sure? (y/n)", {"n", "y"});
    if (sure == 1) {
        std::string command = "mkdir " + (std::string)(global->path / new_name);
        if (system(command.c_str()) == -1)
            print_warning("Error: can't create folder");
    }
}

