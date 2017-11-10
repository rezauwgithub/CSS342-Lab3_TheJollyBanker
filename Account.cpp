#include "stdafx.h"
#include "Account.h"

std::ostream &operator <<(std::ostream &output, const Account &sourceObj)
{
	output <<
		sourceObj.getFirstName() << " " << sourceObj.getLastName()
		<< " Account ID: " << sourceObj.getAccountID() << std::endl;


	for (int fundTypeIterator = 0; fundTypeIterator < TOTAL_FUNDS_INT; fundTypeIterator++)
	{
		output << " " << std::left << std::setw(19) << 
			sourceObj.getFundName(fundTypeIterator) << ":";

		output << std::right << std::setw(2) << "$" << 
			sourceObj.getBalance(fundTypeIterator) << std::endl;
	}

	output << std::endl;

	return output;
}

Account::Account(const Customer &Customer)
{
	accountOwner = Customer;
}

Account::Account(const Account &sourceObj)
{
	*this = sourceObj;
}

Account::~Account()
{

}

const std::string Account::getFirstName() const
{
	return accountOwner.getFirstName();
}

const std::string Account::getLastName() const
{
	return accountOwner.getLastName();
}

const int Account::getAccountID() const
{
	return accountOwner.getAccountID();
}

const int Account::getBalance(int fundType) const
{
	return accountFunds.getBalance(fundType);
}

const std::string Account::getAccountHistory(int fundType) const
{
	return accountFunds.getAccountHistory(fundType);
}

const std::string Account::getFundName(int fundType) const
{
	switch (fundType)
	{
	case MONEY_MARKET:
		return "Money Market";
	case PRIME_MONEY_MARKET:
		return "Prime Money Market";
	case LONG_TERM_BOND:
		return "Long-Term Bond";
	case SHORT_TERM_BOND:
		return "Short-Term Bond";
	case INDEX_FUND_500:
		return "500 Index Fund";
	case CAPITAL_VALUE_FUND:
		return "Capital Value Fund";
	case GROWTH_EQUITY_FUND:
		return "Growth Equality Fund";
	case GROWTH_INDEX_FUND:
		return "Growth Index Fund";
	case VALUE_FUND:
		return "Value Fund";
	case VALUE_STOCK_INDEX:
		return "Value Stock Index";
	default:
		return "Error: FUND_TYPE";
	}
}

bool Account::Deposit(int amount, int fundType, bool isTransfer, std::string &errorMessage)
{
	bool isSuccessful = accountFunds.Deposit(amount, fundType);

	std::string logEntry = DEPOSIT_AMOUNT_STR;
	logEntry += std::to_string(amount);

	if (isSuccessful)
	{
		if (isTransfer)
		{
			logEntry += " (Transfer Deposit)";
		}

		accountFunds.AddLogEntry(fundType, logEntry);
		errorMessage = SUCCESS_STR;
		return true;
	}

	logEntry += " Failed: Parameters not met";

	if (isTransfer)
	{
		logEntry += " (Transfer aborted)";
	}

	accountFunds.AddLogEntry(fundType, logEntry);	

	errorMessage = "Error: Failed to deposit into account " + 
		std::to_string(getAccountID()) + ": " + 
		getFundName(fundType) + FORMAT_ERROR_STR + logEntry;
	
	
	return false;
}

bool Account::Withdraw(int amount, int &cashReturned, int fundType, bool isTransfer, std::string &errorMessage)
{

	std::string logEntry = WITHDRAW_AMOUNT_STR;
	logEntry += std::to_string(amount);

	int availableCash = getBalance(fundType);

	bool fundsAvailable = true;
	if (amount > availableCash)
	{
		fundsAvailable = false;
	}

	if (fundsAvailable)
	{
		bool isSuccessful = accountFunds.Withdraw(amount, cashReturned, fundType);

		if (isSuccessful)
		{
			if (isTransfer)
			{
				logEntry += " (Transfer Withdraw)";
			}

			accountFunds.AddLogEntry(fundType, logEntry);
			errorMessage = SUCCESS_STR;
			return true;
		}
	}

	logEntry += ERROR_INSUFFICIENT_FUNDS_STR;

	if (isTransfer)
	{
		logEntry += "(Transfer aborted)";
	}

	accountFunds.AddLogEntry(fundType, logEntry);
	errorMessage = "Error: Could not withdraw from account " + getAccountID() + getFundName(fundType);
	errorMessage += FORMAT_ERROR_STR + logEntry;
	cashReturned = 0;
	return false;
}

