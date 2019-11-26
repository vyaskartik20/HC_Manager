// OfficeOfAccounts Header File
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
//#include <windows.h>
#define SUCCESSFUL 1

class OfficeOfAccounts
{
    public:
        static void login()
        {
            char EmployeeID[40], pass[40];
            std::cout << "Enter EmployeeID: " ;
            std::cin >> EmployeeID;
            std::cout << "Enter Password: " ;
            std::cin >> pass;
            int loginverify = OfficeOfAcademics::VerifyCredentials(EmployeeID, pass);
            if(loginverify==SUCCESSFUL)
            {
                std::cout << ("You have been successfully logged in!\n");
                DisplayOptions();
            }
            else
            {
                std::cout << ("Enter credentials again\n");
                login();
            }
        }//
        // static void ViewMedicalExpenses()
        // {
        //     std::cout << " 1. A particular Patient's MedicalExpenses\n 2.whole  MedicalExpense\n";
        //     int choice;
        //     std::cin >> choice ;
        //     if(choice == 1)
        //     {
        //         char ldap[40];
        //         std::cout <<" Enter Patient ID:\n";
        //         std::cin >> ldap;
        //         // output the data corresponding to this ID.If ID doesnot exists, return 0.
        //         std::cout << "Do You Want to know Any other Patient's expenses?"
        //     }
        //     else if(choice == 2)
        //     {
        //         //output the whole expenditure
        //     }
        //     else
        //     {
        //         std::cout <<"Please Select a Valid option \n";
        //         ViewMedicalExpenses();
        //     }

        // }
        static void UpdateExpenses(double amt)
        {
        //     std::cout << "Enter the ldap ID for which you wish to Update Medical Expenses: \n";
        //     char ldap[40];
        //     std::cin >> ldap ;
        //    // IMPORTANT    //verifyCredentials(ldap);
        //     std::cout << "Enter the Amount you wish to Update Against given ldap id: \n";
        //     //Update;


        }
        static void DisplayOptions()
        {
            int flag = 0;
            int flag2 = 0;
            do
            {        	
		        std::cout << " 1:View Medical Expenses\n";      //can be made into two if we want(for whole expenses and for particular patient)
		        std::cout << " 2:Update Medical Expenses\n";
		        // std::cout << " 3:Get Test Results\n";
		        // std::cout << " 4:Request Medical Supplements\n";
		        //std::cout << " 5:Get Medical Certificate\n";
		        std::cout << "Enter your choice (The corresponding number): ";
		        int choice;
		        std::cin >> choice;

		        switch(choice)
		        {
		            case 1:         //getting Medical expenses record
		            {   
		                //ViewMedicalExpenses();
		                break;
		            }
		            case 2:         // enquiring regarding specialist
		            {
		                //UpdateMedicalExpenses();
		                break;
		            }
		            default:
		            {
						std::cout << "Please enter a valid option!\n";
		            	flag = 1;
		            }
		        }
		        if(flag == 1)
		        flag2 = 1;
		        else
		        {
		        	std::cout << " Do you wish to go again? (Yes/No): ";
		        	std::string resp1;
		        	std::cin >> resp1;
		        	std::transform(resp1.begin(), resp1.end(), resp1.begin(), ::tolower);
					if(resp1.std::string::compare("yes")==0)
                        flag2=1;
                    else
                        flag2 = 0;
                }	        
			}while(flag==1);
        }
};