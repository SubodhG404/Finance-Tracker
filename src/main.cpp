#include "FinanceTracker.h"
#include <vector>
#include <iostream>
#include "Utils.h"
#include "Menu.h"
int main()
{

    int choice{0};
    const int consoleWidth = 80;
    FinanceTracker f;
    do
    {
        printMenu();
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::string type, category, description;
            double amount;
            std::cout << "Enter type (e.g., Income/Expense): ";
            std::cin >> type;

            std::cout << "Enter Amount:";
            std::cin >> amount;

            std::cout << "Enter Category:";
            std::cin >> category;
            std::cin.ignore(); // clearing input buffer
            std::cout << "Enter Description:";
            std::getline(std::cin, description);

            f.addTransaction(description, amount, type, category, getCurrentDate());

            break;
        }
        case 2:
        {
            f.displayAllTransactions();
            break;
        }
        case 3:
        {
            std::string month;
            std::cout << "Enter Month in YYYY-MM format:";
            std::cin >> month;
            f.displayTransactionsByMonth(month);
            break;
        }
        case 4:
            f.calculateSummary(); // all time
            break;
        case 5:
        {
            std::string month;
            std::cout << "Enter Month in YYYY-MM format:";
            std::cin >> month;
            f.calculateMonthlySummary(month);
            break;
        }
        case 6:
        {
            std::cout << "\nExiting......\n";
            f.saveTransactions();
            break;
        }
        default:
            std::cout << "\nInvalid choice. Please try again.\n";
            break;
        }
    } while (choice != 4);

    return 0;
}