#include "system.h"
#include "Customer.h"
#include "Movie.h"
#include "TimeTable.h"

#include <QPushButton>
#include <QApplication>
#include <QMessageBox>
#include <QRandomGenerator>

#pragma warning(disable : 4996)


ReservationSystem::ReservationSystem(QWidget* parent) : QMainWindow(parent) {

    ui.setupUi(this);
    this->setFixedSize(1000, 750);

    usericon = QIcon("ticket.png");
    adminbtn = QIcon("admin.png");
    rbutton = QIcon("RB.png");
    eseat = QIcon("AvailableSeat.png");
    rseat = QIcon("ReservedSeat.png");
    seseat = QIcon("SelectedSeat.png");
    QFont font("Helvetica", 24, QFont::Bold);

    Header = new QLabel("Welcome to الشعب الصيني Cinema", this);
    tickets = new QPushButton(this);
    Admin = new QPushButton(this);

    tickets->setIcon(usericon);
    tickets->setIconSize(QSize(100, 100));
    tickets->setFixedSize(100, 100);
    tickets->setStyleSheet("border: none;");
    tickets->setGeometry(600, 200, 0, 0);

    Admin->setIcon(adminbtn);
    Admin->setIconSize(QSize(100, 100));
    Admin->setFixedSize(100, 100);
    Admin->setStyleSheet("border: none;");
    Admin->setGeometry(300, 200, 0, 0);

    Header->setFont(font);
    Header->setAlignment(Qt::AlignCenter);
    int labelWidth = 600;
    int labelHeight = 80;
    int x = (width() - labelWidth) / 2;
    int y = 30;
    Header->setGeometry(x, y, labelWidth, labelHeight);

    connect(Admin, &QPushButton::clicked, this, &ReservationSystem::getAdminPassword);
    connect(tickets, &QPushButton::clicked, this, &ReservationSystem::DisplayMovies);
 
    ReturnButton = new QPushButton(this);
    ReturnButton->hide();
    ReturnButton->setIcon(rbutton);
    ReturnButton->setIconSize(QSize(50, 50));
    ReturnButton->setFixedSize(50, 50);
    ReturnButton->setStyleSheet("border: none;");
    ReturnButton->setGeometry(10, 2, 0, 0);
}


ReservationSystem::~ReservationSystem()
{}


void ReservationSystem::DisplayMovies() { 
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton->text( ) == tickets->text()) Interface = false;   
    else {
        delete Days;
        Days = nullptr;
    }
    ReturnButton->show();
    connect(ReturnButton, &QPushButton::clicked, this, &ReservationSystem::MainMenu);

    for (int i = 0; i < 3; i++) {
        slot = schedule.getTime(i, i);
        M = slot.getMovie();
        Movie_button[i] = new QPushButton(QString::fromStdString(M.getTitle()), this);
        Movie_button[i]->show();
        Movie_button[i]->setGeometry(225 + i * 200, 170, 170, 270);
    
        connect(Movie_button[i], &QPushButton::clicked, this, &ReservationSystem::DisplaySessions);
    }
    if (Interface) {
        int width = 200;
        int height = 30;
        int x = (this->width() - width) / 2;
        int y = (this->height() - height) / 2;
        EditMovie = new QPushButton("Edit Movie", this);
        EditMovie->setGeometry(x, y +200, width, height);
        connect(EditMovie, &QPushButton::clicked, this, &ReservationSystem::ChangeMovie);
    }
    
    Admin->hide();
    tickets->hide();
    Header->setText("Choose A Movie");
}


void ReservationSystem::getAdminPassword() {
    QString styleSheet = "QLineEdit {" "background-color: #f0f0f0;" "border: 1px solid #ccc;" "border-radius: 5px;" "padding: 5px;""}";
    adminConfirm = new QPushButton("Login", this);

    Admin->hide();

    tickets->hide();
    int width = 200;
    int height = 30;
    int x = (this->width() - width) / 2;
    int y = (this->height() - height) / 2;

    AdminPassword= new QLineEdit(this);
    AdminPassword->setEchoMode(QLineEdit::Password);
    AdminPassword->setPlaceholderText("Admin Password ");
    adminConfirm->show();
    AdminPassword->show();
    AdminPassword->setGeometry(x, y - 130, width, height);
    adminConfirm->setGeometry(x, y - 90, width, height);
    AdminPassword->setStyleSheet(styleSheet);
    connect(adminConfirm, &QPushButton::clicked, this, &ReservationSystem::pswrdConfirmation);
}


