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

void key_manage(int ch, global_t *global)
{
    if (ch == MY_KEY_QUIT)
        stop();
    if (ch == MY_KEY_SORT_FILES)
        change_sort(global);
    if (ch == MY_KEY_NEW_FILE)
        new_file(global);
    if (ch == MY_KEY_NEW_FOLDER)
        new_folder(global);
    if (ch == MY_KEY_BACK)
        key_back_function(global);
    if (ch == MY_KEY_UP && global->pos > 0)
        global->pos--;
    if (ch == MY_KEY_DOWN && global->pos < (int)global->files.size() - 1)
        global->pos++;
    if (ch == MY_KEY_SELECT)
        option_loop(global);
    if (ch == MY_KEY_SETTINGS)
        settings_loop(global);
    for (int i = 0; i < OPTIONS_SIZE; i++)
        if (ch == getKey(OPTIONS_TAB[i].name))
            OPTIONS_TAB[i].func(global);
}

void loop(global_t *global)
{
    key_manage(getch(), global);
    clear();
    print_path(global, {0, 0});
    print_files(global, {0, 2});
    PRINT_GUI_INFO;
    refresh();
    REDUCE_LAG;
}

void common_fix(global_t *global)
{
    if (global->pos < 0)
        global->pos = 0;
    if (global->pos > (int)global->files.size() - 1)
        global->pos = (int)global->files.size() - 1;
}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    init_ncurses();
    endwin();
    global_t *global = create_struct();
    while (1) {
        common_fix(global);
        loop(global);
    }
    return (0);
}
