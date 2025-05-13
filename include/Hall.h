#pragma once
#include "Seat.h"
#include "Movie.h"

using namespace std;


class Hall {
	int rows, cols;
	string id;
	Seat** auditorium;

public:
	Hall();
	Hall(const int&, const int&, const string&);

	bool isAvailable(const string&);
	void bookSeat(const string&);

	Seat& getSeat(int,int);
	int getSize();
	string getID();

	bool operator ==(const Hall&);
};

