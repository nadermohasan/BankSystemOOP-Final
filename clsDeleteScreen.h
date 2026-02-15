#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
#include <vector>
class clsDeleteScreen: protected clsScreen
{
public:
    static void DeleteClient() {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }
        _DrawScreenHeader("\tDelete Client Screen");
        string AccountNumber;
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        Client.Print();
        cout << "\nAre you sure you want to delete this client ? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            if (Client.Delete() == true) {
                cout << "Client Deleted successfully!" << endl;
                Client.Print();
            }
            else {
                cout << "Error, Client was not deleted!" << endl;
                Client.Print();
            }
        }
    }
};

