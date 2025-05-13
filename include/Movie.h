#pragma once
#include <iostream>
#include <string>
#include <format>

using namespace std;


class Movie{
	string title, genre;
	int year;
	int duration;

public:
	Movie();
	Movie(const string&, const string&, const int&, const int&);

	void setTitle(const string&);
	void setGenre(const string&);
	void setYear(const int&);
	void setDuration(const int&);

	string getTitle() const;
	string getGenre() const;
	int getYear() const;
	int getDuration() const;
	

	void operator=(Movie);
	bool operator==(const Movie&);

	friend istream& operator>>(istream&, Movie&);
	friend ostream& operator<<(ostream&, Movie&);
};