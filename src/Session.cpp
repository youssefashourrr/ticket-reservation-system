#include "Session.h"


Session::Session(){}


Session::Session(Movie& f, Hall& l, string dt, string time) {
	film = f;
	location = l;
	dayDate = dt;
	attendances = new Reservation[reservationCnt];
	timing = time;
}


void Session::setMovie(const Movie& film) {
	this->film = film;
}


void Session::setHall(const Hall& location) {
	this->location = location;
}


void Session::setDayDate(const string& dateTime) {
	this->dayDate = dateTime;
}


Movie Session::getMovie() const {
	return film;
}


Hall Session::getHall() const {
	return location;
}


string Session::getDayDate() const {
	return dayDate;
}


string Session::getTiming() const {
	return timing;
}


int Session::getReservationCount() const {
	return reservationCnt;
}


void Session::addReservation(const Reservation& r) {
	attendances[reservationCnt - 1] = r;
	reservationCnt++;
}


void Session::removeReservation(const string& id) {
	for (int i = 0; i < reservationCnt; ++i) {
		if (attendances[i].getOrderID() == id) {
			for (int j = i; j < reservationCnt - 1; ++j) {
				attendances[j] = attendances[j + 1];
			}
		}
	}
	reservationCnt--;
}

void Session::operator=(const Session& s) {
	film = s.film;
	location = s.location;
	dayDate = s.dayDate;
	timing = s.timing;
	reservationCnt = s.reservationCnt;

	if (s.attendances != nullptr) {
		attendances = new Reservation[reservationCnt];
		for (int i = 0; i < reservationCnt; ++i) attendances[i] = s.attendances[i];
	}
	else attendances = nullptr;
}

bool Session::operator==(const Session& s) {
	if (this->getMovie().getTitle() == s.getMovie().getTitle() && this->getHall().getID() == s.getHall().getID() && this->getTiming() == s.getTiming() && this->getDayDate() == s.getDayDate()) {
		return true;
	}
	else return false;
}