#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

#include "Patient.h"
#include "Faculty.h"
#include "DoctorsOffice.h"
#include "OfficeOfAccounts.h"
#include "Pharmacy.h"

#define DOCTOR 1
#define HCSTAFF 2
#define STUDENT 1
#define NO 0
#define YES 1

int main()
{
    DoctorsOffice::PreLoadStuff();
    int repeat = YES;
    do
    {
        int choice;
        std::cout << "\t***IIT Jodhpur Health Center Management System***\n";
        std::cout << "How do you wish to login? (Enter the coorresponding number):\n";
        std::cout << " 1: Patient\n"; 
        std::cout << " 2: Faculty\n"; 
        std::cout << " 3: Doctor's Office\n"; 
        std::cout << " 4: Office of Accounts\n"; 
        std::cout << " 5: Pharmacy\n";
        std::cout << "Your choice - ";
        std::cin >> choice;

        switch(choice)
        {
            case 1:	//login for Patients
            {
                int repeat = YES, incorrectChoice = NO;
                do
                {
                    int subchoice;
                    std::cout << "You wish to login as? (Enter the corresponding number):\n";
                    std::cout << " 1: Student\n";
                    std::cout << " 2: Faculty\n";
                    std::cout << " 3: Staff\n";
                    std::cout << "Your choice - ";
                    std::cin >> subchoice;
                    switch(subchoice)
                    {
                        case 1:
                        {
                            student::login(1);		//students as patients
                            break;
                        }
                        case 2:
                        {				
                            faculty::login(2);		//faculty as patients
                            break;
                        }
                        case 3:
                        {
                            staff::login(3);		//staff as patients
                            break;
                        }
                        default:
                        {
                            std::cout << "Please enter a valid option!\n";
                            incorrectChoice = YES;
                        }
                    }
                    if(incorrectChoice == YES)
                    repeat = YES;
                    else
                    {
                        std::cout << "Do you wish to login as patient again? (yes/no): ";
                        std::string response;
                        std::cin >> response;
                        std::transform(response.begin(), response.end(), response.begin(), ::tolower);
                        if(response.std::string::compare("yes")==0)
                        {
                            repeat = YES;
                        }
                        else repeat = NO;
                    }
                } while(repeat == YES);
                break;
            }
            case 2:		// login for Faculty
            {
                Faculty::login();
                break;
            }
            case 3:		// Login for Doctor's Office
            {
                //DoctorsOffice::PreLoadStuff()
                int repeat = YES, incorrectChoice = NO;
                do
                {
                    int subchoice;
                    std::cout << "You wish to login as? (Enter the corresponding number)\n";
                    std::cout << " 1: Doctor\n";
                    std::cout << " 2: Staff\n";
                    std::cout << "Your choice - ";
                    std::cin >> subchoice;
                    switch(subchoice)
                    {
                        case 1:		//Login as Doctor
                        {	
                            Doctor::login(DOCTOR); //login mode is a doctor
                            break;
                        }
                        case 2:		// Login as HC Staff
                        {		
                            HCstaff::login(HCSTAFF);
                            break;
                        }
                        default:
                        {
                            std::cout << "Please enter a valid option!\n";
                            incorrectChoice = YES;
                        }
                    }
                    if(incorrectChoice == YES)
                    repeat = YES;
                    else
                    {
                        std::cout << "Do you wish to login from Doctors' Office again? (yes/no): ";
                        std::string response;
                        std::cin >> response;
                        std::transform(response.begin(), response.end(), response.begin(), ::tolower);
                        if(response.std::string::compare("yes")==0)
                        {
                            repeat = YES;
                        }
                        else repeat = NO;
                    }
                } while(repeat==YES);
                break;
            }
            case 4:		//Login for Office Of Accounts
            {
                OfficeOfAccounts::login();
                break;
            }	
            case 5:		//Login for Pharmacys
            {
                Pharmacy::login();
            }
            
        }
        std::cout << "Do you wish to re-run the program? (yes/no): ";
        std::string response;
        std::cin >> response;
        std::transform(response.begin(), response.end(), response.begin(), ::tolower);
        if(response.std::string::compare("yes")==0)
        {
            repeat = YES;
        }
        else repeat = NO;
    }while(repeat == YES);

}
