#include "TimeTable.h"
#pragma warning(disable:4996)


string TimeTable::getCurrentDateString(int daysOffset) {
        auto now = chrono::system_clock::now();
        now += chrono::hours(24 * daysOffset);
        time_t t = chrono::system_clock::to_time_t(now);
        tm* tm_nextDay = gmtime(&t);

        char buffer[80];
        strftime(buffer, 80, "%a", tm_nextDay);

        ostringstream oss;
        oss << put_time(tm_nextDay, "%d/%m");
        return oss.str() + " " + string(buffer);
}


TimeTable::TimeTable() {
    DAYS = 3;
    DAILY_MAX_SHOWTIMES = 9;
    showtime = new Session * [DAYS];
    for (int i = 0; i < DAYS; ++i) {
        showtime[i] = new Session[DAILY_MAX_SHOWTIMES];
    }
    for (int i = 0; i < DAYS; ++i) {
        showtimeCounts[i] = 0;
        startDate[i] = getCurrentDateString(i);
    }
}


TimeTable::~TimeTable()
{}


int TimeTable::getDays() const {
    return DAYS;
}


int TimeTable::getDailyMaxShowtimes() const {
    return DAILY_MAX_SHOWTIMES;
}


string TimeTable::getDayDate(int dayIndex) const {
    return startDate[dayIndex];
}


Session TimeTable::getTime(int dayIndex, int slotIndex) const {
    return showtime[dayIndex][slotIndex];
}


void TimeTable::addShow(Session St, int dayIndex,int sessionIndex) {
    if (dayIndex > 0 || dayIndex <= DAYS || showtimeCounts[dayIndex] <= DAILY_MAX_SHOWTIMES) {
        Hall h = St.getHall();
        showtime[dayIndex][sessionIndex] = St;
    }
}


void TimeTable::operator=(TimeTable other) {
    int days = other.getDays();
    int maxShowtimes = other.getDailyMaxShowtimes();
    for (int i = 0; i < days; ++i) {
        for (int j = 0; j < maxShowtimes; ++j) {
            Session session = other.getTime(i, j);
            addShow(session, i, j);
        }
    }
}