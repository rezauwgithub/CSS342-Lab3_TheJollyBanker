#include "stdafx.h"
#include "TaskList.h"


void TaskList::generateOpenTransaction(std::ifstream &inFile)
{
	std::string firstName;
	std::string lastName;
	int accountID;

	inFile >> lastName >> firstName >> accountID;

	Transaction currentTask(firstName, lastName, accountID);
	list.push(currentTask);


}

void TaskList::generateDepositTransaction(std::ifstream &inFile)
{
	int accountID, amount, fundType;

	int data;
	inFile >> data >> amount;

	findValues(data, accountID, fundType);

	Transaction newTransaction(
		TRANSACTION_TYPE_DEPOSIT_CHAR,
		amount,
		DEFAULT_INVALID_INT,
		fundType,
		DEFAULT_INVALID_INT,
		accountID
		);

	list.push(newTransaction);
}

void TaskList::generateWithdrawTransaction(std::ifstream & inFile)
{
	int accountID, amount, fundType;

	int data;
	inFile >> data >> amount;

	findValues(data, accountID, fundType);

	Transaction newTransaction(
		TRANSACTION_TYPE_WITHDRAW_CHAR,
		amount,
		fundType,
		DEFAULT_INVALID_INT,
		accountID,
		DEFAULT_INVALID_INT
		);

	list.push(newTransaction);

}

void TaskList::generateTransferTransaction(std::ifstream & inFile)
{
	int fromAccountID, toAccountID, 
		amount, 
		fromFundType, toFundType, 
		fromData, toData;

	inFile >> fromData >> amount >> toData;

	findValues(fromData, fromAccountID, fromFundType);
	findValues(toData, toAccountID, toFundType);

	Transaction newTransaction(
		TRANSACTION_TYPE_TRANSFER_CHAR,
		amount,
		fromFundType,
		toFundType,
		fromAccountID,
		toAccountID
		);

	list.push(newTransaction);
}

void TaskList::generateHistoryTransaction(std::ifstream & inFile)
{
	int accountID, fundType, data;

	inFile >> data;

	findValues(data, accountID, fundType);

	Transaction newTransaction(
		TRANSACTION_TYPE_HISTORY_CHAR,
		DEFAULT_INVALID_INT,
		fundType,
		DEFAULT_INVALID_INT,
		accountID,
		DEFAULT_INVALID_INT
		);

	list.push(newTransaction);
}

void TaskList::findValues(int data, int & accountID, int &fundType)
{
	if ((data < 1000) || data > 99999)
	{
		accountID = data;
		fundType = DEFAULT_INVALID_INT;

		return;
	}

	if (data < 10000)
	{
		accountID = data;
		fundType = DEFAULT_INVALID_INT;
	}
	else
	{
		accountID = data / 10;
		fundType = data % 10;
	}
}

TaskList::TaskList()
{
}

TaskList::~TaskList()
{
}

void TaskList::LoadTasks(std::ifstream & inFile)
{
	char transactionType;
	while (inFile >> transactionType)
	{
		switch (transactionType)
		{
			case TRANSACTION_TYPE_OPEN_ACCOUNT_CHAR:
				generateOpenTransaction(inFile);
				break;
			case TRANSACTION_TYPE_DEPOSIT_CHAR:
				generateDepositTransaction(inFile);
				break;
			case TRANSACTION_TYPE_WITHDRAW_CHAR:
				generateWithdrawTransaction(inFile);
				break;
			case TRANSACTION_TYPE_TRANSFER_CHAR:
				generateTransferTransaction(inFile);
				break;
			case TRANSACTION_TYPE_HISTORY_CHAR:
				generateHistoryTransaction(inFile);
				break;
			default:
				std::string crapData;
				std::getline(inFile, crapData);
				break;
		}
	}
}

const Transaction TaskList::getNextTask()
{
	Transaction newTransaction = list.front();
	list.pop();

	return newTransaction;
}

bool TaskList::isEmpty()
{
	return list.empty();
}
