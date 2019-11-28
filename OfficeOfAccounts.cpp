// OfficeOfAccounts Header File
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

#include "OfficeOfAcademics.h"
#include "OfficeOfAccounts.h"

#define ExpensesPath "Expenses.txt"

#define SUCCESSFUL 1
#define YES 1
#define NO 0


void OfficeOfAccounts::login()
{
    char EmployeeID[40], pass[40];
    std::cout << "Enter EmployeeID: ";
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
}

void OfficeOfAccounts::ViewMedicalExpenses()
{
    std::cout << "Cumulative Medical Expenses: Rs. ";
    FILE *fp = fopen(ExpensesPath,"r");
    double amt;
    fscanf(fp,"%lf", &amt);
    fclose(fp);
    std::cout << amt << "\n";
}

void OfficeOfAccounts::UpdateExpenses(double amt)
{

    FILE *fp = fopen(ExpensesPath,"r");
    double StoredAmount;
    fscanf(fp,"%lf", &StoredAmount);
    fclose(fp);
    amt += StoredAmount;
    fp = fopen(ExpensesPath,"w");
    fprintf(fp,"%.2lf",amt);
    fclose(fp);
}

void OfficeOfAccounts::DisplayOptions()
{
    int incorrectChoice = NO;
    int repeat = YES;
    do
    {        	
        std::cout << " 1:View Medical Expenses\n";      //can be made into two if we want(for whole expenses and for particular patient)
        //std::cout << " 2:Update Medical Expenses\n";
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
                ViewMedicalExpenses();
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
            std::cout << " Do you wish to perform more functions as an OfficeOfAccounts user? (Yes/No): ";
            std::string resp1;
            std::cin >> resp1;
            std::transform(resp1.begin(), resp1.end(), resp1.begin(), ::tolower);
            if(resp1.std::string::compare("yes")==0)
                repeat = YES;
            else
                repeat = NO;
        }	        
    }while(repeat == YES);

}
