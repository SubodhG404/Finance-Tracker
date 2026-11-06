#include "FinanceTracker.h"
#include <vector>
#include <iostream>
#include "Utils.h"
#include "Menu.h"
#include <algorithm>
int main()
{

    int choice{0};
    const int consoleWidth = 80;
    FinanceTracker f;
    do
    {
        printMenu();
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = 0; // falls to "Invalid choice"
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            std::string type, category, description;
            double amount;
            std::cout << "Enter type (e.g., Income/Expense): ";
            std::cin >> type;
            std::transform(type.begin(), type.end(), type.begin(), ::tolower);
            type[0] = std::toupper(type[0]);

            std::cout << "Enter Amount:";
            std::cin >> amount;

            std::cout << "Enter Category:";
            std::cin >> std::ws;
            std::getline(std::cin, category);

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
            std::string query;
            std::cout << "Enter keyword like category or description :";
            std::cin >> std::ws;
            std::getline(std::cin, query);
            f.searchTransactions(query);
            break;
        }
        case 7:
        {
            std::string month;
            double budget;
            std::cout << "Enter Month in YYYY-MM format:";
            std::cin >> month;
            std::cout << "Enter Budget :";
            std::cin >> budget;

            f.setBudget(month, budget);
            break;
        }
        case 8:
        {
            std::string month;
            std::cout << "Enter Month in YYYY-MM format:";
            std::cin >> month;
            f.checkBudget(month);
            break;
        }

        case 9:
        {
            std::cout << "\nExiting......\n";
            f.saveTransactions();
            f.saveMonthlyBudgets();
            break;
        }
        default:
            std::cout << "\nInvalid choice. Please try again.\n";
            break;
        }
    } while (choice != 9);

    return 0;
}