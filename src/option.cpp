/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** option
*/

#include "my.hpp"

int key_option_manage(int ch, global_t *global, int *pos, std::filesystem::path path)
{
    if (ch == MY_KEY_BACK || ch == 27)
        return 1;
    if (ch == MY_KEY_UP && *pos > 0)
        pos[0]--;
    if (ch == MY_KEY_DOWN && *pos < OPTIONS_SIZE - 1)
        pos[0]++;
    if (ch == MY_KEY_SELECT || ch == 10) {
        OPTIONS_TAB[*pos].func(global, path);
        return 1;
    }
    return 0;
}

void option_loop(std::filesystem::path path, std::vector<std::string> files, global_t *global, int cursorFile)
{
    static int cursor = 0;
    std::filesystem::path currentFile = path.filename();
    std::filesystem::path parentPath = path.parent_path();
    while (1) {
        if (key_option_manage(getch(), global, &cursor, path) == 1)
            break;
        clear();
        print_path(parentPath, {0, 0});
        print_files({0, 2}, cursorFile, parentPath, files);
        print_colored_text({get_max_str_size_from_vector(files) + 3, 1}, currentFile.string(), GREEN);
        print_options({get_max_str_size_from_vector(files) + 3, 3}, cursor);
        PRINT_GUI_INFO;
        refresh();
        REDUCE_LAG;
    }
}
