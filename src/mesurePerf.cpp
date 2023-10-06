/*
** EPITECH PROJECT, 2023
** ShellFileExplorer
** File description:
** mesurePerf
*/

#include "my.hpp"

double mesureExecutionSpeed(void)
{
    static double speed = 0.0;
    if (speed != 0.0)
        return 100 - speed;
    auto start = std::chrono::high_resolution_clock::now();

    int j = 0;
    for (int i = 0; i < 1000000; i++) {
        j += i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double executionTime = duration.count() / 1000.0;

    speed = 100.0 - (executionTime / 100.0) * 100.0;

    if (speed < 0.0) {
        speed = 0.0;
    } else if (speed > 100.0) {
        speed = 100.0;
    }

    return 100 - speed;
}
