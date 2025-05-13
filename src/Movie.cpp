#include "Movie.h"


Movie::Movie() {
	title = "";
	genre = "";
	year = 0000;
	duration = 00.00;
}


Movie::Movie(const string& title, const string& genre, const int& year, const int& duration) {
	this->title = title;
	this->genre = genre;
	this->year = year;
	this->duration = duration;
}


void Movie::setTitle(const string& title) {
	this->title = title;
}


void Movie::setGenre(const string& genre) {
	this->genre = genre;
}


void Movie::setYear(const int& year) {
	this->year = year;
}


void Movie::setDuration(const int& duration) {
	this->duration = duration;
}


string Movie::getTitle() const {
	return title;
}


string Movie::getGenre() const {
	return genre;
}


int Movie::getYear() const {
	return year;
}


int Movie::getDuration() const {
	return duration;
}


void Movie::operator=(Movie m2) {
	title = m2.getTitle();
	genre = m2.getGenre();
	duration = m2.getDuration();
	year = m2.getYear();

}


bool Movie::operator==(const Movie& m2) {
	return title == m2.title && year == m2.year && duration == m2.duration && genre == m2.genre;
}


istream& operator>>(istream& ins, Movie& m) {
	string title, genre;
	int year;
	int duration;
	ins >> title >> year >> duration >> genre;
	m.setTitle(title);
	m.setGenre(genre);
	m.setYear(year);
	m.setDuration(duration);
	return ins;
}


ostream& operator<<(ostream& outs, Movie& m) {
	outs << "Title: " << m.title << endl << "Genre: " << m.genre << endl << "Release Year: " << m.year << endl 
	<< "Duration: " << m.duration << endl;
	return outs;
}