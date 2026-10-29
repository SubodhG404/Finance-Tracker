#pragma once
#include <string>
class Transaction
{
private:
    int id;
    std::string type;
    double amount;
    std::string category;
    std::string description;
    std::string date;

public:
    Transaction(int id, std::string type, double amount, std::string category, std::string description, std::string date);

    void display() const;

    std::string getType() const;

    double getAmount() const;

    std::string getCategory() const;
    std::string getDescription() const;
    int getID() const;
    std::string getDate() const;
};
