#include "BankSystem.h"
#include <random>
#include <chrono>

// BankAccount class implementation
BankAccount::BankAccount() : accountNumber(""), accountHolderName(""), password(""), 
                            balance(0.0), accountType("Savings"), creationDate(""), isActive(true) {}

BankAccount::BankAccount(string accNo, string name, string pass, double bal, string type) 
    : accountNumber(accNo), accountHolderName(name), password(pass), balance(bal), 
      accountType(type), isActive(true) {
    creationDate = getCurrentDate();
}

void BankAccount::setAccountNumber(const string& accNo) { accountNumber = accNo; }
void BankAccount::setAccountHolderName(const string& name) { accountHolderName = name; }
void BankAccount::setPassword(const string& pass) { password = pass; }
void BankAccount::setBalance(double bal) { balance = bal; }
void BankAccount::setAccountType(const string& type) { accountType = type; }
void BankAccount::setCreationDate(const string& date) { creationDate = date; }
void BankAccount::setActiveStatus(bool status) { isActive = status; }

string BankAccount::getAccountNumber() const { return accountNumber; }
string BankAccount::getAccountHolderName() const { return accountHolderName; }
string BankAccount::getPassword() const { return password; }
double BankAccount::getBalance() const { return balance; }
string BankAccount::getAccountType() const { return accountType; }
string BankAccount::getCreationDate() const { return creationDate; }
bool BankAccount::getActiveStatus() const { return isActive; }

string BankAccount::getCurrentDate() const {
    time_t now = time(0);
    char* dt = ctime(&now);
    string dateStr(dt);
    dateStr.pop_back(); // Remove newline character
    return dateStr;
}

bool BankAccount::validatePassword(const string& pass) const {
    return password == pass;
}

// BankingSystem class implementation
BankingSystem::BankingSystem() {
    loadAccountsFromFile();
    loadTransactionsFromFile();
}

BankingSystem::~BankingSystem() {
    saveAccountsToFile();
    saveTransactionsToFile();
}

void BankingSystem::displayHeader() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║              RIDDHI'S ADVANCED BANKING SYSTEM                ║\n";
    cout << "║                   Enhanced Version 2.0                      ║\n";
    cout << "║                                                              ║\n";
    cout << "║  Developer: Riddhi Chakraborty                               ║\n";
    cout << "║  Professional Banking Management System                      ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
}

void BankingSystem::displayFooter() {
    cout << "\n╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║                                                              ║\n";
    cout << "║           Thank you for using Riddhi's Banking System!      ║\n";
    cout << "║                    Banking made simple & secure             ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
}

void BankingSystem::displayMainMenu() {
    clearScreen();
    displayHeader();
    cout << "\n┌─────────────────── MAIN MENU ───────────────────┐\n";
    cout << "│  1. Create New Account                          │\n";
    cout << "│  2. Deposit Money                               │\n";
    cout << "│  3. Withdraw Money                              │\n";
    cout << "│  4. Check Balance                               │\n";
    cout << "│  5. View Account Details                        │\n";
    cout << "│  6. Transfer Money                              │\n";
    cout << "│  7. Transaction History                         │\n";
    cout << "│  8. Generate Account Statement                  │\n";
    cout << "│  9. Deactivate Account                          │\n";
    cout << "│  0. Exit System                                 │\n";
    cout << "└─────────────────────────────────────────────────┘\n";
    cout << "\n➤ Enter your choice: ";
}

void BankingSystem::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void BankingSystem::pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

string BankingSystem::generateAccountNumber() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(100000, 999999);
    
    string accNo;
    bool unique = false;
    
    while (!unique) {
        accNo = "RC" + to_string(dis(gen));
        unique = (findAccountIndex(accNo) == -1);
    }
    
    return accNo;
}

bool BankingSystem::isValidAccountNumber(const string& accountNo) {
    return findAccountIndex(accountNo) != -1;
}

int BankingSystem::findAccountIndex(const string& accountNo) {
    for (size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].getAccountNumber() == accountNo && accounts[i].getActiveStatus()) {
            return i;
        }
    }
    return -1;
}

