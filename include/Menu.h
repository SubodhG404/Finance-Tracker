#pragma once
#include "Utils.h"
void printMenu()
{
    const int consoleWidth = 80;
    std::cout << "\n";
    printCentered("====================================", consoleWidth);
    printCentered("********* MENU *********", consoleWidth);
    printCentered("====================================", consoleWidth);
    printCentered("1. Add Transaction", consoleWidth);
    printCentered("2. View Transactions", consoleWidth);
    printCentered("3. View Transactions by Month", consoleWidth);
    printCentered("4. All-Time Summary", consoleWidth);
    printCentered("5. Monthly Summary", consoleWidth);
    printCentered("6. Exit", consoleWidth);
    printCentered("====================================", consoleWidth);

    // Center the prompt spacing
    std::cout << std::string((consoleWidth - 20) / 2, ' ') << "Enter choice: ";
}