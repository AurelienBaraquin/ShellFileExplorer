/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** struct
*/

#ifndef STRUCT_HPP_
    #define STRUCT_HPP_

    #include "my.hpp"


const std::vector<std::string> helpText = {
    "Usage: ./SFE [OPTION]...",
    "A simple file explorer",
    "",
    "Options:",
    "  -init\t\t\t\tInitialize the config folder in ~/.config/SFE (need to be done once)",
    "  -d\t\t\t\tOpen the /home/<username> path",
    "  -h\t\t\t\tDisplay this help",
    "  -t\t\t\t\tOpen the program in tty mode\t\t-> not implemented yet",
    "  -v\t\t\t\tDisplay the version of the program",
    "  -p\t\t\t\tOpen the program at the path specified after the option\t\t-> not implemented yet",
    "",
    "Before using the program, you need to use the -init option to initialize the config folder",
    "",
    "Report bugs to <Aurelien_#5270> on Discord"
};

struct Index {
    int x;
    int y;
};

struct FileStackElement {
    std::string path;
    int position;
};

enum sortTypeEnum {
    SORT_BY_NAME,
    SORT_BY_NAME_REVERSE,
    DONT,
};

namespace SortType {
    std::string toString(sortTypeEnum type);
    sortTypeEnum fromString(const std::string& str);

    extern const std::string SORT_BY_NAME_STR;
    extern const std::string SORT_BY_NAME_REVERSE_STR;
    extern const std::string DONT_STR;
}

enum class stateEnum {
    FILE_EXPLORER,
    TERMINAL
};

static const std::unordered_map<int, stateEnum> stateMap = {
    {KEY_F(1), stateEnum::TERMINAL},
    {KEY_F(2), stateEnum::FILE_EXPLORER}
};

#define SET_STATE(ch) try { global->state = stateMap.at(ch); } catch (const std::out_of_range& e) {}
#define VERIFY_STATE(currentState) if (global->state != currentState) return;

typedef struct global_s {
    bool TTY_MODE = false;

    std::filesystem::path path;
    std::vector<std::string> files;
    sortTypeEnum sort_type = SORT_BY_NAME;
    int pos;
    std::vector<int> pos_stack;
    std::vector<FileStackElement> file_stack;

    std::filesystem::path copy_path;

    stateEnum state = stateEnum::FILE_EXPLORER;
} global_t;

#define GLOBAL_PATH global->path / global->files[global->pos]

struct FileOption {
    std::string name;
    void (*func)(global_t *global, std::filesystem::path filePath);
};

void rename_file(global_t *global, std::filesystem::path filePath);
void delete_file(global_t *global, std::filesystem::path filePath);
void open_file(global_t *global, std::filesystem::path filePath);
void copy_file(global_t *global, std::filesystem::path filePath);
void paste_file(global_t *global, std::filesystem::path filePath);
void move_file(global_t *global, std::filesystem::path filePath);
void new_file(global_t *global, std::filesystem::path filePath);
void new_folder(global_t *global, std::filesystem::path filePath);
void copy_path(global_t *global, std::filesystem::path filePath);

const FileOption OPTIONS_TAB[] = {
    {"Open", open_file},
    {"Rename", rename_file},
    {"Delete", delete_file},
    {"Copy", copy_file},
    {"Paste", paste_file},
    {"Move", move_file},
    {"CopyPath", copy_path},
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
#define MY_KEY_SORT_FILES getKey("Sort Files")
#define MY_KEY_SEARCH getKey("Search")



#define MY_KEY_LEFT MY_KEY_BACK
#define MY_KEY_RIGHT MY_KEY_SELECT


struct commandReturn_t {
    std::string output;
    int returnValue;
};


#endif /* !STRUCT_HPP_ */
