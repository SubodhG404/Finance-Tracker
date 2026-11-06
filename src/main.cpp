#include "FinanceTracker.h"
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
        choice = readInt(std::string((consoleWidth - 20) / 2, ' ') + "Enter choice: ");

        switch (choice)
        {
        case 1:
        {
            std::string type = readType("Enter type (Income/Expense): ");
            double amount = readDouble("Enter Amount: ", 0.01);
            std::string category = readText("Enter Category: ", "Category");
            std::string description = readText("Enter Description: ", "Description");

            f.addTransaction(description, amount, type, category, getCurrentDate());
            break;
        }
        case 2:
            f.displayAllTransactions();
            break;
        case 3:
            f.displayTransactionsByMonth(readMonth("Enter Month in YYYY-MM format: "));
            break;
        case 4:
            f.calculateSummary();
            break;
        case 5:
            f.calculateMonthlySummary(readMonth("Enter Month in YYYY-MM format: "));
            break;
        case 6:
            f.searchTransactions(readText("Enter keyword like category or description: ", "Keyword"));
            break;
        case 7:
        {
            std::string month = readMonth("Enter Month in YYYY-MM format: ");
            double budget = readDouble("Enter Budget: ", 0);
            f.setBudget(month, budget);
            break;
        }
        case 8:
            f.checkBudget(readMonth("Enter Month in YYYY-MM format: "));
            break;
        case 9:
            std::cout << "\nExiting......\n";
            f.saveTransactions();
            f.saveMonthlyBudgets();
            break;
        default:
            std::cout << "\nInvalid choice. Please try again.\n";
            break;
        }
    } while (choice != 9);

    return 0;
}