#pragma once
#include "Person.h"


class Employee : public Person{
	int salary;
	string title;
	string shift;

public:
	Employee();
	Employee(const string&, const string&, const string&, const int&, const int&, const string&, const string&);

	void setSalary(const int&);
	void setTitle(const string&);
	void setShift(const string&);

	int getSalary() const;
	string getTitle() const;
	string getShift() const;
};

