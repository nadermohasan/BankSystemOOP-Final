#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
class clsUpdateUser : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser& User) {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }
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
    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += clsUser::enPermissions::pShowClientsList;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClient;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTransactionsMenu;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        return Permissions;

    }

public:
    static void ShowUpdateUserScreen() {
        _DrawScreenHeader("\tUpdate User Screen");
        string Username = "";
        char Answer;
        cout << "Please, Enter the Username to Update: ";
        Username = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(Username)) {
            cout << "Username dosn't exist, please enter another one: ";
            Username = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(Username);
        _PrintUser(User);
        cout << "Are you sure you want to update the user info ? Y|N: ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";
            _ReadUserInfo(User);
            _PrintUser(User);
            cout << "Are you sure you want to save the data ? Y|N: ";
            cin >> Answer;
            if (toupper(Answer) == 'Y') {
                clsUser::enSaveResults Save;
                Save = User.Save();
                switch (Save) {
                case clsUser::enSaveResults::svSucceeded:
                    cout << "User Updated Successfully!";
                    break;
                case clsUser::enSaveResults::svFaildEmptyObject:
                    cout << "User Update Failed!";
                    break;
                }
            }
        }
    }
};

