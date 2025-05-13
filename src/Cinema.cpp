#include "Cinema.h"


Cinema::Cinema() {
	filmCnt = 3; filmList = new Movie[filmCnt];
	ifstream file("movies.txt");
	string line;
	int numMovies = 0;

	if (file.is_open()) {
		while (getline(file, line) && numMovies < filmCnt) {
			istringstream iss(line);
			string title, genre;
			int year, duration;

			iss >> title >> genre >> year >> duration;
			filmList[numMovies] = Movie(title, genre, year, duration);
			numMovies++;
		}
		file.close();
		halls[0] = Hall(10, 10, "H-1");
		halls[1] = Hall(6, 6, "H-2");
		halls[2] = Hall(10, 10, "H-3");
		string filename = "Sessionss.txt";
		ofstream file(filename);

		if (file.is_open()) {
			for (int i = 0; i < tt.getDays(); i++) {
				tt.getCurrentDateString(i);
				for (int j = 0; j < filmCnt; j++) {
					for (int k = 0; k < filmCnt; k++) {
						Session s(filmList[i], halls[k], tt.getDayDate(j), times[i][k]);
						tt.addShow(s, i, ((j * filmCnt) + k) % 10);
					}
				}
			}
		}
	}
}


int Cinema::getFilmCnt() const {
	return filmCnt;
}


int Cinema::getHallsCnt() const {
	return sizeof(halls) / sizeof(Hall);
}


int Cinema::getTimesCnt() const {
	return sizeof(times) / sizeof(string);
}


void Cinema::addFilm(const string& title, const int& pos) {
	filmList[pos].setTitle(title);
}


void Cinema::removeFilm(const string& title) {
	for (int i = 0; i < filmCnt; ++i) {
		if (filmList[i].getTitle() == title) {
			for (int j = i; j < filmCnt - 1; ++j) filmList[j] = filmList[j + 1];
			filmCnt--;
			return;
		}
	}
	// cout << "Movie does not exist in your list.";
}


TimeTable Cinema::getSchedule() {
	return tt;
}