bool Account::Withdraw(int amount, int &cashReturned, int fundTypeA, int fundTypeB, bool isTransfer, std::string &errorMessage)
{
	std::string logEntry = WITHDRAW_AMOUNT_STR;

	int availableCash = getBalance(fundTypeA) + getBalance(fundTypeB);
	bool fundsAvailable = true;

	if (amount > availableCash)
	{
		fundsAvailable = false;
	}

	if (fundsAvailable)
	{
		int totalCash = 0;

		bool isSuccessful = accountFunds.Withdraw(amount, cashReturned, fundTypeA);

		if (isSuccessful)
		{
			logEntry += std::to_string(cashReturned);

			if (isTransfer)
			{
				logEntry += " (Withdraw Transfer)";
			}

			if (cashReturned < amount)
			{
				logEntry += " (Attemping Overdraw)";
			}

			accountFunds.AddLogEntry(fundTypeA, logEntry);
		}
		else
		{
			logEntry += std::to_string(amount); 
			logEntry += ERROR_INSUFFICIENT_FUNDS_STR;
			
			accountFunds.AddLogEntry(fundTypeA, logEntry);
		}

		totalCash += cashReturned;
	
		
		if (totalCash < amount)
		{
			isSuccessful = accountFunds.Withdraw(amount - totalCash, cashReturned, fundTypeB);

			logEntry = WITHDRAW_AMOUNT_STR; 
			logEntry += std::to_string(amount - totalCash);

			if (isSuccessful)
			{
				if (isTransfer)
				{
					logEntry += "	(Withdraw Transfer)";
				}

				accountFunds.AddLogEntry(fundTypeB, logEntry);
			}

			totalCash += cashReturned;
		}

		if (totalCash == amount)
		{
			cashReturned = totalCash;
			errorMessage = SUCCESS_STR;
			return true;
		}

		logEntry += "	Failed: Overdraw unsuccessful";

		if (isTransfer)
		{
			logEntry += " (Transfer Failed)";
		}

		errorMessage = "Error: Could not withdraw $" +
			std::to_string(amount) + " from account " + 
			std::to_string(getAccountID()) + 
			"\n\tInsufficient funds in both " +
			getFundName(fundTypeA) + 
			" and " + getFundName(fundTypeB) + " types.";

		accountFunds.AddLogEntry(fundTypeB, logEntry);
		return false;
	}

	
	logEntry += std::to_string(amount);
	logEntry += ERROR_INSUFFICIENT_FUNDS_STR;

	if (isTransfer)
	{
		logEntry += " Transfer Aborted";
	}

	accountFunds.AddLogEntry(fundTypeA, logEntry);
	accountFunds.AddLogEntry(fundTypeB, logEntry);
	cashReturned = 0;
	return false;
}

const Account &Account::operator =(const Account &sourceObj)
{
	accountOwner = sourceObj.accountOwner;
	accountFunds = sourceObj.accountFunds;

	return *this;
}


bool Account::operator >(const Account &sourceObj) const
{
	return  getAccountID() > sourceObj.getAccountID();
}

bool Account::operator >=(const Account &sourceObj) const
{
	return (*this > sourceObj) || (*this == sourceObj);
}

bool Account::operator <(const Account &sourceObj) const
{
	return getAccountID() < sourceObj.getAccountID();
}

bool Account::operator <=(const Account &sourceObj) const
{
	return (*this < sourceObj) || (*this == sourceObj);
}

bool Account::operator ==(const Account &sourceObj) const
{
	return getAccountID() == sourceObj.getAccountID();
}

bool Account::operator !=(const Account &sourceObj) const
{
	return !
		(*this == sourceObj);
}



