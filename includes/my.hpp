/*
** EPITECH PROJECT, 2023
** Files_ncurses
** File description:
** include
*/

#ifndef INCLUDE_HPP_
    #define INCLUDE_HPP_

    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    #include <map>
    #include <algorithm>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <cstring>
    #include <chrono>
    #include <dirent.h>
    #include <grp.h>
    #include <pwd.h>
    #include <time.h>
    #include <fcntl.h>
    #include <cstdlib>
    #include <filesystem>
    #include <thread>
    #include <stack>
    #include <ncurses.h>

    #include "struct.hpp"
    #include "prototype.hpp"

    using namespace std;

    enum color {
        BLACK = 0,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };

    #define DEFAULT_PATH (std::filesystem::path("/home") / std::string(getlogin()))

    #define WIDTH getmaxx(stdscr)
    #define HEIGHT getmaxy(stdscr)

    #define VERSION "1.0.0"
    #define AUTHOR "Aurelien_#5270"

    #define VERSION_INFO "Version : " VERSION
    #define AUTHOR_INFO "Author : " AUTHOR

    #define PRINT_GUI_INFO print_text({WIDTH - 30, HEIGHT - 3}, VERSION_INFO "\n" AUTHOR_INFO "\nShift + [s] to open Settings")

    #define REDUCE_LAG std::this_thread::sleep_for(std::chrono::milliseconds(60))

#endif /* !INCLUDE_HPP_ */
