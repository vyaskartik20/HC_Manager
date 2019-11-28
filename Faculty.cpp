#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

#include "Faculty.h"
#include "OfficeOfAcademics.h"

#define SUCCESSFUL 1
#define YES 1
#define NO 0

void Faculty::login()
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

void Faculty::FurtherOptions()
{
    int repeat = YES;
    while(repeat == YES)
    {
        std::cout << ("Enter the Roll Number of the student to retrieve Medical Leave Record: ");
        char roll[15];
        std::cin >> roll;
        OfficeOfAcademics::GetMedicalLeaveRecord(roll);
        std::cout << "Do you wish to check for another student? (Yes/No): ";
        std::string response;
        std::cin >> response;
        std::transform(response.begin(), response.end(), response.begin(), ::tolower);
        if(response.std::string::compare("yes")==0)
        {
            repeat = YES;
        }
        else repeat = NO;
    }
}
