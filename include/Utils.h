#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <cstdlib>

inline void printCentered(const std::string &text, int width = 80)
{
    if (text.length() >= static_cast<size_t>(width))
    {
        std::cout << text << '\n';
        return;
    }
    int padding = (width - text.length()) / 2;
    std::cout << std::string(padding, ' ') << text << '\n';
}

inline void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#endif