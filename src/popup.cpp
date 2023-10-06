/*
** EPITECH PROJECT, 2023
** ShellFileExplorer
** File description:
** popup
*/

#include "my.hpp"

//* clear_ is true by default / messageColor and waitKeyColor are 7 by default
void FullScreenPopup(const std::string& message, bool clear_, color messageColor, color waitKeyColor)
{
    if (clear_)
        clear();
    if (messageColor != 7)
        attron(COLOR_PAIR(messageColor));
    print_text({(WIDTH / 2 - (int)message.size() / 2), HEIGHT / 2 - 1}, message);
    if (messageColor != 7)
        attroff(COLOR_PAIR(messageColor));
    if (waitKeyColor != 7)
        attron(COLOR_PAIR(waitKeyColor));
    print_text({WIDTH / 2 - 13, HEIGHT / 2 + 2}, "Press any key to continue...");
    if (waitKeyColor != 7)
        attroff(COLOR_PAIR(waitKeyColor));
    if (clear_)
        wrefresh(stdscr);
    nodelay(stdscr, FALSE);
    getch();
    nodelay(stdscr, TRUE);
}

//* clear_ is true by default / messageColor and waitKeyColor are 7 by default / duration is 2 seconds by default
void FullScreenPopupTimed(const std::string& message, bool clear_, const std::chrono::duration<double> duration, color messageColor, color waitKeyColor)
{
    if (clear_)
        clear();
    if (messageColor != 7)
        attron(COLOR_PAIR(messageColor));
    print_text({(WIDTH / 2 - (int)message.size() / 2), HEIGHT / 2 - 1}, message);
    if (messageColor != 7)
        attroff(COLOR_PAIR(messageColor));
    if (waitKeyColor != 7)
        attron(COLOR_PAIR(waitKeyColor));
    print_text({WIDTH / 2 - 13, HEIGHT / 2 + 2}, "Press any key to continue...");
    if (waitKeyColor != 7)
        attroff(COLOR_PAIR(waitKeyColor));
    if (clear_)
        wrefresh(stdscr);
    nodelay(stdscr, FALSE);
    getch();
    nodelay(stdscr, TRUE);
    std::this_thread::sleep_for(duration);
}

//* clear_ is true by default / messageColor and waitKeyColor are 7 by default
void Popup(const std::string& message, Index pos, bool clear_, color messageColor, color waitKeyColor)
{
    if (clear_)
        clear();
    if (messageColor != 7)
        attron(COLOR_PAIR(messageColor));
    print_text(pos, message);
    if (messageColor != 7)
        attroff(COLOR_PAIR(messageColor));
    if (waitKeyColor != 7)
        attron(COLOR_PAIR(waitKeyColor));
    print_text({WIDTH - 23, HEIGHT - 2}, "Press any key to continue...");
    if (waitKeyColor != 7)
        attroff(COLOR_PAIR(waitKeyColor));
    wrefresh(stdscr);
    nodelay(stdscr, FALSE);
    getch();
    nodelay(stdscr, TRUE);
}

//* clear_ is true by default / messageColor is 7 by default / duration is 2 seconds by default
void PopupTimed(const std::string& message, Index pos, bool clear_, const std::chrono::duration<double> duration, color messageColor)
{
    if (clear_)
        clear();
    if (messageColor != 7)
        attron(COLOR_PAIR(messageColor));
    print_text(pos, message);
    if (messageColor != 7)
        attroff(COLOR_PAIR(messageColor));
    wrefresh(stdscr);
    std::this_thread::sleep_for(duration);
}

struct PopupNoDelayTimedData {
    std::string message;
    Index pos;
    bool clear_;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::duration<double> duration;
    color messageColor;
};

std::vector<PopupNoDelayTimedData> popupNoDelayTimedData;

//* clear_ is true by default / messageColor is 7 by default / duration is 2 seconds by default
void addPopupNoDelayTimed(const std::string& message, Index pos, bool clear_, const std::chrono::duration<double>& duration, color messageColor)
{
    PopupNoDelayTimedData data;
    data.message = message;
    data.pos = pos;
    data.clear_ = clear_;
    data.startTime = std::chrono::steady_clock::now();
    data.duration = duration;
    data.messageColor = messageColor;

    popupNoDelayTimedData.push_back(data);
}

void refreshPopupNoDelayTimed()
{
    auto currentTime = std::chrono::steady_clock::now();
    auto it = popupNoDelayTimedData.begin();
    while (it != popupNoDelayTimedData.end()) {
        const auto& data = *it;
        if (data.clear_)
            clear();
        if (data.messageColor != 7)
            attron(COLOR_PAIR(data.messageColor));
        print_text(data.pos, data.message);
        if (data.messageColor != 7)
            attroff(COLOR_PAIR(data.messageColor));
        wrefresh(stdscr);
        auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - data.startTime);
        if (elapsedTime >= data.duration) {
            it = popupNoDelayTimedData.erase(it);
        } else {
            ++it;
        }
    }
}

void clearPopupNoDelayTimed()
{
    popupNoDelayTimedData.clear();
}

void addNotifPopup(const std::string& message, color color)
{
    addPopupNoDelayTimed(message, {WIDTH - 2 - (int)message.size(), 1}, false, std::chrono::seconds(2), color);
}

void addNotifPopupVector(const std::vector<std::string>& messages, const std::vector<color>& colors)
{
    int totalSize = 0;
    for (size_t i = 0; i < messages.size(); i++)
        totalSize += messages[i].size();
    int x = WIDTH - 2 - totalSize;
    for (size_t i = 0; i < messages.size(); i++) {
        addPopupNoDelayTimed(messages[i], {x, 1}, false, std::chrono::seconds(2), colors[i % colors.size()]);
        x += messages[i].size();
    }
}
