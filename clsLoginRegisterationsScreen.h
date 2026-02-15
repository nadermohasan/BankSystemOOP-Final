#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsUser.h"
#include <fstream>
#include <vector>
class clsLoginRegisterationsScreen: protected clsScreen
{
private:
    static void PrintLoginRegisterRecordLine(clsUser::stLoginRegistration LoginRegistration)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegistration.DateTime;
        cout << "| " << setw(20) << left << LoginRegistration.Username;
        cout << "| " << setw(20) << left << LoginRegistration.Password;
        cout << "| " << setw(10) << left << LoginRegistration.Permissions;
    }

public:

	static void ShowLoginRegistrationsScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegistrations))
        {
            return;
        }
        vector <clsUser::stLoginRegistration> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

        string Title = "\tLogin Register List Screen";
        string SubTitle = "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsUser::stLoginRegistration Record : vLoginRegisterRecord)
            {

                PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};