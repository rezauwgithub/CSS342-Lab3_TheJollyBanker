#include "stdafx.h"
#include "Person.h"
#include "VariableDefaultsValues.h"

void Person::setUnknownName()
{
	firstName = UNKNOWN_NAME_STR;
	lastName = UNKNOWN_NAME_STR;
}

Person::Person()
{
	setUnknownName();
}

Person::Person(std::string firstName, std::string lastName)
{
	this->firstName = firstName;
	this->lastName = lastName;
}


Person::~Person()
{
}

const std::string Person::getFirstName() const
{
	return firstName;
}

void Person::setFirstName(const std::string firstName)
{
	this->firstName = firstName;
}

const std::string Person::getLastName() const
{
	return lastName;
}

void Person::setLastName(const std::string lastName)
{
	this->lastName = lastName;
}
