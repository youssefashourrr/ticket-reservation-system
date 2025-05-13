#pragma once
#include "system.ui"
#include "Cinema.h"
#include "CreditCard.h";

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>


class ReservationSystem : public QMainWindow {
    Q_OBJECT

public:
    ReservationSystem(QWidget *parent = nullptr);
    ~ReservationSystem();

public slots:
    void getAdminPassword();
    void DisplayMovies();
    void DisplaySessions();
    void MainMenu();
    void DisplayHall();
    void Select();
    void rSelected();
    void Deselect();
    void rDeselect();
    void BookTickets();
    void CreateCustomer();
    void ConfirmPayment();
    void CancelReservation();
    void pswrdConfirmation();
    void ChangeMovie();
    void submitName();

private:
    Ui::ReservationSystemClass ui;
    QLabel* Header, *ButtonLabel[3],*Money;
    QPushButton *tickets, *Admin, *Movie_button[3], *ReturnButton, *sessionButtons[9], *Confirm, *Payment, *cancel,*adminConfirm , *EditMovie,*Submit;
    QLineEdit* Namebar, * Email, * CardNumber, * CardHolder, * CVV, *AdminPassword, *NewMovie;
    QComboBox *Month, * Year, *movies;
    QIcon rbutton, rseat, eseat, adminbtn, usericon,seseat;
    QPushButton*** Chairs;
    QTabWidget* Days;
    QWidget* Day[3];
    Cinema MainCinema;
    TimeTable schedule = MainCinema.getSchedule();
    Customer C;
    CreditCard visa;
    Movie M;
    Hall h;
    Session slot;
    Reservation *reservedChair;
    string MovieName;
    string DayDate;
    string timing;
    string HallIdentifier;
    string sessionfile;
    int hsize;
    bool Interface = false;
};
