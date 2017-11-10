#include "stdafx.h"
#include "Transaction.h"
#include "VariableDefaultsValues.h"


Transaction::Transaction(char transactionType, int amount, int fromFundType, int toFundType, int fromAccountID, int toAccountID)
{
	this->transactionType = transactionType;
	this->amount = amount;
	this->fromFundType = fromFundType;
	this->toFundType = toFundType;
	this->fromAccountID = fromAccountID;
	this->toAccountID = toAccountID;

	accountID = DEFAULT_INVALID_INT;
}


Transaction::Transaction(const std::string firstName, const std::string lastName, int accountID)
{
	customer.setFirstName(firstName);
	customer.setLastName(lastName);

	this->accountID = accountID;

	transactionType = DEFAULT_TRANSACTION_TYPE_CHAR;
	fromAccountID = DEFAULT_INVALID_INT;
	fromFundType = DEFAULT_INVALID_INT;
	amount = DEFAULT_INVALID_INT;
	toAccountID = DEFAULT_INVALID_INT;
	toFundType = DEFAULT_INVALID_INT;
}


Transaction::~Transaction()
{
}


char Transaction::getTransactionType() const
{
	return transactionType;
}


int Transaction::getFromAccountID() const
{
	return fromAccountID;
}


int Transaction::getFromFundType() const
{
	return fromFundType;
}


int Transaction::getTransactionAmount() const
{
	return amount;
}


int Transaction::getToAccountID() const
{
	return toAccountID;
}


int Transaction::getToFundType() const
{
	return toFundType;
}


int Transaction::getAccountID() const
{
	return accountID;
}

std::string Transaction::getFirstName() const
{
	return customer.getFirstName();
}
std::string Transaction::getLastName() const
{
	return customer.getLastName();
}