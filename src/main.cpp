#include <iostream>
#include <string>

// Helper function to calculate padding and print centered text
void printCentered(const std::string& text, int width = 80) {
    if (text.length() >= static_cast<size_t>(width)) {
        std::cout << text << '\n';
        return;
    }
    int padding = (width - text.length()) / 2;
    std::cout << std::string(padding, ' ') << text << '\n';
}

int main() {
    int choice {0};
    const int consoleWidth = 80;

    do {
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

        switch (choice) {
            case 1:
                std::cout << "\nAdding Transaction......\n";
                break;
            case 2:
                std::cout << "\nViewing Transactions......\n"; 
                break;
            case 3:
                std::cout << "\nViewing Summary......\n"; 
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