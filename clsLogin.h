#pragma once

#include <iostream>
#include <cstdlib>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
#include "clsDate.h"

class clsLogin :protected clsScreen
{

private:
    static void _LoginTrials(string username, string password, bool LoginFailed) {
        static int counter = 3;
        if (LoginFailed) {
            counter--;
            cout << "You have " << counter << " Trials.";
            if (counter < 1) {
                system("cls");
                cout << "You are locked after 3 trials.";
                exit(0);
            }
        }
    }
    static void _SaveLoginData(clsUser User = CurrentUser, string Date = clsDate::GetSystemDateTimeString())
    {

        fstream MyFile;
        MyFile.open("LoginRegisteration.txt", ios::out | ios::app);

        string DataLine;

        if (MyFile.is_open())
        {
            MyFile << Date << "|";
            MyFile << clsUser::GetNewUserLine(CurrentUser);
            MyFile << endl;
            MyFile.close();

        }

    }
    static  void _Login()
    {
        bool LoginFaild = false;
        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!\n\n";
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;


            CurrentUser = clsUser::Find(Username, Password);
            LoginFaild = CurrentUser.IsEmpty();
            if (!LoginFaild) {
                _SaveLoginData();
            }
            _LoginTrials(Username, Password, LoginFaild);
        } while (LoginFaild);

        clsMainScreen::ShowMainMenu();
    }

public:


    static void ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        _Login();

    }

};

