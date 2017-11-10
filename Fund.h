#pragma once
/*
The fund class holds integers representing currency and the history of all
transactions that access that currency.  By assignment requirement, there
ten fund types.  Each fund type is an element in an integer array.  History
is stored as a doubly linked list of std::string objects.  Each fund history
is stored in a vector container indexed by fund type.

I chose the STL list for storing history because of the low cost associated
with adding items, given that it is a doubly linked list and every new
addition can be appended to the end of the list.
*/

#ifndef FUND_H
#define FUND_H

#include <iostream>
#include <vector>
#include <list>

#include "VariableDefaultsValues.h"

class Fund
{
	private:
		int funds[TOTAL_FUNDS_INT];
		std::vector<std::list<std::string>> accountHistory;


	public:
		Fund();
		~Fund();

		const int getBalance(int fundType) const;
		const std::string getAccountHistory(int fundType) const;
		bool Deposit(int amount, int fundType);
		bool Withdraw(int amount, int &cashReturned, int fundType);

		bool AddLogEntry(int fundType, const std::string &logEntry);
};

#endif // FUND_H
