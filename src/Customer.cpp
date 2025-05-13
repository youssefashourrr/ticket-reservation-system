#include "Customer.h"


Customer::Customer(){
	name = "";
	email = "";
}


Customer::Customer(const string& name, const string& email){
	this->name = name;
	this->email = email;
}


void Customer::setName(const string& name){
	this->name = name;
}


void Customer::setEmail(const string& email){
	this->email = email;
}


string Customer::getName() const{
	return name;
}


string Customer::getEmail() const{
	return email;
}


bool Customer::operator==(const Customer& c2){
	return name == c2.name && email == c2.email;
}


bool Customer::isValidEmail(const string& email) {
        size_t atPos = email.find('@');
        if (atPos == string::npos || atPos == 0 || atPos == email.size() - 1)
            return false;
        string localPart = email.substr(0, atPos);
        string domainPart = email.substr(atPos + 1);

        if (localPart.empty() || domainPart.empty()) 
            return false;

        size_t dotPos = domainPart.find('.');

        if (dotPos == string::npos || dotPos == 0 || dotPos == domainPart.size() - 1)
            return false;

        for (char ch : localPart)
        {
            if (!(isalnum(ch) || ch == '_' || ch == '.' || ch == '+' || ch == '-')) 
                return false;
        }
        for (char ch : domainPart) {
            if (!(isalnum(ch) || ch == '-' || ch == '.')) return false;
        }

        if (localPart.find("..") != string::npos || domainPart.find("..") != string::npos)
            return false;

        return true;
}


ostream& operator<<(ostream& outs, Customer& c) {
	outs << "Name: " << c.name << endl << "Email: " << c.email << endl;
	return outs;
}

