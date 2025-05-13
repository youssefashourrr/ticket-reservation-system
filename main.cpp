#include "system.h"
#include <QtWidgets/QApplication>
#include <QLineEdit>


int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	ReservationSystem w;
	w.show();
	return a.exec();
}