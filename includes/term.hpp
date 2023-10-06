/*
** EPITECH PROJECT, 2023
** ShellFileExplorer
** File description:
** term
*/

#ifndef TERM_HPP_
    #define TERM_HPP_

    #include "my.hpp"

    #define ALLOWED_CHAR " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_+=-*/\\|[]{}()<>.,;:!@#$%^&~`\"\'"

    int isKeyAllowed(const int& key)
    {
        if (key == KEY_BACKSPACE || key == KEY_DC || key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN || key == KEY_END || key == KEY_HOME || key == KEY_PPAGE || key == KEY_NPAGE || key == KEY_ENTER || key == 10 || key == 27 || key == 127)
            return 2;

        const char* keyName = keyname(key);
        if (keyName != nullptr && keyName[0] == '^' && keyName[1] != '\0')
            return 0;

        for (int i = 0; ALLOWED_CHAR[i]; i++)
            if (key == ALLOWED_CHAR[i])
                return 1;

        return 0;
    }

#endif /* !TERM_HPP_ */
