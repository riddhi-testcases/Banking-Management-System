/*
 * ╔══════════════════════════════════════════════════════════════╗
 * ║                  RIDDHI'S BANKING SYSTEM                     ║
 * ║                                                              ║
 * ║                                                              ║
 * ║  Developer: Riddhi Chakraborty                               ║
 * ║  Features: Account Management, Money Transfer,               ║
 * ║           Transaction History, Statement Generation          ║
 * ║                                                              ║
 * ║  This system provides comprehensive banking operations       ║
 * ║  with enhanced security and user experience.                 ║
 * ╚══════════════════════════════════════════════════════════════╝
 */

#include "BankSystem.h"

int main() {
    try {
        cout << "\nWelcome to Riddhi's Advanced Banking System!\n";
        cout << "Initializing system...\n";
        
        BankingSystem bankSystem;
        bankSystem.runBankingSystem();
    }
    catch (const exception& e) {
        cout << "System Error: " << e.what() << endl;
        cout << "Please restart the application." << endl;
        return 1;
    }
    catch (...) {
        cout << "Unknown error occurred!" << endl;
        cout << "Please restart the application." << endl;
        return 1;
    }
    
    return 0;
}
