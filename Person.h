#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person
{
	private:
		std::string firstName;
		std::string lastName;

		void setUnknownName();


	public:
		Person();
		Person(const std::string firstName, const std::string lastName);
		virtual ~Person();
		const std::string getFirstName() const;
		void setFirstName(const std::string firstName);
		const std::string getLastName() const;
		void setLastName(const std::string lastName);

};

#endif // NAME_H

