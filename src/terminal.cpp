/*
** EPITECH PROJECT, 2023
** ShellFileExplorer
** File description:
** terminal
*/

#include "my.hpp"
#include "term.hpp"

struct command_t {
    std::string command;
    std::string commandResult;
    std::filesystem::path commandPath;
    int returnValue;
};

std::vector<command_t> commandList;

int keyManageTerminal(int ch, std::string* currentCommand, int *cursorWriter, int *currentCommandIndex, global_t *global)
{
    if (ch == -1)
        return 0;
    SET_STATE(ch);
    if (ch == MY_KEY_QUIT)
        stop();
    if (ch == MY_KEY_UP) {
        if (commandList.size() > 0 && *currentCommandIndex < (int)commandList.size() - 1) {
            *currentCommandIndex += 1;
            *currentCommand = commandList[commandList.size() - 1 - *currentCommandIndex].command;
        }
        return 0;
    }
    if (ch == MY_KEY_DOWN) {
        if (commandList.size() > 0 && *currentCommandIndex > -1) {
            *currentCommandIndex -= 1;
            if (*currentCommandIndex >= 0)
                *currentCommand = commandList[commandList.size() - 1 - *currentCommandIndex].command;
            else
                *currentCommand = "";
        return 0;
        }
    }
    if (ch == MY_KEY_LEFT) {
        if (*cursorWriter > 0)
            *cursorWriter -= 1;
        return 0;
    }
    if (ch == MY_KEY_RIGHT) {
        if (*cursorWriter < (int)currentCommand->size())
            *cursorWriter += 1;
        return 0;
    }
    if (ch == 263) {
        if (*cursorWriter <= 0)
            return 0;
        *currentCommand = currentCommand->substr(0, *cursorWriter - 1) + currentCommand->substr(*cursorWriter, currentCommand->size());
        *cursorWriter -= 1;
        return 0;
    }
    if (ch == MY_KEY_OPEN) {
        if (currentCommand->size() > 0) {
            command_t newCommand;
            newCommand.command = *currentCommand;
            commandReturn_t tmpReturn = executeCommandInCurrentDirectory(*currentCommand);
            newCommand.commandResult = tmpReturn.output;
            newCommand.returnValue = tmpReturn.returnValue;
            newCommand.commandPath = std::filesystem::current_path();
            commandList.push_back(newCommand);
            *currentCommandIndex = -1;
            *currentCommand = "";
            *cursorWriter = 0;
        }
        return 0;
    }
    if (isKeyAllowed(ch) == 1) {
        *currentCommand = currentCommand->substr(0, *cursorWriter) + (char)ch + currentCommand->substr(*cursorWriter, currentCommand->size());
        *cursorWriter += 1;
        return 0;
    }
    return 0;
}

void print_command(Index pos, command_t command, int maxWidth = WIDTH)
{
    Index defaultPos = pos;
    int printedPathSize = print_path(command.commandPath, pos, maxWidth - pos.x);
    print_colored_text({printedPathSize + 1 + pos.x, pos.y}, command.command, GREEN, maxWidth - pos.x - printedPathSize - 1);
    print_text({pos.x, pos.y + 1}, "->", maxWidth - pos.x - printedPathSize - 1);
    print_colored_text({pos.x + 3, pos.y + 1}, std::to_string(command.returnValue), GREEN);
    pos.y += 2;
    for (int i = 0; i < (int)command.commandResult.size(); i++) {
        if (command.commandResult[i] == '\n') {
            pos.y++;
            pos.x = defaultPos.x;
        } else {
            mvprintw(pos.y, pos.x, "%c", command.commandResult[i]);
            pos.x++;
        }
        if (pos.x >= maxWidth) {
            pos.y++;
            pos.x = defaultPos.x;
        }
    }
}

int print_all_commands(Index pos)
{
    int commandSize = 0;
    int i = 0;
    for (i = 0; i < (int)commandList.size(); i++) {
        print_command({pos.x, pos.y + i + commandSize}, commandList[i]);
        commandSize += std::count(commandList[i].commandResult.begin(), commandList[i].commandResult.end(), '\n');
        commandSize += (commandList[i].commandResult.size() / (WIDTH - pos.x));
    }
    return commandSize + i;
}

void print_currentCommand(const Index& pos, const std::string& command, int cursor = -1, int maxWidth = WIDTH)
{
    int x = pos.x;
    int y = pos.y;
    for (int i = 0; i < (int)command.size(); i++) {
        if (i == cursor)
            attron(A_REVERSE);
        mvprintw(y, x, "%c", command[i]);
        if (i == cursor)
            attroff(A_REVERSE);
        x++;
        if (x >= pos.x + maxWidth) {
            x = pos.x;
            y++;
        }
    }
    if (cursor == (int)command.size()) {
        attron(A_REVERSE);
        mvprintw(y, x, " ");
        attroff(A_REVERSE);
    }
}

void terminal_loop(global_t *global)
{
    const std::string prompt = "$";
    static std::string currentCommand = "";
    static int cursorWriter = 0;
    static int currentCommandIndex = -1;
    while (1) {
        VERIFY_STATE(stateEnum::TERMINAL);
        clear();
        print_path(std::filesystem::current_path(), {0, 0}, WIDTH / 3 - 1);
        print_text({0, 1}, prompt);
        print_currentCommand({(int)prompt.size() + 1, 1}, currentCommand, cursorWriter, WIDTH / 3 - 1);
        drawLine({WIDTH / 3, 0}, LineType::VERTICAL, HEIGHT, '|', color::WHITE);
        if (commandList.size() > 0 && currentCommandIndex >= 0)
            print_command({WIDTH / 3 + 1, 0}, commandList[commandList.size() - 1 - currentCommandIndex], WIDTH);
        else if (commandList.size() > 0)
            print_command({WIDTH / 3 + 1, 0}, commandList[commandList.size() - 1], WIDTH);
        refresh();
        if (keyManageTerminal(getch(), &currentCommand, &cursorWriter, &currentCommandIndex, global) == 1)
            return;
    }
}
