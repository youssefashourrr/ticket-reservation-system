#include "CreditCard.h"


CreditCard::CreditCard() {
    cardNumber = "";
    cardHolderName = "";
    expirationDate = "";
    cvv = 000;
}


CreditCard::CreditCard(const string& cardNumber, const string& cardHolderName, const string& expirationDate, const int cvv) {
    this->cardNumber = cardNumber;
    this->cardHolderName = cardHolderName;
    this->expirationDate = expirationDate;
    this->cvv = cvv;
}


void CreditCard::setCardNumber(const string& cardNumber) {
    this->cardNumber = cardNumber;
}


void CreditCard::setCardHolderName(const string& cardHolderName) {
    this->cardHolderName = cardHolderName;
}


void CreditCard::setExpirationDate(const string& expirationDate) {
    this->expirationDate = expirationDate;
}


void CreditCard::setCvv(const int cvv) {
    this->cvv = cvv;
}


string CreditCard::getCardNumber() const {
    return cardNumber;
}


string CreditCard::getCardHolderName() const {
    return cardHolderName;
}


string CreditCard::getExpirationDate() const {
    return expirationDate;
}


int CreditCard::getCvv() const {
    return cvv;
}


bool CreditCard::isValidCardNumber(const string& cardNumber) { //Luhn's Algorthm//
    string sanitized;
    for (char ch : cardNumber) {
        if (std::isdigit(ch)) {
            sanitized += ch;
        }
    }

    int nDigits = sanitized.length();
    int sum = 0;
    bool isSecond = false;

    for (int i = nDigits - 1; i >= 0; i--) {
        int digit = sanitized[i] - '0';

        if (isSecond) {
            digit *= 2;
        }

        sum += digit / 10;
        sum += digit % 10;

        isSecond = !isSecond;
    }

    return (sum % 10 == 0);
}


bool CreditCard::isValidCardHolderName(const string& name) {
    if (name.empty()) return false;
    for (int i = 0; i < name.length(); ++i) {
        if (!isalpha(name[i]) && name[i] != ' ') return false;
    }

    return true;
}


bool CreditCard::isValidCVV(const string& cvv) {
    if (cvv.length() == 3 || cvv.length() == 4) {
        for (char c : cvv) {
            if (!isdigit(c)) return false;
        }
        return true;
    }
    return false;
}
