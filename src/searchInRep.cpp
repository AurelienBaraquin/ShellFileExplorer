/*
** EPITECH PROJECT, 2023
** ShellFileExplorer
** File description:
** searchInRep
*/

#include "my.hpp"

std::string searchInCurrentRep(const std::string& toSearch, std::filesystem::path currentPath)
{
    std::string command = "find " + currentPath.string() + " -maxdepth 1 -not -path '*/.*' -name \"" + toSearch + "*\"";
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("Erreur lors de l'exécution de la commande");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        std::filesystem::path path(buffer.data());
        if (currentPath.filename().string() != path.filename().string().substr(0, path.filename().string().size() - 1))
            result += path.filename().string();
    }
    return result;
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
        mvprintw(1, 0, "Search : %s", search.c_str());
        print_files({0, 2}, cursor, global->path, files);
        nb_files = (int)files.size() - 1;
        refresh();
        
    }
}
