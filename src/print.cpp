/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** print
*/

#include "my.hpp"

struct FileColor {
    std::filesystem::file_type fileType;
    int colorPair;
};

const std::vector<FileColor> FILE_COLORS = {
    {std::filesystem::file_type::regular, WHITE},
    {std::filesystem::file_type::directory, BLUE},
    {std::filesystem::file_type::symlink, MAGENTA},
    {std::filesystem::file_type::block, CYAN},
    {std::filesystem::file_type::character, RED},
    {std::filesystem::file_type::fifo, GREEN},
    {std::filesystem::file_type::socket, YELLOW}
};

void print_files(global_t *global, struct Index pos)
{
    std::vector<std::string>::size_type i = 0;
    int j = 0;
    if (global->pos + pos.y + 1 > HEIGHT)
        i = global->pos - HEIGHT + pos.y + 1;
    get_files(global);
    for (; i < global->files.size(); i++, j++) {
        if ((int)i == global->pos)
            attron(A_REVERSE);
        const std::filesystem::path filePath = global->path / global->files[i];
        const std::filesystem::file_status fileStatus = std::filesystem::status(filePath);
        for (const FileColor& fileColor : FILE_COLORS) {
            if (fileStatus.type() == fileColor.fileType) {
                attron(COLOR_PAIR(fileColor.colorPair));
                break;
            }
        }
        mvprintw(j + pos.y, pos.x, "%s", global->files[i].c_str());
        attroff(A_REVERSE);
        for (const FileColor& fileColor : FILE_COLORS) {
            if (fileStatus.type() == fileColor.fileType) {
                attroff(COLOR_PAIR(fileColor.colorPair));
                break;
            }
        }
    }
}

void print_options(global_t *global, struct Index pos, int cursor)
{
    (void)global;
    int i = 0;
    int j = 0;
    if (cursor + pos.y + 1 > HEIGHT)
        i = cursor - HEIGHT + pos.y + 1;
    for (; i < OPTIONS_SIZE; i++, j++) {
        if ((int)i == cursor)
            attron(A_REVERSE);
        mvprintw(j + pos.y, pos.x, "%s", OPTIONS_TAB[i].name.c_str());
        attroff(A_REVERSE);
    }
}

void print_path(global_t *global, struct Index pos)
{
    const std::filesystem::path Parent = global->path.parent_path();
    const std::string currentDir = global->path.filename().string();
    attron(COLOR_PAIR(RED));
    mvprintw(pos.y, pos.x, "%s/", Parent.c_str());
    attroff(COLOR_PAIR(RED));
    attron(COLOR_PAIR(YELLOW));
    mvprintw(pos.y, pos.x + Parent.string().size() + 1, "%s", currentDir.c_str());
    attroff(COLOR_PAIR(YELLOW));
}

void print_text(struct Index pos, std::string text)
{
    std::vector<std::string> lines = split(text, '\n');
    for (std::vector<std::string>::size_type i = 0; i < lines.size(); i++) {
        mvprintw(pos.y + i, pos.x, "%s", lines[i].c_str());
    }
}

void print_colored_text(struct Index pos, std::string text, int color)
{
    std::vector<std::string> lines = split(text, '\n');
    attron(COLOR_PAIR(color));
    for (std::vector<std::string>::size_type i = 0; i < lines.size(); i++) {
        mvprintw(pos.y + i, pos.x, "%s", lines[i].c_str());
    }
    attroff(COLOR_PAIR(color));
}

void print_settings(Index pos, int cursor)
{
    std::unordered_map<std::string, int> keyMap = get_keys_Map();
    std::vector<std::string> keys;
    std::vector<std::string> actions;
    int i = 0;
    int j = 0;
    if (cursor + pos.y + 1 > HEIGHT)
        i = cursor - HEIGHT + pos.y + 1;
    for (auto it = keyMap.begin(); it != keyMap.end(); it++) {
        keys.push_back(it->first);
        actions.push_back(std::to_string(it->second));
    }
    for (; i < (int)keys.size(); i++, j++) {
        mvprintw(pos.y + j, pos.x, "%s", (keys[i] + ":").c_str());
        if (i == cursor)
            attron(A_REVERSE);
        attron(COLOR_PAIR(YELLOW));
        int current_key = (int)std::stoi(actions[i]);
        mvprintw(pos.y + j, pos.x + 15, "%s", key_to_str(current_key).c_str());
        attroff(COLOR_PAIR(YELLOW));
        attroff(A_REVERSE);
    }
}