void ReservationSystem::DisplaySessions() {
    Header->setText("Choose Time");
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    int hsize = h.getSize();
    if (clickedButton->text() == ReturnButton->text()) {
        if (Chairs != nullptr) {
            for (int x = 0; x < hsize; x++) {
                if (Chairs[x] != nullptr) {
                    for (int y = 0; y < hsize; y++) {
                        delete Chairs[x][y];
                        Chairs[x][y] = nullptr;
                    }
                    delete[] Chairs[x];
                    Chairs[x] = nullptr;
                }
            }
            delete[] Chairs;
            Chairs = nullptr;
            MovieName = slot.getMovie().getTitle();
        }
        Confirm->hide();
    }
    else MovieName = clickedButton->text().toStdString();

    Days = new QTabWidget(this);
    int spacing = 100;
    for (int i = 0; i < 3; i++) {
        string name = schedule.getDayDate(i);
        Day[i] = new QWidget();
        Days->addTab(Day[i], QString::fromStdString(name));
        Day[i]->setGeometry(20 * (1 + i), 40, 20, 20);
        Movie_button[i]->hide();
    }
    int buttonIndex = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 9; j++) {
                slot = schedule.getTime(i, j);
                if (MovieName == slot.getMovie().getTitle()) {
                    sessionButtons[buttonIndex] = new QPushButton(QString::fromStdString(slot.getTiming()), Day[j / 3]);
                    sessionButtons[buttonIndex]->show();
                    sessionButtons[buttonIndex]->setGeometry(250 + (j % 3) * 140, 100, 120, 80);
                    connect(sessionButtons[buttonIndex], &QPushButton::clicked, this, &ReservationSystem::DisplayHall);
                    buttonIndex++;
                }
            }
            if (buttonIndex == 9) break;
        }

    Days->show();
    Days->setGeometry(0,100, 1000, 500);
    connect(ReturnButton, &QPushButton::clicked, this, &ReservationSystem::DisplayMovies);
}


void ReservationSystem::MainMenu() {
    delete Days;
    Days = nullptr;
    for (int i = 0; i < 3; i++) {
        delete Movie_button[i];
        Movie_button[i] = nullptr;
    }
    ReturnButton->hide();
    Header->setText("Main Menu");
    Admin->show();
    tickets->show();
}