bool BankingSystem::authenticateUser(string& accountNo) {
    cout << "\n┌─────────── USER AUTHENTICATION ───────────┐\n";
    cout << "│ Account Number: ";
    cin >> accountNo;
    
    int index = findAccountIndex(accountNo);
    if (index == -1) {
        cout << "│ ❌ Invalid account number!                │\n";
        cout << "└────────────────────────────────────────────┘\n";
        return false;
    }
    
    string password;
    cout << "│ Password: ";
    cin >> password;
    
    if (!accounts[index].validatePassword(password)) {
        cout << "│ ❌ Incorrect password!                    │\n";
        cout << "└────────────────────────────────────────────┘\n";
        return false;
    }
    
    cout << "│ ✅ Authentication successful!             │\n";
    cout << "└────────────────────────────────────────────┘\n";
    return true;
}

void BankingSystem::addTransaction(const string& accountNo, const string& type, double amount, double newBalance) {
    Transaction trans;
    trans.accountNo = accountNo;
    trans.type = type;
    trans.amount = amount;
    trans.balanceAfter = newBalance;
    
    time_t now = time(0);
    char* dt = ctime(&now);
    string dateStr(dt);
    dateStr.pop_back();
    trans.date = dateStr;
    
    transactions.push_back(trans);
}

void BankingSystem::createNewAccount() {
    clearScreen();
    displayHeader();
    cout << "\n┌─────────── CREATE NEW ACCOUNT ───────────┐\n";
    
    string name, password, accountType;
    double initialDeposit;
    
    cin.ignore();
    cout << "│ Account Holder Name: ";
    getline(cin, name);
    
    cout << "│ Create Password: ";
    cin >> password;
    
    cout << "│ Account Type (1-Savings/2-Current): ";
    int typeChoice;
    cin >> typeChoice;
    accountType = (typeChoice == 1) ? "Savings" : "Current";
    
    cout << "│ Initial Deposit (Min ₹" << MIN_BALANCE << "): ₹";
    cin >> initialDeposit;
    
    if (initialDeposit < MIN_BALANCE) {
        cout << "│ ❌ Minimum deposit required: ₹" << MIN_BALANCE << "\n";
        cout << "└────────────────────────────────────────────┘\n";
        pauseScreen();
        return;
    }
    
    string accountNo = generateAccountNumber();
    BankAccount newAccount(accountNo, name, password, initialDeposit, accountType);
    accounts.push_back(newAccount);
    
    addTransaction(accountNo, "Account Opening", initialDeposit, initialDeposit);
    
    cout << "│ ✅ Account created successfully!          │\n";
    cout << "│ Your Account Number: " << accountNo << "           │\n";
    cout << "│ Please note down your account number!     │\n";
    cout << "└────────────────────────────────────────────┘\n";
    
    pauseScreen();
}

void BankingSystem::depositMoney() {
    clearScreen();
    displayHeader();
    
    string accountNo;
    if (!authenticateUser(accountNo)) {
        pauseScreen();
        return;
    }
    
    int index = findAccountIndex(accountNo);
    double amount;
    
    cout << "\n┌─────────── DEPOSIT MONEY ───────────┐\n";
    cout << "│ Current Balance: ₹" << fixed << setprecision(2) << accounts[index].getBalance() << "\n";
    cout << "│ Enter deposit amount: ₹";
    cin >> amount;
    
    if (amount <= 0) {
        cout << "│ ❌ Invalid amount!                  │\n";
        cout << "└─────────────────────────────────────┘\n";
        pauseScreen();
        return;
    }
    
    double newBalance = accounts[index].getBalance() + amount;
    accounts[index].setBalance(newBalance);
    
    addTransaction(accountNo, "Deposit", amount, newBalance);
    
    cout << "│ ✅ Deposit successful!              │\n";
    cout << "│ New Balance: ₹" << fixed << setprecision(2) << newBalance << "\n";
    cout << "└─────────────────────────────────────┘\n";
    
    pauseScreen();
}

