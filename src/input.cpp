/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** input
*/

#include "my.hpp"

std::string get_input(const std::string& ask, const std::string& default_value)
{
    int y, x;
    getmaxyx(stdscr, y, x);

    std::string input = default_value;
    int ch;
    while ((ch = getch()) != '\n') {
        if (ch == MY_KEY_QUIT)
            return std::string();
        if (ch >= 32 && ch <= 126)
            input.push_back(ch);
        if (ch == KEY_BACKSPACE && input.size() > 0)
            input.pop_back();
        clear();
        mvprintw(y / 2, (x / 2) - (ask.size() / 2), "%s", ask.c_str());
        mvprintw(y / 2 + 1, (x / 2) - (input.size() / 2), "%s", input.c_str());
        refresh();
        
    }
    return input;
}

int get_choice(const std::string& ask, const std::vector<std::string>& choices)
{
    int y, x;
    getmaxyx(stdscr, y, x);

    int choice = 0;
    int ch;
    while ((ch = getch()) != MY_KEY_SELECT) {
        if (ch == MY_KEY_OPEN)
            break;
        if (ch == MY_KEY_QUIT)
            return -1;
        if (ch == MY_KEY_UP && choice > 0)
            choice--;
        if (ch == MY_KEY_DOWN && choice < (int)choices.size() - 1)
            choice++;
        clear();
        mvprintw(y / 2, (x / 2) - (ask.size() / 2), "%s", ask.c_str());
        for (std::vector<std::string>::size_type i = 0; i < choices.size(); i++) {
            if ((int)i == choice)
                attron(A_REVERSE);
            mvprintw(y / 2 + i + 1, (x / 2) - (choices[i].size() / 2), "%s", choices[i].c_str());
            attroff(A_REVERSE);
        }
        refresh();
        
    }
    return choice;
}