void ReservationSystem::DisplayHall() {
    Header->setText("Choose Seats");
    QMessageBox msg;
    
    Confirm = new QPushButton("Confirm", this);
    Confirm->show();
    Confirm->setGeometry(910, 10, 80, 30);
    connect(Confirm, &QPushButton::clicked, this, &ReservationSystem::BookTickets);
    connect(ReturnButton, &QPushButton::clicked, this, &ReservationSystem::DisplaySessions);

    bool flag = false;
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    timing = clickedButton->text().toStdString();
    int tabIndex = Days->indexOf(clickedButton->parentWidget());
    DayDate = Days->tabText(tabIndex).toStdString();

    delete Days;
    Days = nullptr;

    int indix = 0;
    int indiy = 0;
    for (int x = 0; x < 3; x++) {
        for (int  y =0 ; y < 9; y++) {
            slot = schedule.getTime(x, y);
            if (MovieName == slot.getMovie().getTitle() && timing == slot.getTiming() && DayDate == slot.getDayDate()) {
                indix = x;
                indiy = y;
            }
        }
    }

    slot = schedule.getTime(indix, indiy);
    h = slot.getHall();
    
    hsize = h.getSize();
   
    Chairs = new QPushButton * *[hsize];

    int seatWidth = 50;
    int seatHeight = 50; 

    string fname = "Session" + to_string(indix) + "-" + to_string(indiy) + ".txt";
    ifstream file(fname);
    string line;
    int lnum = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line == "0") {
                h.getSeat(lnum / 10, lnum % 10).setState(false);
            }
            else {
                h.getSeat(lnum / 10, lnum % 10).setState(true);
            }
            lnum++;
        }
        file.close();
    }
   
    for (int i = 0; i < hsize; i++) {
        Chairs[i] = new QPushButton * [hsize];
        for (int j = 0;  j < hsize; j++) {
            if (hsize != 10) {
                float price_updated = h.getSeat(i, j).getPrice() * 1.4;
                h.getSeat(i, j).setPrice(price_updated);
            }

            Seat chair = h.getSeat(i, j);
            QString seatId = QString::fromStdString(chair.getId());
            Chairs[i][j] = new QPushButton(seatId, this);
            if (chair.getState() == false) {
                Chairs[i][j]->setIcon(rseat);
                if (Interface == false) Chairs[i][j]->setEnabled(0);
                else connect(Chairs[i][j], &QPushButton::clicked, this, &ReservationSystem::rSelected);
            }
            else {
                Chairs[i][j]->setIcon(eseat);
                connect(Chairs[i][j], &QPushButton::clicked, this, &ReservationSystem::Select);
            }
            Chairs[i][j]->setIconSize(QSize(40, 40));
            Chairs[i][j]->setFixedSize(60, 60);
            Chairs[i][j]->setStyleSheet("QPushButton { color: transparent; border: none; }");
            
            int xPos = (j+5) * seatWidth;
            int yPos = (i+2.5) * seatHeight;

            if(hsize != 10) {
                xPos += 90;
                yPos += 50;
            }
            Chairs[i][j]->setGeometry(xPos, yPos, seatWidth, seatHeight);
            Chairs[i][j]->show();
        }
    }

    ButtonLabel[0] = new QLabel(this);
    ButtonLabel[0]->setPixmap(QPixmap("AvailableSeat.png").scaled(20, 20));
    ButtonLabel[0]->setText("Available Seat");
    ButtonLabel[0]->setContentsMargins(5, 5, 5, 5);
}
   

void ReservationSystem::Select() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    clickedButton->setIcon(seseat);
    connect(clickedButton, &QPushButton::clicked, this, &ReservationSystem::Deselect);
}


void ReservationSystem::rSelected() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    clickedButton->setIcon(seseat);
    connect(clickedButton, &QPushButton::clicked, this, &ReservationSystem::rDeselect);
}


void ReservationSystem::Deselect() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    clickedButton->setIcon(eseat);
    connect(clickedButton, &QPushButton::clicked, this, &ReservationSystem::Select);  
}


void ReservationSystem::rDeselect() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    clickedButton->setIcon(rseat);
    connect(clickedButton, &QPushButton::clicked, this, &ReservationSystem::rSelected);
}


