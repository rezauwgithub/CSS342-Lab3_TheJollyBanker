#pragma once
/*
This class is primarily an interface for the storage object for accounts.
A binary tree is used by assignment requirement, but also because it is the
most efficient container (I'm aware of) for random retrieval of objects
stored.  In some cases, redefining how accounts are accessed proved
to be beneficial, so this class was created.  This also allows the BSTree
implementation to remain generic for other uses.
*/

#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H

#include <iostream>

#include <string>

#include "Account.h"
#include "BSTree.h"

class AccountList
{
	private:
		BSTree<Account> list;


	public:
		AccountList();
		~AccountList();

		bool AddAccount(Account* account);

		bool LoadAccount(int accountID, Account* &account) const;
		bool ExistsAccount(int accountID) const;

		void Display() const;
		void Empty();
		bool isEmpty() const;
};

#endif // ACCOUNTLIST_H
