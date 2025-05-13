#pragma once
#include "Session.h"

#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <fstream>
using namespace std;


class TimeTable {
private:
    int DAYS, DAILY_MAX_SHOWTIMES;
    int showtimeCounts[9];
    string startDate[3];
    Session** showtime;

public:
    TimeTable();
    ~TimeTable();

    string getCurrentDateString(int);
    int getDays() const;
    int getDailyMaxShowtimes() const;
    string getDayDate(int) const;

    Session getTime(int, int) const;
    void addShow( Session, int,int);
    void operator = (TimeTable);
};