void ReservationSystem::BookTickets() {  
    Money = new QLabel("Total Basket", this);
    connect(ReturnButton, &QPushButton::clicked, this, &ReservationSystem::MainMenu);
    QMessageBox msg;
    hsize = h.getSize();
    Seat s;
    int numReserves = 0;

    int randomNumber = QRandomGenerator::global()->bounded(100, 1000);
    string num = std::to_string(randomNumber);
    HallIdentifier = h.getID()[0]; HallIdentifier += h.getID()[2]; HallIdentifier += num;

    
    for (int i = 0; i < hsize; i++) {
        for (int j = 0; j < hsize; j++) {
            QIcon btnicon = Chairs[i][j]->icon();
            QPixmap btnPixmap = btnicon.pixmap(btnicon.actualSize(QSize(100, 100)));
            QPixmap seseatPixmap = seseat.pixmap(seseat.actualSize(QSize(100, 100)));
            bool validity = btnPixmap.toImage() == seseatPixmap.toImage();
     
            if (validity) numReserves++;
        }
    }
    reservedChair = new Reservation(HallIdentifier, slot.getMovie(), numReserves);

    int placingIndex = 0;
    for (int i = 0; i < hsize; i++) {
        for (int j = 0; j < hsize; j++) {
            QIcon btnicon = Chairs[i][j]->icon();
            QPixmap btnPixmap = btnicon.pixmap(btnicon.actualSize(QSize(100, 100)));
            QPixmap seseatPixmap = seseat.pixmap(seseat.actualSize(QSize(100, 100)));
            bool validity = btnPixmap.toImage() == seseatPixmap.toImage();
            if (validity) { 
                if (Interface) {
                    h.getSeat(i, j).setState(true);
                }
                else {
                    h.getSeat(i, j).setState(false);
                }
                reservedChair->addSeat(h.getSeat(i, j), placingIndex++);
            }
        }
    }

    for (int i = 0; i < reservedChair->getSeatCnt(); ++i) {
        string messageID = reservedChair->getReserved(i);
        msg.setText(QString::fromStdString(messageID));
        msg.exec();
    }

    int indix, indiy;
    bool flag = false;
    for (int x =0 ; x < 3; x++) {
        for (int y =0; y < 9; y++) {
            if (schedule.getTime(x,y).getMovie().getTitle() == slot.getMovie().getTitle() && schedule.getTime(x, y).getHall().getID() == slot.getHall().getID() && schedule.getTime(x, y).getTiming() == slot.getTiming() && schedule.getTime(x, y).getDayDate() == slot.getDayDate()) {
                indix = x; indiy = y;
            }
        }
    }
    sessionfile = "Session" + to_string(indix) + "-" + to_string(indiy) + ".txt";
    ofstream file(sessionfile);
    if (file.is_open()) {
        for (int i = 0; i < hsize; i++) {
            for (int j = 0; j < hsize; j++) {
                file << h.getSeat(i, j).getState();
                file << endl;
            }
        }
    }

    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton->text() == Confirm->text()) {
        if (Chairs != nullptr) {
            for (int x = 0; x < hsize; x++) {
                if (Chairs[x] != nullptr) {
                    for (int y = 0; y < hsize; y++) {
                        delete Chairs[x][y];
                        Chairs[x][y] = nullptr;
                    }
                    delete[] Chairs[x];
                    Chairs[x] = nullptr;
                }
            }
            delete[] Chairs;
            Chairs = nullptr;
        }
    }

    string price = "The Total Price:  " + to_string(reservedChair->calcTotalPrice()) ;
    Money->setText(QString::fromStdString(price));
    delete Confirm;
    Confirm = nullptr;

    if (Interface == false) CreateCustomer();
    else {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to free these seats?",QMessageBox::Yes | QMessageBox::No);
 
        if (reply == QMessageBox::Yes) {
            int x = reservedChair->getSeatCnt();
            ofstream file(sessionfile);

            if (file.is_open()) {
                for (int i = 0; i < hsize; i++) {
                    for (int j = 0; j < hsize; j++) {
                        for (int z = 0; z < x; z++) {
                            if (reservedChair->getReserved(z) == h.getSeat(i, j).getId()) {
                                h.getSeat(i, j).setState(true);
                            }
                        }
                        file << h.getSeat(i, j).getState();
                        file << endl;
                    }
                }
            }
        }
        MainMenu();
    }
}


void ReservationSystem::CreateCustomer() {
    Header->setText("Payment");

    int width = 200;
    int height = 30;
    int x = (this->width() - width) / 2;
    int y = (this->height() - height) / 2;
    QString styleSheet = "QLineEdit {" "background-color: #f0f0f0;" "border: 1px solid #ccc;" "border-radius: 5px;" "padding: 5px;""}";

    Namebar = new QLineEdit(this);
    Email = new QLineEdit(this);
    CardNumber = new QLineEdit(this);
    CardHolder = new QLineEdit(this);
    Month = new QComboBox(this);
    Year = new QComboBox(this);
    Payment = new QPushButton("Confrim Payment",this);
    cancel = new QPushButton("Cancel", this);

    for (int i = 1; i <= 12; ++i) { Month->addItem(QString("%1").arg(i, 2, 10, QChar('0')));}
    for (int i = 2024; i <= 2032; ++i) {Year->addItem(QString::number(i));}

    Namebar->show();
    Email->show();
    CardNumber->show();
    CardHolder->show();
    Money->show();
    Month->show();
    Year->show();
    Payment->show();
    cancel->show();

    Namebar->setPlaceholderText("Name: ");
    Email->setPlaceholderText("E-mail: ");
    CardNumber->setPlaceholderText("Card Number: ");
    CardHolder->setPlaceholderText("Holder Name: ");

    Namebar->setStyleSheet(styleSheet);
    Email->setStyleSheet(styleSheet);
    CardNumber->setStyleSheet(styleSheet);
    CardHolder->setStyleSheet(styleSheet);

    Namebar->setGeometry(x, y-250, width, height);
    Email->setGeometry(x, y-210, width, height);
    CardNumber->setGeometry(x, y - 170, width, height);
    CardHolder->setGeometry(x, y - 130, width, height);
    Money->setGeometry(x, y - 50, width, height);
    Month->setGeometry(x, y-90, 50, 30);
    Year->setGeometry(x+70, y-90, 50, 30); 
    Payment->setGeometry(x, y - 50, width, height);
    Payment->setGeometry(x, y - 50, width, height);
    cancel->setGeometry(x, y - 10, width, height);
    connect(Payment, &QPushButton::clicked, this, &ReservationSystem::ConfirmPayment);
    connect(cancel, &QPushButton::clicked, this, &ReservationSystem::CancelReservation);
}


