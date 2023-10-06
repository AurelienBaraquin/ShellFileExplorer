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
    #include <sys/wait.h>
    #include <unordered_map>

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

    //* POPUP
    void FullScreenPopup(const std::string& message, bool clear_ = false, color messageColor = WHITE, color waitKeyColor = WHITE);
    void FullScreenPopupTimed(const std::string& message, bool clear_ = false, const std::chrono::duration<double> duration = std::chrono::seconds(2), color messageColor = WHITE, color waitKeyColor = WHITE);
    void Popup(const std::string& message, Index pos, bool clear_ = false, color messageColor = WHITE, color waitKeyColor = WHITE);
    void PopupTimed(const std::string& message, Index pos, bool clear_ = false, const std::chrono::duration<double> duration = std::chrono::seconds(2), color messageColor = WHITE);
    void addPopupNoDelayTimed(const std::string& message, Index pos, bool clear_ = false, const std::chrono::duration<double>& duration = std::chrono::seconds(2), color messageColor = WHITE);
    void refreshPopupNoDelayTimed();
    void clearPopupNoDelayTimed();
    void addNotifPopup(const std::string& message, color color = WHITE);
    void addNotifPopupVector(const std::vector<std::string>& messages, const std::vector<color>& colors = {WHITE});

    //* DRAW

    enum class LineType {
        HORIZONTAL,
        VERTICAL
    };

    void drawLine(Index pos, LineType lineType, int length, char charLine = '*', color colorPair = color::WHITE);

    #define refresh() refreshPopupNoDelayTimed();refresh();REDUCE_LAG

    #define DEFAULT_PATH (std::filesystem::path("/home") / std::string(getlogin()))

    #define WIDTH (int)getmaxx(stdscr)
    #define HEIGHT (int)getmaxy(stdscr)

    #define VERSION "1.1.1"
    #define AUTHOR "Aurelien_#5270"

    #define VERSION_INFO "Version : " VERSION
    #define AUTHOR_INFO "Author : " AUTHOR

    #define PRINT_GUI_INFO print_text({WIDTH - 30, HEIGHT - 3}, VERSION_INFO "\n" AUTHOR_INFO "\nShift + [s] to open Settings")

    #define REDUCE_LAG std::this_thread::sleep_for(std::chrono::milliseconds(100))

#endif /* !INCLUDE_HPP_ */

//TODO : checkpoint path use number key to go to a fixed checkpoint
//TODO : add a way to cut files
//TODO : do TTY mode (with emacs or nano to text edit...) using -t flag 

//TODO : config folder to save settings, checkpoint and cutted files
/*
ALL IN CONFIG FOLDER :
    - key_settings // DONE
    - checkpoint
    - cutted files


Use -init flag to create config folder // DONE
*/