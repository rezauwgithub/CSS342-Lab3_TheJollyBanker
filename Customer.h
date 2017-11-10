#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"

class Customer : public Person
{
	private:
		int accountID;


	public:
		Customer();
		Customer(int accountID);
		Customer(std::string firstName, std::string lastName);
		Customer(std::string firstName, std::string lastName, int accountID);
		Customer(const Customer &sourceObj);
		~Customer();

		const int getAccountID() const;
		void setAccountID(const int accountID);

};

#endif // CUSTOMER_H

