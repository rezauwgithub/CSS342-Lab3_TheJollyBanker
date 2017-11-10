// The Jolly Banker.cpp : Defines the entry point for the console application.
//

// Reza Naeemi

#include "stdafx.h"

#include <fstream>
#include <string>

#include "TaskList.h"
#include "Teller.h"
#include "Transaction.h"
#include "VariableDefaultsValues.h"

int main()
{
	// Read in a std::string of transactions into an in-memory queue
	
	std::ifstream inFile(INFILE_PATH_STR);
	if (!inFile)
	{
		std::cout << INFILE_PATH_STR << " could not be loaded." << std::endl;
		
		system("pause");
		return -1;
	}

	TaskList tasklist;
	tasklist.LoadTasks(inFile);

	// Process the transactions in order
	Teller jollyBanker;
	Transaction currentTask;

	std::string errorMessage;
	while (!tasklist.isEmpty())
	{

		currentTask = tasklist .getNextTask();
		bool isSuccessful = jollyBanker.OpenTask(currentTask, errorMessage);
		if (!isSuccessful)
		{
			std::cerr << errorMessage << std::endl;
		}
	}

	// Print out open accounts and balances in those accounts
	for (int i = 0; i < SEPARATOR_WIDTH_INT; i++)
	{
		std::cout << SEPARATOR_CHAR;
	}
	std::cout << std::endl;

	std::cout << "Processing complete.  Final balances are below:" << std::endl << std::endl;
	jollyBanker.DisplayAllOpenAccounts();

	system("pause");
    return 0;
}