void BankingSystem::withdrawMoney() {
    clearScreen();
    displayHeader();
    
    string accountNo;
    if (!authenticateUser(accountNo)) {
        pauseScreen();
        return;
    }
    
    int index = findAccountIndex(accountNo);
    double amount;
    
    cout << "\n┌─────────── WITHDRAW MONEY ───────────┐\n";
    cout << "│ Current Balance: ₹" << fixed << setprecision(2) << accounts[index].getBalance() << "\n";
    cout << "│ Enter withdrawal amount: ₹";
    cin >> amount;
    
    if (amount <= 0) {
        cout << "│ ❌ Invalid amount!                   │\n";
        cout << "└──────────────────────────────────────┘\n";
        pauseScreen();
        return;
    }
    
    double currentBalance = accounts[index].getBalance();
    if (amount > currentBalance) {
        cout << "│ ❌ Insufficient balance!             │\n";
        cout << "└──────────────────────────────────────┘\n";
        pauseScreen();
        return;
    }
    
    if ((currentBalance - amount) < MIN_BALANCE) {
        cout << "│ ❌ Minimum balance ₹" << MIN_BALANCE << " required! │\n";
        cout << "└──────────────────────────────────────┘\n";
        pauseScreen();
        return;
    }
    
    double newBalance = currentBalance - amount;
    accounts[index].setBalance(newBalance);
    
    addTransaction(accountNo, "Withdrawal", amount, newBalance);
    
    cout << "│ ✅ Withdrawal successful!            │\n";
    cout << "│ New Balance: ₹" << fixed << setprecision(2) << newBalance << "\n";
    cout << "└──────────────────────────────────────┘\n";
    
    pauseScreen();
}

void BankingSystem::checkBalance() {
    clearScreen();
    displayHeader();
    
    string accountNo;
    if (!authenticateUser(accountNo)) {
        pauseScreen();
        return;
    }
    
    int index = findAccountIndex(accountNo);
    
    cout << "\n┌─────────── BALANCE INQUIRY ───────────┐\n";
    cout << "│ Account Number: " << accounts[index].getAccountNumber() << "\n";
    cout << "│ Account Holder: " << accounts[index].getAccountHolderName() << "\n";
    cout << "│ Current Balance: ₹" << fixed << setprecision(2) << accounts[index].getBalance() << "\n";
    cout << "│ Account Type: " << accounts[index].getAccountType() << "\n";
    cout << "└────────────────────────────────────────┘\n";
    
    pauseScreen();
}

void BankingSystem::viewAccountDetails() {
    clearScreen();
    displayHeader();
    
    string accountNo;
    if (!authenticateUser(accountNo)) {
        pauseScreen();
        return;
    }
    
    int index = findAccountIndex(accountNo);
    
    cout << "\n┌─────────── ACCOUNT DETAILS ───────────┐\n";
    cout << "│ Account Number: " << accounts[index].getAccountNumber() << "\n";
    cout << "│ Account Holder: " << accounts[index].getAccountHolderName() << "\n";
    cout << "│ Account Type: " << accounts[index].getAccountType() << "\n";
    cout << "│ Current Balance: ₹" << fixed << setprecision(2) << accounts[index].getBalance() << "\n";
    cout << "│ Account Created: " << accounts[index].getCreationDate() << "\n";
    cout << "│ Status: " << (accounts[index].getActiveStatus() ? "Active" : "Inactive") << "\n";
    cout << "└────────────────────────────────────────┘\n";
    
    pauseScreen();
}