void ReservationSystem::ConfirmPayment() {
    QMessageBox msg;
    msg.setText("Reservation Done");
    msg.exec();

    Namebar->hide();
    Email->hide();
    CardNumber->hide();
    CardHolder->hide();
    Money->hide();
    Month->hide();
    Year->hide();
    Payment->hide();
    cancel->hide();
    MainMenu();
}

void ReservationSystem::CancelReservation() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to cancel your reservation?", QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        int x = reservedChair->getSeatCnt();
        
        ofstream file(sessionfile);
        if (file.is_open()) {
            for (int i = 0; i < hsize; i++) {
                for (int j = 0; j < hsize; j++) {
                    for (int z = 0; z < x; z++) {
                        if (reservedChair->getReserved(z) == h.getSeat(i, j).getId()) {
                           h.getSeat(i, j).setState(true);
                        }
                    }
                    file << h.getSeat(i, j).getState();
                    file << endl;
                }
            }
        }

    }
}


void ReservationSystem::pswrdConfirmation() {
    QMessageBox error;
    if (AdminPassword->text().toStdString() == "123") {
        error.setText("Welcome Admin");
        error.exec();
        adminConfirm->hide();
        AdminPassword->hide();
        Interface = true;
        DisplayMovies();
    }
    else {
        error.setText("Not An Admin");
        error.exec();
        MainMenu();
        delete adminConfirm;
        delete AdminPassword;
    }
}


void ReservationSystem::ChangeMovie() {
    int width = 200;
    int height = 30;
    int x = (this->width() - width) / 2;
    int y = (this->height() - height) / 2;
    delete EditMovie;
    for (int i = 0; i < 3; i++) {
        delete Movie_button[i];
        Movie_button[i] = nullptr;
    }

    movies = new QComboBox(this);
    NewMovie = new QLineEdit(this);
    Submit = new QPushButton("Submit Movie", this);

    QString styleSheet = "QLineEdit {" "background-color: #f0f0f0;" "border: 1px solid #ccc;" "border-radius: 5px;" "padding: 5px;""}";
    NewMovie->setPlaceholderText("Movie Name ");
    NewMovie->setStyleSheet(styleSheet);

    string filePath = "MovieList.txt";
    ifstream file(filePath);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream iss(line);
            string title, genre;
            int year, duration;

            iss >> title >> genre >> year >> duration;

            QString qTitle = QString::fromStdString(title);
            movies->addItem(qTitle);
        }
        file.close();
        movies->show();
        movies->setGeometry(x, y - 200, width, height);
        NewMovie->setGeometry(x, y - 150, width, height);
        Submit->setGeometry(x, y - 100, width, height);
        Submit->show();
        connect(Submit, &QPushButton::clicked, this, &ReservationSystem::submitName);
        NewMovie->show();
    }
}


void ReservationSystem::submitName() {
    int currentIndex = movies->currentIndex();
    QMessageBox msg;
    msg.setText(NewMovie->text());
    msg.exec();
    msg.setText(QString::number(currentIndex));
    msg.exec();
    Movie_button[currentIndex]->setText(NewMovie->text());
    MainMenu();
}