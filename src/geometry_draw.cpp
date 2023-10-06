/*
** EPITECH PROJECT, 2023
** ShellFileExplorer
** File description:
** geometry_draw
*/

#include "my.hpp"

void drawLine(Index pos, LineType lineType, int length, char charLine, color colorPair)
{
    attron(COLOR_PAIR(colorPair));
    if (lineType == LineType::HORIZONTAL) {
        for (int i = 0; i < length; i++)
            mvprintw(pos.y, pos.x + i, "%c", charLine);
    } else if (lineType == LineType::VERTICAL) {
        for (int i = 0; i < length; i++)
            mvprintw(pos.y + i, pos.x, "%c", charLine);
    } else {
        throw std::invalid_argument("Invalid line type");
    }
    attroff(COLOR_PAIR(colorPair));
}
