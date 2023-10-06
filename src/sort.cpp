/*
** EPITECH PROJECT, 2023
** ShellFileExplorer
** File description:
** sort
*/

#include "my.hpp"

namespace SortType {
    const std::string SORT_BY_NAME_STR = "SORT BY NAME";
    const std::string SORT_BY_NAME_REVERSE_STR = "SORT BY NAME REVERSE";
    const std::string DONT_STR = "NOT SORTED";

    std::string toString(sortTypeEnum type) {
        switch (type) {
            case SORT_BY_NAME:
                return SORT_BY_NAME_STR;
            case SORT_BY_NAME_REVERSE:
                return SORT_BY_NAME_REVERSE_STR;
            case DONT:
                return DONT_STR;
            default:
                return "Unknown";
        }
    }

    sortTypeEnum fromString(const std::string& str) {
        if (str == SORT_BY_NAME_STR) {
            return SORT_BY_NAME;
        } else if (str == SORT_BY_NAME_REVERSE_STR) {
            return SORT_BY_NAME_REVERSE;
        } else if (str == DONT_STR) {
            return DONT;
        } else {
            return static_cast<sortTypeEnum>(-1);
        }
    }
}

void change_sort(global_t *global)
{
    if (global->sort_type == static_cast<sortTypeEnum>(-1) || global->sort_type == DONT)
        global->sort_type = SORT_BY_NAME;
    else
        global->sort_type = static_cast<sortTypeEnum>(global->sort_type + 1);
    addNotifPopupVector({"Sort type changed to ", SortType::toString(global->sort_type)}, {WHITE, GREEN});
}
