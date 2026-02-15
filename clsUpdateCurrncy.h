#pragma once
#include <vector>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsUpdateCurrncy : protected clsScreen
{
private:
	static void _PrintCurrencyInfo(clsCurrency Currency) {
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();

		cout << "\n_____________________________\n";
	}

public:
	static void UpdateCurrency() {
		string CurrencyCode;
		float NewRate = 0.0;
		char Answer = 'y';
		cout << "\nPlease Enter CurrencyCode: ";
		CurrencyCode = clsInputValidate::ReadString();
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrencyInfo(Currency);
		cout << "Are you sure you want to update currency rate ? y|n ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {
			cout << "\nUpdate Currency:\n";
			cout << "_____________________________\n";
			cout << "Enter New Rate: ";
			cin >> NewRate;
			Currency.UpdateRate(NewRate);
			cout << "Currency Rate Updated Successfully.";
			_PrintCurrencyInfo(Currency);
		}
	}
};