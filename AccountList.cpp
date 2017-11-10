#include "stdafx.h"
#include "AccountList.h"

AccountList::AccountList()
{

}

AccountList::~AccountList()
{

}

bool AccountList::AddAccount(Account* account)
{
	return list.Insert(account);
}

bool AccountList::LoadAccount(int accountID, Account * &account) const
{
	Customer accountOwner(accountID);
	Account target(accountOwner);

	return list.Retrieve(target, account);

}

bool AccountList::ExistsAccount(int accountID) const
{
	Customer accountOwner(accountID);
	Account target(accountOwner);

	return list.Exists(target);
}

void AccountList::Display() const
{
	list.Display();
}

void AccountList::Empty()
{
	list.Empty();
}

bool AccountList::isEmpty() const
{
	return list.isEmpty();
}

