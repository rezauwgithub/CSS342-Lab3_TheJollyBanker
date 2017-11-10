#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Customer.h"
#include "VariableDefaultsValues.h"

class Transaction
{
	private:

		char transactionType;
		int fromAccountID;
		int fromFundType;
		int amount;
		int toAccountID;
		int toFundType;
		int accountID;
		Customer customer;

	public:
		Transaction(
			char transactionType = INVALID_TRANSACTION_TYPE_CHAR, 
			int amount = DEFAULT_INVALID_INT, 
			int fromFundType = DEFAULT_INVALID_INT, 
			int toFundType = DEFAULT_INVALID_INT, 
			int fromAccountID = DEFAULT_INVALID_INT, 
			int toAccountID = DEFAULT_INVALID_INT
			);

		Transaction(const std::string firstName, const std::string lastName, int accountID);
		~Transaction();

		char getTransactionType() const;

		int getFromAccountID() const;
		int getFromFundType() const;
		int getTransactionAmount() const;
		int getToAccountID() const;
		int getToFundType() const;
		int getAccountID() const;
		std::string getFirstName() const;
		std::string getLastName() const;

};

#endif // TRANSACTION_H
