#pragma once
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsFindCurrencyScreen: protected clsScreen
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
	static void ShowFindCurrency() {
        _DrawScreenHeader("\t  Find Currency Screen");

        cout << "\nFind By: [1] Code or [2] Country ? ";
        short Answer = 1;

        cin >> Answer;

        if (Answer == 1)
        {
            string CurrencyCode;
            cout << "\nPlease Enter CurrencyCode: ";
            CurrencyCode = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _PrintCurrencyInfo(Currency);
        }
        else
        {
            string Country;
            cout << "\nPlease Enter Country Name: ";
            Country = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _PrintCurrencyInfo(Currency);
        }
    }
};

