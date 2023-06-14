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
    if (global->path == DEFAULT_PATH)
        return;
    global->file_stack.push_back({global->path, global->pos});
    global->path = global->path.parent_path();
    global->pos = global->pos_stack.back();
    global->pos_stack.pop_back();
}

void change_sort(global_t *global)
{
    global->sort_type++;
    if (global->sort_type > (int)sizeof(sortType) - 1)
        global->sort_type = 0;
}

void search_loop(global_t *global)
{
    static string search = "";
    int ch = 0;
    int cursor = 0;
    int nb_files = 0;
    vector<string> files;
    while (ch != MY_KEY_QUIT && ch != MY_KEY_BACK) {
        files = split(searchInCurrentRep(search, global->path), '\n');
        ch = getch();
        if (ch == KEY_BACKSPACE && search.size() > 0)
            search.pop_back();
        if (ch >= 32 && ch <= 126)
            search += ch;
        if (ch == MY_KEY_UP && cursor > 0)
            cursor--;
        if (ch == MY_KEY_DOWN && cursor < nb_files)
            cursor++;
        if (ch == MY_KEY_SELECT || ch == MY_KEY_OPEN) {
            option_loop(global->path / files[cursor], files, global, cursor);
            break;
        }
        cursor_fix(&cursor, {0, nb_files});
        clear();
        print_path(global->path, {0, 0});
        PRINT_GUI_INFO;
        mvprintw(1, 0, "Search : %s", search.c_str());
        print_files({0, 2}, cursor, global->path, files);
        nb_files = (int)files.size() - 1;
        refresh();
        REDUCE_LAG;
    }
}

void key_manage(int ch, global_t *global)
{
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
        settings_loop(global);
    if (ch == MY_KEY_SEARCH)
        search_loop(global);
    for (int i = 0; i < OPTIONS_SIZE; i++)
        if (ch == getKey(OPTIONS_TAB[i].name))
            OPTIONS_TAB[i].func(global, GLOBAL_PATH);
}

void loop(global_t *global)
{
    key_manage(getch(), global);
    get_files(global);
    clear();
    print_path(global->path, {0, 0});
    print_files({0, 2}, global->pos, global->path, global->files);
    PRINT_GUI_INFO;
    refresh();
    REDUCE_LAG;
}

void cursor_fix(int *cursor, Index min_max)
{
    //min = x, max = y
    if (*cursor < min_max.x)
        *cursor = min_max.x;
    if (*cursor > min_max.y)
        *cursor = min_max.y;
}

const std::vector<std::string> helpText = {
    "Usage: ./SFE [OPTION]...",
    "A simple file explorer",
    "",
    "Options:",
    "  -init\t\t\t\tInitialize the config folder in ~/.config/SFE (need to be done once)",
    "  -d\t\t\t\tOpen the default path",
    "  -h\t\t\t\tDisplay this help",
    "  -t\t\t\t\tOpen the program in tty mode\t\t-> not implemented yet",
    "  -v\t\t\t\tDisplay the version of the program",
    "  -p\t\t\t\tOpen the program at the path specified after the option\t\t-> not implemented yet",
    "",
    "Before using the program, you need to use the -init option to initialize the config folder",
    "",
    "Report bugs to <Aurelien_#5270> on Discord"
};

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
    init_ncurses();
    endwin();
    if (ac == 2 && (string)av[1] == "-t")
        global->TTY_MODE = true;
    while (1) {
        cursor_fix(&global->pos, {0, (int)global->files.size() - 1});
        loop(global);
    }
    return 0;
}
