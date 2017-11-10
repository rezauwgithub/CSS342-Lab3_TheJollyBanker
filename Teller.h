#pragma once
#ifndef TELLER_H
#define TELLER_H

#include <iostream>
#include <string>
#include "Transaction.h"
#include "Bank.h"
#include "Customer.h"
#include "Account.h"

class Teller
{
	private:
		Bank bank;

		bool processOpenNewAccount(const Transaction &currentTask, std::string &errorMessage);
		bool processDeposit(const Transaction &currentTask, std::string &errorMessage);
		bool processWithdraw(const Transaction &currentTask, std::string &errorMessage);
		bool processTransfer(const Transaction &currentTask, std::string &errorMessage);
		bool processHistory(const Transaction &currentTask, std::string &errorMessage);

		bool checkUnableOpenNewAccount(int accountID, std::string &errorMessage) const;
		bool checkUnableTransaction(char transactionType, int accountID, int amount, int fundType, std::string &errorMessage) const;

		bool checkInvalidAccountID(int accountID) const;
		bool checkInvalidFundType(int fundType) const;
		bool checkInvalidAmount(int amount) const;
		bool checkUnavailableAccount(int accountID) const;


	public:
		Teller();
		~Teller();

		bool OpenTask(const Transaction &currentTask, std::string &errorMessage);

		void DisplayAllOpenAccounts() const;
};

#endif // TELLER_H
