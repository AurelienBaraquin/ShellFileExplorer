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