void BankingSystem::transferMoney() {
    clearScreen();
    displayHeader();
    
    string fromAccount;
    if (!authenticateUser(fromAccount)) {
        pauseScreen();
        return;
    }
    
    string toAccount;
    double amount;
    
    cout << "\n┌─────────── MONEY TRANSFER ───────────┐\n";
    cout << "│ Transfer to Account Number: ";
    cin >> toAccount;
    
    int fromIndex = findAccountIndex(fromAccount);
    int toIndex = findAccountIndex(toAccount);
    
    if (toIndex == -1) {
        cout << "│ ❌ Recipient account not found!      │\n";
        cout << "└───────────────────────────────────────┘\n";
        pauseScreen();
        return;
    }
    
    if (fromAccount == toAccount) {
        cout << "│ ❌ Cannot transfer to same account!  │\n";
        cout << "└───────────────────────────────────────┘\n";
        pauseScreen();
        return;
    }
    
    cout << "│ Transfer Amount: ₹";
    cin >> amount;
    
    if (amount <= 0) {
        cout << "│ ❌ Invalid amount!                   │\n";
        cout << "└───────────────────────────────────────┘\n";
        pauseScreen();
        return;
    }
    
    double fromBalance = accounts[fromIndex].getBalance();
    if (amount > fromBalance || (fromBalance - amount) < MIN_BALANCE) {
        cout << "│ ❌ Insufficient balance!             │\n";
        cout << "└───────────────────────────────────────┘\n";
        pauseScreen();
        return;
    }
    
    // Perform transfer
    accounts[fromIndex].setBalance(fromBalance - amount);
    accounts[toIndex].setBalance(accounts[toIndex].getBalance() + amount);
    
    // Record transactions
    addTransaction(fromAccount, "Transfer Out to " + toAccount, amount, accounts[fromIndex].getBalance());
    addTransaction(toAccount, "Transfer In from " + fromAccount, amount, accounts[toIndex].getBalance());
    
    cout << "│ ✅ Transfer successful!              │\n";
    cout << "│ Transferred ₹" << fixed << setprecision(2) << amount << " to " << toAccount << "\n";
    cout << "│ Your new balance: ₹" << accounts[fromIndex].getBalance() << "\n";
    cout << "└───────────────────────────────────────┘\n";
    
    pauseScreen();
}

void BankingSystem::viewTransactionHistory() {
    clearScreen();
    displayHeader();
    
    string accountNo;
    if (!authenticateUser(accountNo)) {
        pauseScreen();
        return;
    }
    
    cout << "\n┌─────────── TRANSACTION HISTORY ───────────┐\n";
    cout << "│ Account: " << accountNo << "\n";
    cout << "├────────────────────────────────────────────┤\n";
    
    bool hasTransactions = false;
    for (const auto& trans : transactions) {
        if (trans.accountNo == accountNo) {
            hasTransactions = true;
            cout << "│ " << trans.date << "\n";
            cout << "│ Type: " << trans.type << "\n";
            cout << "│ Amount: ₹" << fixed << setprecision(2) << trans.amount << "\n";
            cout << "│ Balance After: ₹" << trans.balanceAfter << "\n";
            cout << "├────────────────────────────────────────────┤\n";
        }
    }
    
    if (!hasTransactions) {
        cout << "│ No transactions found.                     │\n";
    }
    
    cout << "└────────────────────────────────────────────┘\n";
    pauseScreen();
}

void BankingSystem::generateAccountStatement() {
    clearScreen();
    displayHeader();
    
    string accountNo;
    if (!authenticateUser(accountNo)) {
        pauseScreen();
        return;
    }
    
    int index = findAccountIndex(accountNo);
    string filename = "statement_" + accountNo + ".txt";
    
    ofstream file(filename);
    if (!file) {
        cout << "❌ Error creating statement file!\n";
        pauseScreen();
        return;
    }
    
    file << "RIDDHI'S BANKING SYSTEM - ACCOUNT STATEMENT\n";
    file << "==========================================\n\n";
    file << "Account Number: " << accounts[index].getAccountNumber() << "\n";
    file << "Account Holder: " << accounts[index].getAccountHolderName() << "\n";
    file << "Account Type: " << accounts[index].getAccountType() << "\n";
    file << "Current Balance: ₹" << fixed << setprecision(2) << accounts[index].getBalance() << "\n";
    file << "Statement Generated: " << accounts[index].getCurrentDate() << "\n\n";
    file << "TRANSACTION HISTORY:\n";
    file << "-------------------\n";
    
    for (const auto& trans : transactions) {
        if (trans.accountNo == accountNo) {
            file << trans.date << " | " << trans.type << " | ₹" << trans.amount 
                 << " | Balance: ₹" << trans.balanceAfter << "\n";
        }
    }
    
    file.close();
    
    cout << "\n✅ Account statement generated successfully!\n";
    cout << "File saved as: " << filename << "\n";
    pauseScreen();
}

