/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** struct
*/

#ifndef STRUCT_HPP_
    #define STRUCT_HPP_

    #include "my.hpp"

struct Index {
    int x;
    int y;
};

struct FileStackElement {
    std::string path;
    int position;
};

enum sortType {
    SORT_BY_NAME,
    SORT_BY_NAME_REVERSE,
    DONT,
};

typedef struct global_s {
    std::filesystem::path path;
    std::vector<std::string> files;
    int sort_type = SORT_BY_NAME;
    int pos;
    std::vector<int> pos_stack;
    std::vector<FileStackElement> file_stack;

    std::filesystem::path copy_path;
} global_t;

struct FileOption {
    std::string name;
    void (*func)(global_t *global);
};

void rename_file(global_t *global);
void delete_file(global_t *global);
void open_file(global_t *global);
void copy_file(global_t *global);
void paste_file(global_t *global);
void move_file(global_t *global);
void new_file(global_t *global);
void new_folder(global_t *global);

const FileOption OPTIONS_TAB[] = {
    {"Open", open_file},
    {"Rename", rename_file},
    {"Delete", delete_file},
    {"Copy", copy_file},
    {"Paste", paste_file},
    {"Move", move_file},
};

#define OPTIONS_SIZE (int)(sizeof(OPTIONS_TAB) / sizeof(FileOption))

#define MY_KEY_OPEN getKey("Open")
#define MY_KEY_RENAME getKey("Rename")
#define MY_KEY_DELETE getKey("Delete")
#define MY_KEY_UP getKey("Up")
#define MY_KEY_DOWN getKey("Down")
#define MY_KEY_SELECT getKey("Select")
#define MY_KEY_BACK getKey("Back")
#define MY_KEY_QUIT getKey("Quit")
#define MY_KEY_SETTINGS getKey("Settings")
#define MY_KEY_COPY getKey("Copy")
#define MY_KEY_PASTE getKey("Paste")
#define MY_KEY_MOVE getKey("Move")
#define MY_KEY_NEW_FILE getKey("New File")
#define MY_KEY_NEW_FOLDER getKey("New Folder")
#define MY_KEY_SORT_FILES getKey("Sort Files")

#endif /* !STRUCT_HPP_ */
