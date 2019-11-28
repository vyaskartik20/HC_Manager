#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include <cstdio>

#include "Pharmacy.h"
#include "OfficeOfAccounts.h"
#include "OfficeOfAcademics.h"

#define medRequestsPath "MedsRequests.txt"
#define inventoryPath "PharmacyInventory.txt"

#define SUCCESSFUL 1
#define AVAILABLE 1
#define NOT_AVAILABLE 0
#define YES 1
#define NO 0


char Pharmacy::currEmployeeID[40] = {0};

int Pharmacy::checkMedsInPharmacy(char medinp[])
{
    FILE *fp = fopen(inventoryPath,"r");
    char prev[20];
    while(!feof(fp))
    {
        char buffer[100];
        fscanf(fp, "%[^\n]s", buffer);
        char med[20]; int amt;
        sscanf(buffer, "%s %d",med,&amt);
        fgetc(fp);
        if(strcmp(med, prev)==0)
            break;
        if(strcmp(med,medinp)==0)
        {
            if (amt>0) return AVAILABLE;        //medicine is available
            else return NOT_AVAILABLE;
        }
        strcpy(prev,med);            
    }
    return NOT_AVAILABLE;
}


void Pharmacy::addMedRequest(char med[], char ldap[])
{
    FILE *fp = fopen(medRequestsPath,"a+");
    fprintf(fp,"%s %s\n",med, ldap);
    fclose(fp);           
}


void Pharmacy::showMedRequests()
{
    std::cout << "Medicine/Supplement requests are: \n";
    FILE *fp = fopen(medRequestsPath,"r");
    while(!feof(fp))
    {
        fputc(fgetc(fp),stdout);
    }
    std::cout << "\n";
}

void Pharmacy::login()
{
    char EmployeeID[40], pass[40];
    std::cout << "Enter Employee ID: ";
    std::cin >> EmployeeID;
    std::cout << "Enter Password: ";
    std::cin >> pass;
    int loginverify = OfficeOfAcademics::VerifyCredentials(EmployeeID, pass);
    if(loginverify==SUCCESSFUL)
    {
        std::cout << ("You have been successfully logged in\n");
        strcpy(currEmployeeID, EmployeeID);
        DisplayOptions();
    }
    else
    {
        std::cout << ("Enter credentials again\n");
        login();
    }
}

void Pharmacy::ShowMedsList()
{
    FILE *fp = fopen(inventoryPath,"r");
    std::cout << "Medicines lisst is-: \n";

    while(!(feof(fp)))
    {
        fputc(fgetc(fp),stdout);
    }
    std::cout << "\n";
}

void Pharmacy::UpdateMedsList(char med_nameinp[],  int amtinp)
{
    FILE *fp1 = fopen(inventoryPath,"r");
    FILE *fp2 = fopen("temp2.txt","w");
    char prev[20];
    while(!feof(fp1))
    {
        char buffer[100];
        fscanf(fp1,"%[^\n]s",buffer);
        char med_name[25]; int amt;
        sscanf(buffer, "%s %d", med_name, &amt);
        fgetc(fp1);
        if(strcmp(med_name,prev)==0)
            break;
        if(strcmp(med_name,med_nameinp)==0)
            fprintf(fp2,"%s %d",med_nameinp, amt-amtinp);
        else
            fprintf(fp2,"%s",buffer);
        fprintf(fp2,"\n");
        strcpy(prev,med_name);
    }
    fclose(fp1);
    fclose(fp2);
    fp1 = fopen(inventoryPath,"w");
    fp2 = fopen("temp2.txt","r");

    while(!feof(fp2))
    {
        fputc(fgetc(fp2),fp1);
    }

    fclose(fp1);
    fclose(fp2);
}

void Pharmacy::DisplayOptions()
{   
    int repeat = YES;
    int incorrectChoice = NO;
    do
    {   
        std::cout << "Enter your choice (The corresponding number): ";
        std::cout << " 1: Show Medicine List\n";
        std::cout << " 2: Update Medicine List\n";
        std::cout << " 3: Update Expenses With Office Of Accounts";
        std::cout << " 4: Show Medicine Requests\n";
        int choice;
        std::cin >> choice;
        switch(choice)
        {
            case 1:         //getting Meds list
            {   
                ShowMedsList();
                break;
            }
            case 2:         // Update medicines list
            {
                std::cout << "Enter the medicine followed by the amount: ";
                char med_name[25];
                int amt;
                std::cin >> med_name;
                std::cin >> amt;
                UpdateMedsList(med_name,amt);
                break;
            }
            case 3:         // updating expenses
            {
                std::cout << "Enter the amount: ";
                double amt ;
                std:: cin >> amt;
                OfficeOfAccounts::UpdateExpenses(amt);
                break;
            }
            case 4:         
            {
                showMedRequests();
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
            std::cout << " Do you wish to perform another operation from Pharmacy? (Yes/No): ";
            std::string resp1;
            std::cin >> resp1;
            std::transform(resp1.begin(), resp1.end(), resp1.begin(), ::tolower);
            if(resp1.std::string::compare("yes")==0)
                repeat = YES;
            else
                repeat = NO;
        }	        
    }while(repeat==YES);
}


