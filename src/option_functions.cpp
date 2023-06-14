/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** option_functions
*/

#include "my.hpp"

// to upgrade later with a good interface to get the new path (move_to)
void move_file(global_t *global, std::filesystem::path filePath)
{
    (void)global;
    string move_to = get_input("Enter the new path:", filePath.parent_path());
    if (move_to == "")
        return;
    std::string command = "mv " + (std::string)(filePath) + " " + move_to;
    if (system(command.c_str()) == -1)
        print_warning("Error: can't move file");
}

void paste_file(global_t *global, std::filesystem::path filePath)
{
    (void)global;
    if (global->copy_path == "")
        return;
    std::string command = "cp " + (std::string)global->copy_path + " " + (std::string)filePath.parent_path();
    if (system(command.c_str()) == -1)
        print_warning("Error: can't copy file");
}

void copy_file(global_t *global, std::filesystem::path filePath)
{
    (void)global;
    global->copy_path = filePath;
}

void delete_file(global_t *global, std::filesystem::path filePath)
{
    (void)global;
    int sure = get_choice("Are you sure? (y/n)", {"n", "y"});
    if (sure == 0)
        return;
    std::string command = "rm " + (std::string)(filePath);
    if (system(command.c_str()) == -1)
        print_warning("Error: can't remove file");
}

void rename_file(global_t *global, std::filesystem::path filePath)
{
    (void)global;
    std::string new_name = get_input("Enter the new name:", filePath.filename().string());
    if (new_name == "")
        return;
    int sure = get_choice("Are you sure? (y/n)", {"n", "y"});
    if (sure == 1) {
        std::string command = "mv " + (std::string)(filePath) + " " + (std::string)(filePath.parent_path() / new_name);
        if (system(command.c_str()) == -1)
            print_warning("Error: can't rename file");
    }
}

void new_file(global_t *global, std::filesystem::path filePath)
{
    (void)global;
    std::string new_name = get_input("Enter the new name:", "");
    if (new_name == "")
        return;
    int sure = get_choice("Are you sure? (y/n)", {"n", "y"});
    if (sure == 1) {
        std::string command = "touch " + (std::string)(filePath.parent_path() / new_name);
        if (system(command.c_str()) == -1)
            print_warning("Error: can't create file");
    }
}

void new_folder(global_t *global, std::filesystem::path filePath)
{
    (void)global;
    std::string new_name = get_input("Enter the new name:", "");
    if (new_name == "")
        return;
    int sure = get_choice("Are you sure? (y/n)", {"n", "y"});
    if (sure == 1) {
        std::string command = "mkdir " + (std::string)(filePath.parent_path() / new_name);
        if (system(command.c_str()) == -1)
            print_warning("Error: can't create folder");
    }
}

