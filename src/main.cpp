/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** main
*/

#include "my.hpp"

global_t *create_struct(void);

void stop(void)
{
    endwin();
    saveKeyOnFile("~/.config/SFE/key_settings");
    exit(0);
}

void key_back_function(global_t *global)
{
    if (global->path == DEFAULT_PATH) {
        addNotifPopup("Can't go back", RED);
        return;
    }
    global->file_stack.push_back({global->path, global->pos});
    global->path = global->path.parent_path();
    global->pos = global->pos_stack.back();
    global->pos_stack.pop_back();
    refresh_directory(global->path);
}

void key_manage(int ch, global_t *global)
{
    SET_STATE(ch);
    if (ch == MY_KEY_QUIT)
        stop();
    if (ch == MY_KEY_SORT_FILES)
        change_sort(global);
    if (ch == MY_KEY_NEW_FILE) {
        switch (get_choice("Select a file type :", {"File", "Directory", "Cancel"})) {
            case 0:
                new_file(global, GLOBAL_PATH);
                break;
            case 1:
                new_folder(global, GLOBAL_PATH);
                break;
            default:
                break;
        }
    }
    if (ch == MY_KEY_BACK)
        key_back_function(global);
    if (ch == MY_KEY_UP && global->pos > 0)
        global->pos--;
    if (ch == MY_KEY_DOWN && global->pos < (int)global->files.size() - 1)
        global->pos++;
    if (ch == MY_KEY_SELECT)
        option_loop(global->path / global->files[global->pos], global->files, global, global->pos);
    if (ch == MY_KEY_SETTINGS)
        settings_loop();
    if (ch == MY_KEY_SEARCH)
        search_loop(global);
    for (int i = 0; i < OPTIONS_SIZE; i++)
        if (ch == getKey(OPTIONS_TAB[i].name))
            OPTIONS_TAB[i].func(global, GLOBAL_PATH);
}

void fileExplorerLoop(global_t *global)
{
    while (1) {
        VERIFY_STATE(stateEnum::FILE_EXPLORER);
        cursor_fix(&global->pos, {0, (int)global->files.size() - 1});
        key_manage(getch(), global);
        get_files(global);
        clear();
        print_path(global->path, {0, 0});
        print_files({0, 2}, global->pos, global->path, global->files);
        refresh();
    }
}

void cursor_fix(int *cursor, Index min_max)
{
    //min = x, max = y
    if (*cursor < min_max.x)
        *cursor = min_max.x;
    if (*cursor > min_max.y)
        *cursor = min_max.y;
}

void printHelp(const std::vector<std::string>& helpText)
{
    for (const std::string& line : helpText) {
        std::cout << line << std::endl;
    }
}

int main(int ac, char **av)
{
    if (ac == 2 && (string)av[1] == "-init")
        return (init_config_folder());
    global_t *global = create_struct();
    for (int i = 1; i < ac; i++) {
        switch (av[i][1]) {
            case 'd':
                global->path = DEFAULT_PATH;
                break;
            case 'h':
                printHelp(helpText);
                return 0;
            case 'v':
                std::cout << "Version : " << VERSION << std::endl;
                return 0;
            default:
                break;
        }
    }
    endwin();
    init_ncurses();
    if (ac == 2 && (string)av[1] == "-t")
        global->TTY_MODE = true;
    addNotifPopup("Welcome to SFE !", YELLOW);
    while (1) {
        // cursor_fix(&global->pos, {0, (int)global->files.size() - 1});
        // fileExplorerLoop(global);
        statesMap.at(global->state)(global);
    }
    return 0;
}
