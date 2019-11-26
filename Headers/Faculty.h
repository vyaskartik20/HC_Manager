#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESSFUL 1

class Faculty
{
public:
    static void login()
    {
        char ldap[40], pass[40];
        std::cout << "Enter LDAP ID: ";
        std::cin >> ldap;
        std::cout << "Enter Password: ";
        std::cin >> pass;
        int loginverify = OfficeOfAcademics::VerifyCredentials(ldap, pass);

        if (loginverify == SUCCESSFUL)
        {
            std::cout << ("You have been successfully logged in\n");
            FurtherOptions();
        }
        else
        {
            std::cout << ("Enter credentials again\n");
            login();
        }
    }

    static void FurtherOptions()
    {
        std::cout << ("Enter the roll number of the student to retrive Medical Leave Record: ");
        char roll[15];
        std::cin >> roll;
        OfficeOfAcademics::GetMedicalLeaveRecord(roll);
    }
};