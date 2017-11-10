#pragma once
#ifndef VARIABLE_DEFAULTS_VALUES_H
#define VARIABLE_DEFAULTS_VALUES_H

#include <string>

const enum FUNDS
{
	MONEY_MARKET,
	PRIME_MONEY_MARKET,
	LONG_TERM_BOND,
	SHORT_TERM_BOND,
	INDEX_FUND_500,
	CAPITAL_VALUE_FUND,
	GROWTH_EQUITY_FUND,
	GROWTH_INDEX_FUND,
	VALUE_FUND,
	VALUE_STOCK_INDEX
};

const static std::string INFILE_PATH_STR = "BankTrans.txt";

const static std::string FORMAT_ERROR_STR = "\n\t\t\n";
const static std::string FORMAT_SUB_ERROR_STR = "\t";

const static std::string ERROR_ACCOUNT_CREATION_FAILURE_STR = FORMAT_ERROR_STR + "Error: Account creation failed!.";
const static std::string ERROR_DEPOSIT_FAILED_STR = FORMAT_ERROR_STR + "Error: Deposit failed!";
const static std::string ERROR_WITHDRAW_FAILED_STR = FORMAT_ERROR_STR + "Error: Withdraw failed!";
const static std::string ERROR_TRANSFER_FAILED_STR = FORMAT_ERROR_STR + "Error: Transfer failed!";
const static std::string ERROR_INSUFFICIENT_FUNDS_STR = FORMAT_ERROR_STR + "Error: Insufficient funds";
const static std::string ERROR_ACCOUNT_HISTORY_FAILED_STR = FORMAT_ERROR_STR + "Error: Display account history failed.";
const static std::string ERROR_INVALID_DESTINATION_ACCOUNT_ID_STR = FORMAT_ERROR_STR + "Error: Invalid Destination AccountID: ";

const static std::string UNABLE_TO_LOAD_ACCOUNT_STR = FORMAT_SUB_ERROR_STR + "The bank was unable to load account: ";
const static std::string BANK_FAILED_ACCOUNT_CREATION_STR = FORMAT_SUB_ERROR_STR + "The bank failed when creating account: ";
const static std::string TRANSFER_FAILED_STR = "The transfer was unsuccessful";

const static std::string UNKNOWN_NAME_STR = "Unknown";
const static std::string SUCCESS_STR = "Success";
const static std::string DEPOSIT_AMOUNT_STR = FORMAT_SUB_ERROR_STR + "Deposit amount: $";
const static std::string WITHDRAW_AMOUNT_STR = FORMAT_SUB_ERROR_STR + "Withdraw amount: $";
const static std::string ENDING_BAL_STR = FORMAT_SUB_ERROR_STR + "Ending Balance: $";
const static std::string ALL_TRANSACTION_DETAILS_STR = " All transaction details for ";

const static int DEFAULT_INVALID_INT = -1;
const static int TOTAL_FUNDS_INT = 10;
const static int SEPARATOR_WIDTH_INT = 72;
const static int SEPARATOR_EXTRA_INT = 10;


const static char INVALID_TRANSACTION_TYPE_CHAR = '?';
const static char TRANSACTION_TYPE_OPEN_ACCOUNT_CHAR = 'O';
const static char TRANSACTION_TYPE_DEPOSIT_CHAR = 'D';
const static char TRANSACTION_TYPE_WITHDRAW_CHAR = 'W';
const static char TRANSACTION_TYPE_TRANSFER_CHAR = 'T';
const static char TRANSACTION_TYPE_HISTORY_CHAR = 'H';

const static char SEPARATOR_CHAR = '-';

const static char DEFAULT_TRANSACTION_TYPE_CHAR = TRANSACTION_TYPE_OPEN_ACCOUNT_CHAR;


#endif // VARIABLE_DEFAULTS_VALUES_H