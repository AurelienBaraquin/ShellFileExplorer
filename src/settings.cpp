/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** settings
*/

#include "my.hpp"

int key_settings_manage(int *cursor, int ch)
{
    if (ch == MY_KEY_UP && *cursor > 0)
        *cursor -= 1;
    if (ch == MY_KEY_DOWN && *cursor < getNbKeys() - 1)
        *cursor += 1;
    if (ch == MY_KEY_BACK || ch == MY_KEY_QUIT)
        return 1;
    if (ch == MY_KEY_SELECT || ch == MY_KEY_OPEN) {
        string set_key = get_input("Enter the new key:", "");
        int char_key = set_key[0];
        setKey(getKey_byIndex(*cursor), char_key);
    }
    if (ch == 'D')
        setDefaultKeys();
    return 0;
}

void settings_loop(void)
{
    static int cursor = 0;
    while (1) {
        if (key_settings_manage(&cursor, getch()))
            break;
        clear();
        print_settings({1, 1}, cursor);
        print_text({WIDTH / 2, 1}, "Press Shift + [d] to\nreset keys to default");
        PRINT_GUI_INFO;
        refresh();
        
    }
}