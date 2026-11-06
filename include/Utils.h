#ifndef UTILS_H
#define UTILS_H

#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <sstream>

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

// ---------- Input helpers (Task 9.1) ----------

inline std::string trim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// Reads one whole line. If input is closed (Ctrl+Z / Ctrl+D), exit instead of looping forever.
inline std::string readLine(const std::string &prompt)
{
    std::string line;
    std::cout << prompt;
    if (!std::getline(std::cin, line))
    {
        std::cout << "\nInput closed. Exiting.\n";
        std::exit(0);
    }
    return trim(line);
}

inline int readInt(const std::string &prompt)
{
    while (true)
    {
        std::istringstream iss(readLine(prompt));
        int value;
        char extra;
        if (iss >> value && !(iss >> extra)) // a number, and nothing left over
            return value;
        std::cout << "Invalid input. Please enter a whole number.\n";
    }
}

inline double readDouble(const std::string &prompt, double minValue)
{
    while (true)
    {
        std::istringstream iss(readLine(prompt));
        double value;
        char extra;
        if (iss >> value && !(iss >> extra))
        {
            if (value >= minValue)
                return value;
            std::cout << "Value must be at least " << minValue << ".\n";
        }
        else
        {
            std::cout << "Invalid input. Please enter a number (e.g. 250 or 99.50).\n";
        }
    }
}

// Text that goes into the data file: not empty, and no '|' (it is our field separator).
inline std::string readText(const std::string &prompt, const std::string &fieldName)
{
    while (true)
    {
        std::string text = readLine(prompt);
        if (text.empty())
            std::cout << fieldName << " cannot be empty.\n";
        else if (text.find('|') != std::string::npos)
            std::cout << fieldName << " cannot contain the '|' character.\n";
        else
            return text;
    }
}

// Returns "Income" or "Expense" (case-insensitive input).
inline std::string readType(const std::string &prompt)
{
    while (true)
    {
        std::string t = readLine(prompt);
        std::transform(t.begin(), t.end(), t.begin(), ::tolower);
        if (t == "income")
            return "Income";
        if (t == "expense")
            return "Expense";
        std::cout << "Type must be Income or Expense.\n";
    }
}

// Strict YYYY-MM check: 4 digits, '-', 2 digits, month 01-12.
inline bool isValidMonth(const std::string &m)
{
    if (m.length() != 7 || m[4] != '-')
        return false;
    for (int i : {0, 1, 2, 3, 5, 6})
    {
        if (!std::isdigit(static_cast<unsigned char>(m[i])))
            return false;
    }
    int month = std::stoi(m.substr(5, 2));
    return month >= 1 && month <= 12;
}

inline std::string readMonth(const std::string &prompt)
{
    while (true)
    {
        std::string m = readLine(prompt);
        if (isValidMonth(m))
            return m;
        std::cout << "Invalid month. Use YYYY-MM (e.g. 2026-10).\n";
    }
}
#endif