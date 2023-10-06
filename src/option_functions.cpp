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
    if (system(command.c_str()) == -1) {
        addNotifPopup("Error: can't move file", RED);
        return;
    }
    addNotifPopupVector({filePath.filename().string(), " moved to ", move_to}, {GREEN, WHITE, GREEN});
}

void paste_file(global_t *global, std::filesystem::path filePath)
{
    (void)global;
    if (global->copy_path == "")
        return;
    std::string command = "cp " + (std::string)global->copy_path + " " + (std::string)filePath.parent_path();
    if (system(command.c_str()) == -1) {
        addNotifPopup("Error: can't copy file", RED);
        return;
    }
    addNotifPopupVector({global->copy_path.filename().string(), " copied to ", filePath.parent_path().string()}, {GREEN, WHITE, GREEN});
}

void copy_file(global_t *global, std::filesystem::path filePath)
{
    (void)global;
    global->copy_path = filePath;
    addNotifPopupVector({filePath.filename().string(), " copied"}, {GREEN, WHITE});
}

void delete_file(global_t *global, std::filesystem::path filePath)
{
    (void)global;
    int sure = get_choice("Are you sure? (y/n)", {"n", "y"});
    if (sure == 0)
        return;
    std::string command = "rm " + (std::string)(filePath);
    if (system(command.c_str()) == -1) {
        addNotifPopup("Error: can't remove file", RED);
        return;
    }
    addNotifPopupVector({filePath.filename().string(), " removed"}, {GREEN, WHITE});
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
        if (system(command.c_str()) == -1) {
            addNotifPopup("Error: can't rename file", RED);
            return;
        }
    }
    addNotifPopupVector({filePath.filename().string(), " renamed to ", (std::string)(new_name)}, {GREEN, WHITE, GREEN});
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
        if (system(command.c_str()) == -1) {
            addNotifPopup("Error: can't create file", RED);
            return;
        }
    }
    addNotifPopupVector({"File ", new_name, " created"}, {GREEN, WHITE, GREEN});
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
        if (system(command.c_str()) == -1) {
            addNotifPopup("Error: can't create folder", RED);
            return;
        }
    }
    addNotifPopupVector({"Folder ", new_name, " created"}, {GREEN, WHITE, GREEN});
}

void copy_path(global_t *global, std::filesystem::path filePath)
{
    (void)global;
    copyToClipboard((std::string)filePath);
    addNotifPopupVector({"Path ", (std::string)filePath.filename(), " copied in clipboard"}, {GREEN, WHITE, GREEN});
}
