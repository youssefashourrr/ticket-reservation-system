#include "Hall.h"


Hall::Hall() {
	rows = 10, cols = 10; id = "H-0";
	auditorium = new Seat * [rows];
	char i = 'A';
	for (int k = 0; k < rows; ++i, ++k) {
		auditorium[k] = new Seat[cols];
		for (int j = 1, l = 0; l < cols; ++j, ++l) {
			auditorium[k][l] = Seat(i, j);
		}
	}
}


Hall::Hall(const int& rows, const int& cols, const string& id) {
	this->rows = rows; this->cols = cols; this->id = id;
	auditorium = new Seat*[rows];
	char i = 'A';
	for (int k = 0; k < rows; ++k) {
		auditorium[k] = new Seat[cols];

		for (int j = 1; j-1 < cols; ++j) {
			auditorium[k][j-1] = Seat(i, j);
		}
		i++;
	}
}

bool Hall::isAvailable(const string& id) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (auditorium[i][j].getId() == id && auditorium[i][j].getState() == false) return false;
		}

	}
	return true;
}

void Hall::bookSeat(const string& id) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (auditorium[i][j].getId() == id && auditorium[i][j].getState() == true) {
				cout << auditorium[i][j].getId();
				auditorium[i][j].setState(false);
			}
		}
	}
}


Seat& Hall::getSeat(int x, int y) {
	return auditorium[x][y];
}


int Hall::getSize() {
	return rows;
}

string Hall::getID() {
	return id;
}


bool Hall::operator==(const Hall& h) {
	if (this->getID() == h.id) return true;
	else return false;
}
