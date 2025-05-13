#pragma once
#include <string>
using namespace std;


class CreditCard {
		string cardNumber;
		string cardHolderName;
		string expirationDate;
		int cvv;
		
	public:
		CreditCard();
		CreditCard(const string&, const string&, const string&, const int);

		void setCardNumber(const string&);
		void setCardHolderName(const string&);
		void setExpirationDate(const string&);
		void setCvv(const int);

		string getCardNumber() const;
		string getCardHolderName() const;
		string getExpirationDate() const;
		int getCvv() const;

		bool isValidCardNumber(const string&);
		bool isValidCardHolderName(const string&);
		bool isValidCVV(const string&);
};

