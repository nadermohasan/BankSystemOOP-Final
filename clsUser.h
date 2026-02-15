#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "|")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);
        if (vUserData.size() < 7)
        {
            return _GetEmptyUserObject();
        }
        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], vUserData[5], stoi(vUserData[6]));

    }
    static string _ConverUserObjectToLine(clsUser User, string Seperator = "|")
    {

        string UserRecord = "";
        UserRecord += User.UserName + Seperator;
        UserRecord += User.Password + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;

    }
    struct stLoginRegistration;
    static stLoginRegistration _ConvertLoginRegistrationLineToRecord(string Line) {
        stLoginRegistration LoginRegisterRecord;

        vector <string> LoginRegisterDataLine = clsString::Split(Line, "|");
        if (LoginRegisterDataLine.size() < 4)
            return LoginRegisterRecord;
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.Username = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = LoginRegisterDataLine[2];
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;
    }
    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }
    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }
    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }
    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }
    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }
    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }
    string GetUserName()
    {
        return _UserName;
    }
    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;
    void SetPassword(string Password)
    {
        _Password = Password;
    }
    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;
    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }
    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;
    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }
    static clsUser Find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }
    static string GetNewUserLine(clsUser User) {
        string Line = clsUser::_ConverUserObjectToLine(User);
        return Line;
    }
    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };
    enum enPermissions { pShowClientsList = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactionsMenu = 32, pManageUsers = 64, pLoginRegistrations = 128, pCurrencyExchange = 256, pFullAccess = -1 };
    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }

    }
    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }
    static bool IsUserExist(string UserName, string password)
    {

        clsUser User = clsUser::Find(UserName, password);
        return (!User.IsEmpty());
    }
    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }
    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }
    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }
    bool CheckAccessPermissions(enPermissions Permission) {
        if (this->Permissions == enPermissions::pFullAccess) {
            return true;
        }
        return (Permissions & Permission) == Permission;
    }
    struct stLoginRegistration {
        string DateTime;
        string Username;
        string Password;
        int Permissions;
    };
    static  vector <stLoginRegistration> GetLoginRegisterList()
    {
        vector <stLoginRegistration> vLoginRegisterRecord;

        fstream MyFile;
        MyFile.open("LoginRegisteration.txt", ios::in);

        if (MyFile.is_open())
        {

            string Line;

            stLoginRegistration LoginRegisterRecord;

            while (getline(MyFile, Line))
            {

                LoginRegisterRecord = _ConvertLoginRegistrationLineToRecord(Line);

                vLoginRegisterRecord.push_back(LoginRegisterRecord);

            }

            MyFile.close();

        }

        return vLoginRegisterRecord;

    }
};

