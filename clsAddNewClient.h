#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
#include <vector>
class clsAddNewClient:protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }
    static void _Print(clsBankClient &Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }
public:
    static void ShowAddNewClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }
        _DrawScreenHeader("\Add Client Screen");
        string AccountNumber;
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(AccountNumber)) {
            cout << "Account Number is already Exist. Please Enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient NewClient = clsBankClient::GetNewClientObject(AccountNumber);
        clsAddNewClient::_ReadClientInfo(NewClient);
        clsBankClient::enSaveResults SaveResult;
        SaveResult = NewClient.Save();
        switch (SaveResult) {
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "Client Added Successfully!" << endl;
            _Print(NewClient);
            break;
        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "Cliend Add Failed." << endl;
        }
    }
};

