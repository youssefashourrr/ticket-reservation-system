#include "Person.h"
#include "Employee.h"


class Admin : public Person, public Employee {
protected:
	string key;

public:
	Admin();

	void setKey(const string&);
	string getKey() const;
};

