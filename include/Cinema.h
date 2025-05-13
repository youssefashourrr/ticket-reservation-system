#pragma once

#include "Session.h"
#include "Hall.h"
#include "TimeTable.h"

#include <fstream>
#include <sstream>
using namespace std;


class Cinema {
	Movie* filmList; int filmCnt;
	Hall halls[3];
	
	string times[3][3] = { { "10:00 AM","1:00 PM", "3:00 PM" }, { "12:30 PM","3:30 PM", "6:30 PM" }, { "2:15 PM", "5:15 PM", "8:15 PM" } };
	TimeTable tt;

public:
	Cinema();
	
	int getFilmCnt() const;
	int getHallsCnt() const;
	int getTimesCnt() const;

	void addFilm(const string&,const int&);
	void removeFilm(const string&);

	TimeTable getSchedule();
};

