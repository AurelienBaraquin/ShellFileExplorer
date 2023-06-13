/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** option
*/

#include "my.hpp"

int key_option_manage(int ch, global_t *global, int *pos)
{
    if (ch == MY_KEY_BACK || ch == 27)
        return 1;
    if (ch == MY_KEY_UP && *pos > 0)
        pos[0]--;
    if (ch == MY_KEY_DOWN && *pos < OPTIONS_SIZE - 1)
        pos[0]++;
    if (ch == MY_KEY_SELECT || ch == 10) {
        OPTIONS_TAB[*pos].func(global);
        return 1;
    }
    return 0;
}

void option_loop(global_t *global)
{
    static int cursor = 0;
    std::filesystem::path currentFile = global->files[global->pos];
    while (1) {
        if (key_option_manage(getch(), global, &cursor) == 1)
            break;
        clear();
        print_path(global, {0, 0});
        print_files(global, {0, 2});
        print_colored_text({WIDTH / 4, 1}, currentFile.string(), GREEN);
        print_options(global, {WIDTH / 4, 3}, cursor);
        PRINT_GUI_INFO;
        refresh();
        REDUCE_LAG;
    }
}
