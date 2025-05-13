#include "Reservation.h"


Reservation::Reservation() {
	orderID = "H000";
	client; film; 
	seatCnt = 1;
	reserved = new Seat[seatCnt];
}


Reservation::Reservation(const string& orderID, const Movie& film, const int& seatCnt) {
	this->orderID = orderID;
	this->film = film;
	this->seatCnt = seatCnt;
	reserved = new Seat[seatCnt];
}


void Reservation::setSeatCnt(const int& seatCnt) {
	this->seatCnt = seatCnt;
}


void Reservation::setOrderID(const string& orderID) {
	this->orderID = orderID;
}


void Reservation::setClient(const Customer& client) {
	this->client = client;
}


void Reservation::setFilm(const Movie& film) {
	this->film = film;
}

int Reservation::getSeatCnt() const {
	return seatCnt;
}


string Reservation::getOrderID() const {
	return orderID;
}



Movie Reservation::getFilm() const {
	return film;
}


string Reservation::getReserved(int n) const {
	return reserved[n].getId();
}



void Reservation::addSeat(Seat s, int index) {
	reserved[index] = s;
}


void Reservation::cancelReservation() {
	for (int i = 0; i < seatCnt; ++i) {
		reserved[i].setState(true);
	}
	delete[] reserved;
	reserved = nullptr;
}


Reservation::~Reservation() {
	delete[] reserved;
}

float Reservation::calcTotalPrice() {
	float res = 0;
	for (int i = 0; i < seatCnt; ++i) {
		res += reserved[i].getPrice();
	}
	return res;
}





