#include <iostream>
#include <string>
#include "Transaction.h"
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <fstream>
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Helper function to calculate padding and print centered text
void printCentered(const std::string &text, int width = 80)
{
    if (text.length() >= static_cast<size_t>(width))
    {
        std::cout << text << '\n';
        return;
    }
    int padding = (width - text.length()) / 2;
    std::cout << std::string(padding, ' ') << text << '\n';
}

void showSummary(const std::vector<Transaction> &transactions)
{
    double income = 0;
    double expense = 0;

    for (const Transaction &t : transactions)
    {
        if (t.getType() == "Income")
        {
            income += t.getAmount();
        }
        else if (t.getType() == "Expense")
        {
            expense += t.getAmount();
        }
    }

    std::ostringstream incStr, expStr, netStr;
    incStr << std::fixed << std::setprecision(2) << income;
    expStr << std::fixed << std::setprecision(2) << expense;
    netStr << std::fixed << std::setprecision(2) << (income - expense);

    printCentered("----------Monthly Summary----------\n");
    printCentered("Total Income  : Rs. " + incStr.str() + "\n");
    printCentered("Total Expense : Rs. " + expStr.str() + "\n");
    printCentered("Net Balance   : Rs. " + netStr.str() + "\n");
}

int main()
{
    int choice{0};
    const int consoleWidth = 80;
    std::vector<Transaction> transactions;

    int nextId = 1;
    do
    {
        std::cout << "\n";
        printCentered("====================================", consoleWidth);
        printCentered("*** MENU ***", consoleWidth);
        printCentered("====================================", consoleWidth);
        printCentered("1. Add Transaction", consoleWidth);
        printCentered("2. View Transactions", consoleWidth);
        printCentered("3. Monthly Summary", consoleWidth);
        printCentered("4. Exit", consoleWidth);
        printCentered("====================================", consoleWidth);

        // Center the prompt spacing
        std::cout << std::string((consoleWidth - 20) / 2, ' ') << "Enter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::cout << "\nAdding Transaction......\n";
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

            Transaction newTx(nextId++, type, amount, category, description);
            transactions.push_back(newTx);

            std::cout << "\n Transaction Added Successfully";
            break;
        }
        case 2:
        {
            std::cout << "\nViewing Transactions......\n";
            if (transactions.empty())
            {
                std::cout << "No transactions Recorded yet\n";
            }

            else
            {
                for (const auto &tx : transactions)
                { // doesn't create copies, gives a refence
                    tx.display();
                    std::cout << "--------------------------------------------" << std::endl;
                }
            }
            break;
        }
        case 3:
            std::cout << "\nViewing Summary......\n";
            showSummary(transactions);
            break;
        case 4:
            std::cout << "\nExiting......\n";
            break;
        default:
            std::cout << "\nInvalid choice. Please try again.\n";
            break;
        }
    } while (choice != 4);

    return 0;
}