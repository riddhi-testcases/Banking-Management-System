#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// Transaction structure to store transaction history
struct Transaction {
    string accountNo;
    string type;
    double amount;
    string date;
    double balanceAfter;
};

class BankAccount {
private:
    string accountNumber;
    string accountHolderName;
    string password;
    double balance;
    string accountType;
    string creationDate;
    bool isActive;

public:
    // Constructors
    BankAccount();
    BankAccount(string accNo, string name, string pass, double bal, string type);
    
    // Setters
    void setAccountNumber(const string& accNo);
    void setAccountHolderName(const string& name);
    void setPassword(const string& pass);
    void setBalance(double bal);
    void setAccountType(const string& type);
    void setCreationDate(const string& date);
    void setActiveStatus(bool status);
    
    // Getters
    string getAccountNumber() const;
    string getAccountHolderName() const;
    string getPassword() const;
    double getBalance() const;
    string getAccountType() const;
    string getCreationDate() const;
    bool getActiveStatus() const;
    
    // Utility functions
    string getCurrentDate() const;
    bool validatePassword(const string& pass) const;
};

class BankingSystem {
private:
    vector<BankAccount> accounts;
    vector<Transaction> transactions;
    const string ACCOUNTS_FILE = "accounts.dat";
    const string TRANSACTIONS_FILE = "transactions.dat";
    const double MIN_BALANCE = 100.0;
    
public:
    BankingSystem();
    ~BankingSystem();
    
    // Core banking operations
    void createNewAccount();
    void depositMoney();
    void withdrawMoney();
    void checkBalance();
    void viewAccountDetails();
    void transferMoney();
    void viewTransactionHistory();
    void deactivateAccount();
    void generateAccountStatement();
    
    // File operations
    void loadAccountsFromFile();
    void saveAccountsToFile();
    void loadTransactionsFromFile();
    void saveTransactionsToFile();
    
    // Utility functions
    void displayMainMenu();
    void clearScreen();
    void pauseScreen();
    bool authenticateUser(string& accountNo);
    int findAccountIndex(const string& accountNo);
    void addTransaction(const string& accountNo, const string& type, double amount, double newBalance);
    bool isValidAccountNumber(const string& accountNo);
    string generateAccountNumber();
    void displayHeader();
    void displayFooter();
    
    // Main System loop
    void runBankingSystem();
};

#endif
