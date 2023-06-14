/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** init_ncurses
*/

#include "my.hpp"

void init_colors()
{
    start_color();

    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
}

void init_ncurses(void)
{
    initscr();
    start_color();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    init_colors();
}

global_t *create_struct(void)
{
    setDefaultKeys();
    setKeyFromFile("~/.config/SFE/key_settings");
    global_t *global = new global_t;
    global->path = executeCommand("pwd").substr(0, executeCommand("pwd").size() - 1);
    get_files(global);
    global->pos = 0;
    global->pos_stack.push_back(0);
    global->file_stack.push_back({(string)DEFAULT_PATH, 0});
    global->copy_path = "";
    return global;
}
