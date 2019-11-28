#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

#include "OfficeOfAcademics.h"
#include "DoctorsOffice.h"

#define AppointmentsPath "Appointments.txt"
#define HealthRecordPath "HealthRecord.txt"
#define SpecialistsRequestsPath "SpecialistsRequests.txt"
#define SpecialistsAvailabilityPath "SpecialistsAvailability.txt"

#define SUCCESSFUL 1
#define STUDENT 1
#define FACULTY 2
#define DOCTOR 1
#define HCSTAFF 2
#define YES 1
#define NO 0

int DoctorsOffice::loginmode= 0;
int DoctorsOffice::SpecList[7] = {0};
char DoctorsOffice::specname[7][40] = {"Gastroenterologist",
            "Gynaecologist",
            "Paediatrician",
            "ENT_Specialist",
            "Dermatologist",
            "Orthopaedic_Specialist",
            "Ophthalmologist"};

void DoctorsOffice::PreLoadStuff()
{
    FILE *fp = fopen(SpecialistsAvailabilityPath,"r");
    for(int i=0;i<7;i++)
    {
        char buffer[100];    
        fscanf(fp,"%[^\n]s",buffer);
        fgetc(fp);
        char specialist[40]; int availability;
        sscanf(buffer,"%s %d",specialist, &availability);
        SpecList[i] = availability;            
    }
}

void DoctorsOffice::login(int mode)
{
    char ldap[40], pass[40];
        std::cout << "Enter Employee ID: " ;
        std::cin >> ldap;
        std::cout << "Enter Password: " ;
        std::cin >> pass;
        int loginverify= OfficeOfAcademics::VerifyCredentials(ldap, pass);

        if(loginverify==SUCCESSFUL)
        {
            std::cout << ("You have been successfully logged in\n");
            DoctorsOffice::loginmode = mode;
            DoctorsOffice::DisplayOptions();
                            
        }
        else
        {
            std::cout << ("Enter credentials again\n");
            login(mode);
        }
}

void DoctorsOffice::viewHealthRecord(char ldapinp[])
{
    FILE *fp = fopen(HealthRecordPath,"r");
    char prev[20];
    while(!feof(fp))
    {
        char buffer[100];
        fscanf(fp, "%[^\n]s", buffer);
        char ldap[20]; char record[80];
        int len1 = strlen(buffer);
        buffer[len1] = '\n';
        buffer[len1+1] = '\0';
        sscanf(buffer, "%s %[^\n]s",ldap, record);
        fgetc(fp);
        if(strcmp(ldap, prev)==0)
            break;
        if(strcmp(ldapinp,ldap)==0)
        {
            std::cout << "Student LDAP ID: " << ldap << "\n" ;
            std::cout << "Health Record: " << record << "\n" ;
            break;
        }
        strcpy(prev,ldap);            
    }
}

void DoctorsOffice::addSpecialistRequest(int spec, int loginmode)
{   
    // if(loginmode==STUDENT)
    // SpecList[spec-1] ++;
    // else 
    // SpecList[spec-1] +=5;
    FILE *fp1 = fopen(SpecialistsRequestsPath,"r");
    FILE *fp2 = fopen("temp3.txt","w");
    char prev[40];
    while(!feof(fp1))
    {    
        char buffer[100];    
        fscanf(fp1,"%[^\n]s",buffer);
        fgetc(fp1);
        char specialist[40]; int requests;
        sscanf(buffer,"%s %d",specialist, &requests);
        if(strcmp(specialist,prev)==0)
            break;
        if(strcmp(specialist,specname[spec-1])==0)
        {
            if(loginmode==FACULTY)
            fprintf(fp2,"%s %d\n",specialist,requests+5);
            else fprintf(fp2,"%s %d\n",specialist,requests+1);
        }
        else
            fprintf(fp2,"%s %d\n",specialist, requests);
        strcpy(prev,specialist);
    }
    fclose(fp1);
    fclose(fp2);
    fp1 = fopen(SpecialistsRequestsPath,"w");
    fp2 = fopen("temp3.txt","r");
    while(!feof(fp2))
    {
        fputc(fgetc(fp2),fp1);
    }
    fclose(fp2);
    fclose(fp1);
    // fp2 = fopen("temp3.txt","w");
    // //remove("temp3.txt");
    // fclose(fp2);
}

void DoctorsOffice::viewSpecialistRequest()
{
    std::cout << "Requests for specialists are as follows: \n";
    FILE *fp = fopen(SpecialistsRequestsPath,"r");
    while(!feof(fp))
    {
        fputc(fgetc(fp),stdout);
    }
    fclose(fp);
}

void DoctorsOffice::addToAppointments(char ldapinp[], char appt[])
{
    //std::cout << ldapinp <<" " <<  appt << "\n";
    FILE *fp = fopen(AppointmentsPath,"a");
    fprintf(fp,"%s %s\n",ldapinp, appt);
    fclose(fp);
}

