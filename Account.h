#pragma once
/*
The account class holds Customer data as well as fund data.  It also defines
interaction with that data from the bank.  Accounts are comparable based off
of the accountID number of the Customer.  As only the accountID is checked,
account objects are meant to be unique if used to open a new back account.
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "Customer.h"
#include "Fund.h"
#include "VariableDefaultsValues.h"

class Account
{
	friend std::ostream& operator <<(std::ostream &output, const Account &sourceObj);

	private:
		Customer accountOwner;
		Fund accountFunds;


	public:
		Account(const Customer &Customer);
		Account(const Account &sourceObj);
		~Account();

		const std::string getFirstName() const;
		const std::string getLastName() const;
		const int getAccountID() const;
		const int getBalance(int fundType) const;
		const std::string getAccountHistory(int fundType) const;
		const std::string getFundName(int fundType) const;

		bool Deposit(int amount, int fundType, bool isTransfer, std::string &errorMessage);
		bool Withdraw(int amount, int &cashReturned, int fundType, bool isTransfer, std::string &errorMessage);
		bool Withdraw(int amount, int &cashReturned, int fundTypeA, int fundTypeB, bool isTransfer, std::string &errorMessage);

		const Account& operator =(const Account &sourceObj);

		bool operator >(const Account &sourceObj) const;
		bool operator >=(const Account &sourceObj) const;
		bool operator <(const Account &sourceObj) const;
		bool operator <=(const Account &sourceObj) const;
		bool operator ==(const Account &sourceObj) const;
		bool operator !=(const Account &sourceObj) const;

};

#endif // ACCOUNT_H
