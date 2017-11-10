#include "stdafx.h"
#include "Customer.h"
#include "VariableDefaultsValues.h"

Customer::Customer()
{
	accountID = DEFAULT_INVALID_INT;
}

Customer::Customer(int accountID)
{
	this->accountID = accountID;
}

Customer::Customer(std::string firstName, std::string lastName) : Person(firstName, lastName)
{
	int accountID = DEFAULT_INVALID_INT;
}

Customer::Customer(std::string firstName, std::string lastName, int accountID) : Person(firstName, lastName)
{
	this->accountID = accountID;
}

Customer::Customer(const Customer & sourceObj) : Person(sourceObj.getFirstName(), sourceObj.getLastName())
{
	this->accountID = sourceObj.getAccountID();
}

Customer::~Customer()
{
}

const int Customer::getAccountID() const
{
	return accountID;
}

void Customer::setAccountID(const int accountID)
{
	this->accountID = accountID;
}



