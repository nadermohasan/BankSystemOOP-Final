#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUser: protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }
public:
    static void ShowDeleteScreen() {
        _DrawScreenHeader("\tDelete User Screen");
        string UserName = "";
        char Answer;
        cout << "Please, Enter the Username to delete: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName)) {
            cout << "Username dosn't exist, please enter another one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);
        cout << "Are you sure you want to delete this user ? Y|N: ";
        cin >> Answer;
        if (User.Delete())
        {
            cout << "\nUser Deleted Successfully :-)\n";
            _PrintUser(User);
        }
        else
        {
            cout << "\nError User Was not Deleted\n";
        }
    }
};

