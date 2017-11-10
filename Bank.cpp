#include "stdafx.h"
#include "Bank.h"

bool Bank::processDeposit(int accountID, int amount, int fundType, bool isTransfer, std::string & errorMessage)
{
	Account* account;

	bool isSuccessful = accountList.LoadAccount(accountID, account);
	if (!isSuccessful)
	{
		errorMessage = ERROR_DEPOSIT_FAILED_STR;
		errorMessage += UNABLE_TO_LOAD_ACCOUNT_STR;
		errorMessage += std::to_string(accountID);

		return false;
	}

	return account->Deposit(amount, fundType, isTransfer, errorMessage);
}

bool Bank::processWithdraw(int accountID, int amount, int &cashReturned, int fundType, bool isTransfer, std::string & errorMessage)
{
	Account* account;

	bool isSuccessful = accountList.LoadAccount(accountID, account);
	if (!isSuccessful)
	{
		cashReturned = 0;

		errorMessage = ERROR_WITHDRAW_FAILED_STR;
		errorMessage += UNABLE_TO_LOAD_ACCOUNT_STR;
		errorMessage += std::to_string(accountID);

		return false;
	}

	if ((fundType == MONEY_MARKET) || (fundType == PRIME_MONEY_MARKET))
	{
		if (fundType == MONEY_MARKET)
		{
			return account->Withdraw(amount, cashReturned, MONEY_MARKET, isTransfer, errorMessage);
		}


		return account->Withdraw(amount, cashReturned, PRIME_MONEY_MARKET, MONEY_MARKET, isTransfer, errorMessage);
	}

	
	if ((fundType == LONG_TERM_BOND) || (fundType == SHORT_TERM_BOND))
	{
		if (fundType == LONG_TERM_BOND)
		{
			return account->Withdraw(amount, cashReturned, LONG_TERM_BOND, SHORT_TERM_BOND, isTransfer, errorMessage);
		}


		return account->Withdraw(amount, cashReturned, SHORT_TERM_BOND, LONG_TERM_BOND, isTransfer, errorMessage);
	}


	return account->Withdraw(amount, cashReturned, fundType, isTransfer, errorMessage);

}

void Bank::displaySeparator(int width) const
{
	for (int i = 0; i < width; i++)
	{
		std::cout << SEPARATOR_CHAR;
	}

	std::cout << std::endl;
}

Bank::Bank()
{
}

Bank::~Bank()
{
}

bool Bank::OpenNewAccount(const Account & account, std::string & errorMessage)
{
	Account* newAccount = new Account(account);

	bool isSuccessful = accountList.AddAccount(newAccount);
	if (!isSuccessful)
	{
		delete newAccount;
		newAccount = nullptr;

		errorMessage = ERROR_ACCOUNT_CREATION_FAILURE_STR;
		errorMessage = BANK_FAILED_ACCOUNT_CREATION_STR;
		errorMessage += account.getAccountID();

		return false;
	}

	
	errorMessage = SUCCESS_STR;
	return true;
}

bool Bank::Deposit(int accountID, int amount, int fundType, std::string & errorMessage)
{
	return processDeposit(accountID, amount, fundType, false, errorMessage);
}

bool Bank::Withdraw(int accountID, int amount, int &cashReturned, int fundType, std::string & errorMessage)
{
	return processWithdraw(accountID, amount, cashReturned, fundType, false, errorMessage);
}

bool Bank::Transfer(int fromAccountID, int toAccountID, int amount, int fromFundType, int toFundType, std::string & errorMessage)
{
	bool toAccountExists = accountList.ExistsAccount(toAccountID);
	if (toAccountExists)
	{
		int cashReturned;
		bool isSuccessful = processWithdraw(fromAccountID, amount, cashReturned, fromFundType, true, errorMessage);
		if (isSuccessful)
		{
			isSuccessful = processDeposit(toAccountID, amount, toFundType, true, errorMessage);
			if (isSuccessful)
			{
				errorMessage = SUCCESS_STR;

				return true;
			}
		}
	}
	else
	{
		errorMessage += ERROR_INVALID_DESTINATION_ACCOUNT_ID_STR;
	}


	errorMessage += ERROR_TRANSFER_FAILED_STR;

	return false;
}

bool Bank::AccountHistory(int accountID, std::string &errorMessage) const
{
	Account* account;
	
	bool isSuccessful = accountList.LoadAccount(accountID, account);
	if (!isSuccessful)
	{
		errorMessage = ERROR_ACCOUNT_HISTORY_FAILED_STR;
		errorMessage += UNABLE_TO_LOAD_ACCOUNT_STR;

		return false;
	}

	std::string accountHistory;
	displaySeparator(SEPARATOR_WIDTH_INT);
	
	std::cout << std::endl << std::endl 
		<< ALL_TRANSACTION_DETAILS_STR
		<< account->getFirstName() << " " << account->getLastName()
		<< " (" << account->getAccountID() << "):" 
		<< std::endl << std::endl;

	for (int fundTypeIterator = 0; fundTypeIterator < TOTAL_FUNDS_INT; fundTypeIterator++)
	{
		accountHistory = account->getAccountHistory(fundTypeIterator);

		std::cout << FORMAT_SUB_ERROR_STR << account->getFundName(fundTypeIterator) << " summary";

		std::cout << std::endl << FORMAT_SUB_ERROR_STR;
		displaySeparator(account->getFundName(fundTypeIterator).length() + SEPARATOR_EXTRA_INT);
		std::cout << accountHistory;
		std::cout << ENDING_BAL_STR << account->getBalance(fundTypeIterator);
		
		std::cout << std::endl << std::endl << std::endl;
	}

	errorMessage = SUCCESS_STR;

	return true;
}

bool Bank::AccountHistory(int accountID, int fundType, std::string & errorMessage) const
{
	Account* account;

	bool isSuccessful = accountList.LoadAccount(accountID, account);
	if (!isSuccessful)
	{
		errorMessage = ERROR_ACCOUNT_HISTORY_FAILED_STR;
		errorMessage += UNABLE_TO_LOAD_ACCOUNT_STR;

		return false;
	}

	std::string accountHistory = account->getAccountHistory(fundType);

	displaySeparator(SEPARATOR_WIDTH_INT);
	std::cout << account->getFundName(fundType) << " details for "
		<< account->getFirstName() << " " << account->getLastName()
		<< " (" << account->getAccountID() << "):" 
		<< std::endl;

	std::cout << accountHistory;
	std::cout << ENDING_BAL_STR << account->getBalance(fundType);

	std::cout << std::endl << std::endl;

	errorMessage = SUCCESS_STR;

	return true;
}

bool Bank::ExistsAccount(int accountID) const
{
	return accountList.ExistsAccount(accountID);
}

void Bank::DisplayAllOpenAccounts() const
{
	accountList.Display();
}
