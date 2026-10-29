#ifndef UTILS_H
#define UTILS_H

#include <ctime>
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

inline std::string getCurrentDate()
{
    std::time_t now = std::time(nullptr);
    char buffer[11]; // Holds 10 characters + null terminator ('YYYY-MM-DD\0')

    // %Y = 4-digit year, %m = 2-digit month (01-12), %d = 2-digit day (01-31)
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&now));

    return std::string(buffer);
}
#endif