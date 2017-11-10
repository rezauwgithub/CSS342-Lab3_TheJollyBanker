#include "stdafx.h"
#include "Fund.h"

Fund::Fund()
{
	// http://www.cplusplus.com/reference/cstring/memset/ 
	memset(funds, 0, sizeof(int) * TOTAL_FUNDS_INT);

	accountHistory.resize(TOTAL_FUNDS_INT);
}

Fund::~Fund()
{

}

const int Fund::getBalance(int fundType) const
{
	if ((fundType < 0) || (fundType >= TOTAL_FUNDS_INT))
	{
		return -1;
	}

	return funds[fundType];
}

const std::string Fund::getAccountHistory(int fundType) const
{
	if ((fundType < 0) || (fundType >= TOTAL_FUNDS_INT))
	{
		return "Fund type " + std::to_string(fundType) + " was not found";
	}

	std::string allAccountHistoryTransactionsString;
	for (std::list<std::string>::const_iterator iterator = accountHistory[fundType].begin(), end = accountHistory[fundType].end(); iterator != end; ++iterator)
	{
		allAccountHistoryTransactionsString += *iterator + "\n";
	}

	return allAccountHistoryTransactionsString;
}

bool Fund::Deposit(int amount, int fundType)
{
	if ((fundType < 0) || (fundType >= TOTAL_FUNDS_INT) || (amount < 0))
	{
		return false;
	}

	funds[fundType] += amount;
	return true;
}

bool Fund::Withdraw(int amount, int &cashReturned, int fundType)
{
	if ((fundType < 0) || (fundType >= TOTAL_FUNDS_INT) || (amount < 0))
	{
		cashReturned = 0;
		funds[fundType] -= cashReturned;

		return true;
	}
	
	if (amount <= funds[fundType] || funds[fundType] > 0)
	{
		if (amount <= funds[fundType])
		{
			cashReturned = amount;
			funds[fundType] -= cashReturned;
			
			return true;
		}
		else
		{
			cashReturned = funds[fundType];
			funds[fundType] -= cashReturned;

			return true;
		}
		
	}

	cashReturned = 0;
	return false;
}

bool Fund::AddLogEntry(int fundType, const std::string &logEntry)
{
	if ((fundType < 0) || (fundType >= TOTAL_FUNDS_INT))
	{
		return false;
	}

	accountHistory[fundType].push_back(logEntry);
	return true;
}


