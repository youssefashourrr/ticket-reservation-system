#pragma once
#include "Movie.h"
#include "Customer.h"
#include "Seat.h"
#include "Hall.h"


class Reservation{
	int seatCnt;
	string orderID;
	Customer client;
	Movie film;
	Seat* reserved;

public:
	Reservation();
	Reservation(const string&, const Movie&, const int&);

	void setSeatCnt(const int&);
	void setOrderID(const string&);
	void setClient(const Customer&);
	void setFilm(const Movie&);
	
	int getSeatCnt() const;
	string getOrderID() const;
	Customer getClient() const;
	Movie getFilm() const;
	string getReserved(int) const;
	
	void addSeat(Seat, int);
	float calcTotalPrice();
	
	void cancelReservation();

	~Reservation();
};

