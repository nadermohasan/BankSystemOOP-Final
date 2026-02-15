#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
#include <vector>
class clsUpdateClient: protected clsScreen
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
    static void _Print(clsBankClient& Client)
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
    static void UpdateClient() {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient))
        {
            return;
        }
        _DrawScreenHeader("\tUpdate Client Screen");
        string AccountNumber;
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _Print(Client);
        cout << "\n\nUpdate Client Info:";
        cout << "\n____________________\n";
        _ReadClientInfo(Client);
        clsBankClient::enSaveResults SaveResult;
        SaveResult = Client.Save();
        switch (SaveResult) {
        case  clsBankClient::enSaveResults::svSucceeded:
            cout << "\nAccount Updated Successfully :-)\n";
            Client.Print();
            break;
        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }
};

