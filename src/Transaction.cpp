#include <iostream>
#include "Transaction.h"

Transaction::Transaction(int id, std::string type, double amount, std::string category, std::string description) : id(id), type(type), amount(amount), category(category), description(description) {}

void Transaction::display() const
{
    std::cout << "ID: " << id << std::endl;
    std::cout << "Type: " << type << std::endl;
    std::cout << "Amount: " << amount << std::endl;
    std::cout << "Category:" << category << std::endl;
    std::cout << "Description:" << description << std::endl;
}