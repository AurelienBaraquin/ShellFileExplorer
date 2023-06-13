/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** warning
*/

#include "my.hpp"

void print_warning(std::string str)
{
    clear();
    int x, y;
    getmaxyx(stdscr, y, x);
    attron(COLOR_PAIR(RED));
    mvprintw(y / 2, (x / 2) - (str.length() / 2), "%s", str.c_str());
    attroff(COLOR_PAIR(RED));
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
