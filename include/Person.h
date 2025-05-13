#pragma once
#include <iostream>

using namespace std;


class Person {
	string name;
	string email;
	string id;
	int age;

public:
	Person();
	Person(const string&, const string&, const string&, const int&);

	void setName(const string&);
	void setEmail(const string&);
	void setID(const string&);
	void setAge(const int&);

	string getName() const;
	string getEmail() const;
	string getID() const;
	int getAge() const;
};