void BankingSystem::deactivateAccount() {
    clearScreen();
    displayHeader();
    
    string accountNo;
    if (!authenticateUser(accountNo)) {
        pauseScreen();
        return;
    }
    
    int index = findAccountIndex(accountNo);
    
    cout << "\n┌─────────── DEACTIVATE ACCOUNT ───────────┐\n";
    cout << "│ ⚠️  WARNING: This action is irreversible! │\n";
    cout << "│ Current Balance: ₹" << fixed << setprecision(2) << accounts[index].getBalance() << "\n";
    cout << "│ Confirm deactivation (Y/N): ";
    
    char confirm;
    cin >> confirm;
    
    if (confirm == 'Y' || confirm == 'y') {
        accounts[index].setActiveStatus(false);
        addTransaction(accountNo, "Account Deactivated", 0, accounts[index].getBalance());
        
        cout << "│ ✅ Account deactivated successfully!     │\n";
        cout << "│ Please visit branch for balance refund.  │\n";
    } else {
        cout << "│ ❌ Deactivation cancelled.               │\n";
    }
    
    cout << "└───────────────────────────────────────────┘\n";
    pauseScreen();
}

void BankingSystem::loadAccountsFromFile() {
    ifstream file(ACCOUNTS_FILE);
    if (!file) return;
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string accNo, name, pass, type, date;
        double balance;
        bool active;
        
        getline(ss, accNo, '|');
        getline(ss, name, '|');
        getline(ss, pass, '|');
        ss >> balance;
        ss.ignore();
        getline(ss, type, '|');
        getline(ss, date, '|');
        ss >> active;
        
        BankAccount acc(accNo, name, pass, balance, type);
        acc.setCreationDate(date);
        acc.setActiveStatus(active);
        accounts.push_back(acc);
    }
    file.close();
}

void BankingSystem::saveAccountsToFile() {
    ofstream file(ACCOUNTS_FILE);
    if (!file) return;
    
    for (const auto& acc : accounts) {
        file << acc.getAccountNumber() << "|"
             << acc.getAccountHolderName() << "|"
             << acc.getPassword() << "|"
             << acc.getBalance() << "|"
             << acc.getAccountType() << "|"
             << acc.getCreationDate() << "|"
             << acc.getActiveStatus() << "\n";
    }
    file.close();
}

void BankingSystem::loadTransactionsFromFile() {
    ifstream file(TRANSACTIONS_FILE);
    if (!file) return;
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        Transaction trans;
        
        getline(ss, trans.accountNo, '|');
        getline(ss, trans.type, '|');
        ss >> trans.amount;
        ss.ignore();
        getline(ss, trans.date, '|');
        ss >> trans.balanceAfter;
        
        transactions.push_back(trans);
    }
    file.close();
}

void BankingSystem::saveTransactionsToFile() {
    ofstream file(TRANSACTIONS_FILE);
    if (!file) return;
    
    for (const auto& trans : transactions) {
        file << trans.accountNo << "|"
             << trans.type << "|"
             << trans.amount << "|"
             << trans.date << "|"
             << trans.balanceAfter << "\n";
    }
    file.close();
}

void BankingSystem::runBankingSystem() {
    int choice;
    bool exitSystem = false;
    
    while (!exitSystem) {
        displayMainMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: createNewAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: viewAccountDetails(); break;
            case 6: transferMoney(); break;
            case 7: viewTransactionHistory(); break;
            case 8: generateAccountStatement(); break;
            case 9: deactivateAccount(); break;
            case 0:
                clearScreen();
                displayFooter();
                cout << "\n🙏 Thank you for using Riddhi's Banking System!\n";
                cout << "💫 Have a great day ahead!\n\n";
                exitSystem = true;
                break;
            default:
                cout << "\n❌ Invalid choice! Please try again.\n";
                pauseScreen();
        }
    }
}