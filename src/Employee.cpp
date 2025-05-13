#include "Employee.h"


Employee::Employee(){}


Employee::Employee(const string& name, const string& email, const string& id, const int& age, const int& salary, const string& title, const string& shift ) : Person(name, email, id, age){
	this->salary = salary;
	this->title = title;
	this->shift = shift;
	
}


void Employee::setSalary(const int& salary) {
	this->salary = salary;
}


void Employee::setTitle(const string& title) {
	this->title = title;
}


void Employee::setShift(const string& shift) {
	this->shift = shift;
}


int Employee::getSalary() const {
	return salary;
}


string Employee::getTitle() const {
	return title;
}


string Employee::getShift() const {
	return shift;
}
