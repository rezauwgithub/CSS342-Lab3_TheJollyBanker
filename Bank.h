#pragma once
/*
The bank class contains all customer accounts and provides an interface
allowing bank tellers or other authorized users to access them.

Limitations:
-- The bank object cannot be duplicated.  The accountList container uses
a simple implementation of a binary tree to hold accounts, but it will
not deep copy.
-- The History and DisplayOpenAccounts functions rely on the console to
display their output.  This is by assignment requirement.
*/

#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <string>

#include "Account.h"
#include "AccountList.h"

class Bank
{
	private:
		AccountList accountList;

		bool processDeposit(int accountID, int amount, int fundType, bool isTransfer, std::string &errorMessage);
		bool processWithdraw(int accountID, int amount, int &cashReturned, int fundType, bool isTransfer, std::string &errorMessage);

		void displaySeparator(int width) const;


	public:
		Bank();
		~Bank();

		bool OpenNewAccount(const Account &account, std::string &errorMessage);
		bool Deposit(int accountID, int amount, int fundType, std::string &errorMessage);
		bool Withdraw(int accountID, int amount, int &cashReturned, int fundType, std::string &errorMessage);
		bool Transfer(int fromAccountID, int toAccountID, int amount, int fromFundType, int toFundType, std::string &errorMessage);

		bool AccountHistory(int accountID, std::string &errorMessage) const;
		bool AccountHistory(int accountID, int fundType, std::string &errorMessage) const;

		bool ExistsAccount(int accountID) const;

		void DisplayAllOpenAccounts() const;

};

#endif // BANK_H