void DoctorsOffice::ShowAppointments()
{
    FILE *fp = fopen(AppointmentsPath,"r");
    std::cout << "Appointments are: \n";
    while(!(feof(fp)))
    {
        fputc(fgetc(fp),stdout);
    }
    std::cout << "\n";
}

int* DoctorsOffice::getSpecList()
{
    return SpecList;
}


void DoctorsOffice::updateHealthRecord(char ldapinp[], char details[])
{
    FILE *fp1 = fopen(HealthRecordPath,"r");
    FILE *fp2 = fopen("temp1.txt","w");
    char prev[20];
    while(!feof(fp1))
    {
        char buffer[100];
        fscanf(fp1,"%[^\n]s",buffer);
        char ldap[20]; char record[80];
        // int len1 = 0;
        // len1 = strlen(buffer);
        // buffer[len1] = '\n';
        // buffer[len1+1] = '\0';
        sscanf(buffer, "%s %[^\0]s", ldap, record);
        //fgetc(fp1);
        if(strcmp(ldap,prev)==0)
            break;
        fprintf(fp2,"%s",buffer);
        if(strcmp(ldapinp,ldap)==0)
            fprintf(fp2," %s",details);
        fprintf(fp2,"\n");
        strcpy(prev,ldap);
    }
    fclose(fp1);
    fclose(fp2);
    fp1 = fopen(HealthRecordPath,"w");
    fp2 = fopen("temp1.txt","r");
    while(!feof(fp2))
    {
        fputc(fgetc(fp2),fp1);
    }
    fclose(fp2);
    fp2 = fopen("temp1.txt","w");
    remove("temp1.txt");
    fclose(fp2);
}

void DoctorsOffice::DisplayOptions()
{
    if(loginmode==DOCTOR)     //logging in as Doctor
    {
        int repeat = YES;
        do
        { 
            int  incorrectChoice = NO;           
            std::cout << " 1: View health Record\n";
            std::cout << " 2: Send Medical Leave Record\n";
            std::cout << " 3: Show Apointments\n";
            std::cout << "Enter your choice (The corresponding number): ";
            int choice;
            std::cin >> choice;
            switch(choice)
            {
                case 1:
                {
                    char ldap[25];
                    std::cout << "Enter LDAP of the patient \n";
                    std::cin >> ldap;
                    DoctorsOffice::viewHealthRecord(ldap);
                    break;
                }
                case 2:
                {
                    char roll[15];
                    char leaves[60];
                    std::cout << "Enter roll number of the student\n";
                    scanf("%s",roll);
                    std::cout<< "Enter the leaves granted\n";
                    fflush(stdin);
                    scanf("%[^\n]s",leaves);
                    OfficeOfAcademics::UpdateMedicalLeaveRecord(roll,leaves);
                    break;
                }
                case 3:
                {
                    DoctorsOffice::ShowAppointments();
                    break;
                }
                default :
                {
                    std::cout << "  --  Please enter valid choice!  --\n";
                    incorrectChoice = YES;
                }
            }
                if(incorrectChoice==YES)
                    repeat = YES;
                else
                {
                    std::cout << "Would you like to perform more operations as Doctor? (Yes/No): ";
                    std::string response;
                    std::cin >> response;
                        std::transform(response.begin(), response.end(), response.begin(), ::tolower);
                        if(response.std::string::compare("yes")==0)
                            repeat = YES;
                        else
                            repeat = NO;
                }
            }while(repeat == YES);
        }
    
    if(loginmode==HCSTAFF)        //logging in as Staff
    {
        int repeat = YES;
        do
        {
            int incorrectChoice = NO;
            std::cout << " 1: Update Health Record\n";
            std::cout << " 2: View Specialist request\n";
            std::cout << "Enter your choice (The corresponding number): ";
            int choice;
            std::cin >> choice;
            switch(choice)
            {
                case 1:
                {
                    char ldap[15];
                    char details[100];
                    std::cout << "Enter LDAP of the Patient\n";
                    std::cin >> ldap;
                    fflush(stdin);
                    std::cout<<"Enter the details that are to be updated\n";
                    fgetc(stdin);
                    scanf("%[^\n]s", details);
                    DoctorsOffice::updateHealthRecord(ldap,details);
                    break;
                }
                case 2:
                {
                    DoctorsOffice::viewSpecialistRequest();
                    break;
                }
                
                default:
                {
                    std::cout << "Please enter a valid option!\n";
                    incorrectChoice = YES;
                }
            }
            if(incorrectChoice==YES)
                repeat = YES;
            else
            {
                std::cout << "Would you like to perform more operations as HC Staff? (Yes/No): ";
                std::string response;
                std::cin >> response;
                    std::transform(response.begin(), response.end(), response.begin(), ::tolower);
                    if(response.std::string::compare("yes")==0)
                        repeat = YES;
                    else
                        repeat = NO;
            }
        }while(repeat == YES);
    }
}