#include "Person.h"


Person::Person(){}


Person::Person(const string& name, const string& email, const string& id, const int& age) {
	this->name = name;
	this->email = email;
	this->id = id;
	this->age = age;
}


void Person::setName(const string& name) {
	this->name = name;
}


void Person::setEmail(const string& email) {
	this->email = email;
}


void Person::setID(const string& id) {
	this->id = id;
}


void Person::setAge(const int& age) {
	this->age = age;
}


string Person::getName() const {
	return name;
}


string Person::getEmail() const {
	return email;
}


string Person::getID() const {
	return id;
}


int Person::getAge() const {
	return age;
}
