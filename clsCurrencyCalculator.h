#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
class clsCurrencyCalculator: protected clsScreen
{
private:
	static void _PrintCurrencyInfo(clsCurrency Currency) {
		cout << "\nConvert From:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();

		cout << "\n_____________________________\n";

	}
	static float Calculator(float From, float Amount) {
		return Amount / From;
	}
public:
	static void ShowCurrencyCalculator() {
		char Answer = 'n';
		do {
			string CurrencyFrom = "";
			string CurrencyTo = "";
			float ExchangeAmount = 0;
			_DrawScreenHeader("Currency Calculator");
			cout << "Enter Currency to Convert From: ";
			cin >> CurrencyFrom;
			cout << "Enter Currrency to Convert To: ";
			cin >> CurrencyTo;
			cout << "Enter Exchange Amount: ";
			cin >> ExchangeAmount;
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyFrom);
			_PrintCurrencyInfo(Currency);
			cout << ExchangeAmount << " " << Currency.CurrencyCode() << " = " << Calculator(Currency.Rate(), ExchangeAmount) << CurrencyTo;
			cout << "\nDo you want to perform another calculator ? Y|N ";
			cin >> Answer;
			if(toupper(Answer) == 'Y')
				system("cls");
		} while (toupper(Answer) == 'Y');
	}
};

