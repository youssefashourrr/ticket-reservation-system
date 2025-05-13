#pragma once
#include <iostream>
#include <string>
#include <format>

using namespace std;


class Seat {
	string id;
	float price;
	bool state;

public:
	Seat();
	Seat(char, int);

	void setId(const string&);
	void setPrice(const float&);
	void setState(bool);

	string getId() const;
	float getPrice() const;
	bool getState() const;

	void operator=(const Seat&);
};

