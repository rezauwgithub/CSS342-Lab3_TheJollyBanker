#include "stdafx.h"
#include "Teller.h"

bool Teller::processOpenNewAccount(const Transaction &currentTask, std::string &errorMessage)
{
	std::string firstName = currentTask.getFirstName();
	std::string lastName = currentTask.getLastName();
	int accountID = currentTask.getAccountID();

	if (checkUnableOpenNewAccount(accountID, errorMessage))
	{
		return false;
	}

	Customer accountOwner(firstName, lastName, accountID);
	Account account(accountOwner);

	return bank.OpenNewAccount(account, errorMessage);
}

bool Teller::processDeposit(const Transaction &currentTask, std::string &errorMessage)
{
	int accountID = currentTask.getToAccountID();
	int amount = currentTask.getTransactionAmount();
	int fundType = currentTask.getToFundType();

	if (checkUnableTransaction(
		TRANSACTION_TYPE_DEPOSIT_CHAR,
		accountID, amount, fundType, errorMessage)
		)
	{
		false;
	}

	return bank.Deposit(accountID, amount, fundType, errorMessage);
}

bool Teller::processWithdraw(const Transaction &currentTask, std::string &errorMessage)
{
	int accountID = currentTask.getFromAccountID();
	int amount = currentTask.getTransactionAmount();
	int fundType = currentTask.getFromFundType();

	int cashReturned;

	if (checkUnableTransaction(
		TRANSACTION_TYPE_WITHDRAW_CHAR,
		accountID, amount, fundType, errorMessage)
		)
	{
		return false;
	}

	return bank.Withdraw(accountID, amount, cashReturned, fundType, errorMessage);
}

bool Teller::processTransfer(const Transaction &currentTask, std::string &errorMessage)
{
	int fromAccountID = currentTask.getFromAccountID();
	int toAccountID = currentTask.getToAccountID();
	int amount = currentTask.getTransactionAmount();
	int fromFundType = currentTask.getFromFundType();
	int toFundType = currentTask.getToFundType();

	if ((checkUnableTransaction(
		TRANSACTION_TYPE_TRANSFER_CHAR,
		fromAccountID, amount, fromFundType, 
		errorMessage)
		) ||
		(checkUnableTransaction(
			TRANSACTION_TYPE_TRANSFER_CHAR,
			toAccountID, amount, toFundType, 
			errorMessage)
			)
		)
	{
		return false;
	}

	return bank.Transfer(
		fromAccountID, toAccountID,
		amount,
		fromFundType, toFundType,
		errorMessage);
}

bool Teller::processHistory(const Transaction &currentTask, std::string &errorMessage)
{
	int accountID = currentTask.getFromAccountID();
	int fundType = currentTask.getFromFundType();

	if (fundType == DEFAULT_INVALID_INT)
	{
		if (checkUnableTransaction(
			TRANSACTION_TYPE_HISTORY_CHAR,
			accountID, 0, 0, errorMessage))
		{
			return false;
		}

		return bank.AccountHistory(accountID, errorMessage);
	}

	if (checkUnableTransaction(
		TRANSACTION_TYPE_HISTORY_CHAR,
		accountID, 0, fundType, errorMessage))
	{
		return false;
	}

	return bank.AccountHistory(accountID, fundType, errorMessage);
}

bool Teller::checkUnableOpenNewAccount(int accountID, std::string & errorMessage) const
{
	if (checkInvalidAccountID(accountID))
	{
		errorMessage = ERROR_ACCOUNT_CREATION_FAILURE_STR + 
			"		AccountID" + std::to_string(accountID) + " is invalid";

		return true;
	}

	if (!checkUnavailableAccount(accountID))
	{
		errorMessage = ERROR_ACCOUNT_CREATION_FAILURE_STR + 
			"		AccountID " + std::to_string(accountID) + " is already taken.";

		return true;
	}

	return false;
}

bool Teller::checkUnableTransaction(char transactionType, int accountID, int amount, int fundType, std::string & errorMessage) const
{
	switch (transactionType)
	{
		case TRANSACTION_TYPE_DEPOSIT_CHAR:
			errorMessage = ERROR_DEPOSIT_FAILED_STR;
			break;
		case TRANSACTION_TYPE_WITHDRAW_CHAR:
			errorMessage = ERROR_WITHDRAW_FAILED_STR;
			break;
		case TRANSACTION_TYPE_TRANSFER_CHAR:
			errorMessage = ERROR_TRANSFER_FAILED_STR;
			break;
		case TRANSACTION_TYPE_HISTORY_CHAR:
			errorMessage = ERROR_ACCOUNT_HISTORY_FAILED_STR;
			break;
	}

	if (checkInvalidAccountID(accountID))
	{
		errorMessage += FORMAT_SUB_ERROR_STR + FORMAT_SUB_ERROR_STR + "AccountID";
		errorMessage += std::to_string(accountID);
		errorMessage += "is invalid.";

		return true;
	}

	if (checkUnavailableAccount(accountID))
	{
		errorMessage += FORMAT_SUB_ERROR_STR + FORMAT_SUB_ERROR_STR + "AccountID";
		errorMessage += std::to_string(accountID);
		errorMessage += " could not be located.";

		return true;
	}

	if (checkInvalidFundType(fundType))
	{
		errorMessage += FORMAT_SUB_ERROR_STR + FORMAT_SUB_ERROR_STR + "Fund";
		errorMessage += std::to_string(fundType);
		errorMessage += " invalid category type.";

		return true;
	}

	if (checkInvalidAmount(amount))
	{
		errorMessage += FORMAT_SUB_ERROR_STR + FORMAT_SUB_ERROR_STR + "Amount";
		errorMessage += std::to_string(amount);
		errorMessage += " must be positive amount.";

		return true;
	}

	return false;
}

bool Teller::checkInvalidAccountID(int accountID) const
{
	return !
		((accountID >= 1000) && (accountID <= 9999));
}

bool Teller::checkInvalidFundType(int fundType) const
{
	return !
		((fundType >= MONEY_MARKET) && (fundType <= VALUE_STOCK_INDEX));
}

bool Teller::checkInvalidAmount(int amount) const
{
	return !
		(amount >= 0);
}

bool Teller::checkUnavailableAccount(int accountID) const
{
	return !
		(bank.ExistsAccount(accountID));
}

Teller::Teller()
{
}

Teller::~Teller()
{
}

bool Teller::OpenTask(const Transaction & currentTask, std::string & errorMessage)
{
	char transactionType = currentTask.getTransactionType();

	switch (transactionType)
	{
		case TRANSACTION_TYPE_OPEN_ACCOUNT_CHAR:
			return processOpenNewAccount(currentTask, errorMessage);
		case TRANSACTION_TYPE_DEPOSIT_CHAR:
			return processDeposit(currentTask, errorMessage);
		case TRANSACTION_TYPE_WITHDRAW_CHAR:
			return processWithdraw(currentTask, errorMessage);
		case TRANSACTION_TYPE_TRANSFER_CHAR:
			return processTransfer(currentTask, errorMessage);
		case TRANSACTION_TYPE_HISTORY_CHAR:
			return processHistory(currentTask, errorMessage);
		default:
			errorMessage = transactionType;
			errorMessage += ": Unknown transaction type.";

		return false;
	}
}

void Teller::DisplayAllOpenAccounts() const
{
	bank.DisplayAllOpenAccounts();
}
