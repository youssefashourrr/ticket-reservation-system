#pragma once
#include "Movie.h"
#include "Hall.h"
#include "Reservation.h"

using namespace std;


class Session{
	Movie film;
	Hall location;
	string dayDate;
	string timing;
	Reservation* attendances; int reservationCnt = 1;

public:
	Session();
	Session( Movie&,Hall&, string,string);

	void setMovie(const Movie&);
	void setHall(const Hall&);
	void setDayDate(const string&);

	Movie getMovie() const;
	Hall getHall() const;
	string getDayDate() const;

	string getTiming() const;
	int getReservationCount() const;

	void addReservation(const Reservation&);
	void removeReservation(const string&);

	void operator=(const Session&);
	bool operator==(const Session&);
};