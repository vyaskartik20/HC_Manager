#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>
#include "OfficeOfAcademics.h"
#define SUCCESSFUL 1
#define STUDENT 1
#define AppointmentsPath "Appointments.txt"
#define HealthRecordPath "HealthRecord.txt"
#define SpecialistsRequestsPath "SpecialistsRequests.txt"

class DoctorsOffice
{
    // constexpr static char HealthRecordPath[25]= "HealthRecord.txt";
    // constexpr static char AppointmentsPath[25] = "Appointments.txt";
    // constexpr static char SpecialistsRequestsPath[25] = "SpecialistsRequests.txt";
    static int loginmode;
    static int SpecList[7];
    static char specname[7][40];
    public:

    static void PreLoadStuff()
    {
        //loading the appointments
        
        FILE *fp = fopen(SpecialistsRequestsPath,"r");
        char buffer[100];
        for(int i=0;i<7;i++)
        {
            char buffer[100];    
            fscanf(fp,"%[^\n]s",buffer);
            fgetc(fp);
            char specialist[40]; int requests;
            sscanf(buffer,"%s %d",specialist, &requests);
            SpecList[i] = requests;            
        }
    }
    static void login(int mode)
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
                DoctorsOffice::DisplayOptions();
                DoctorsOffice::loginmode = mode;               
            }
            else
            {
                std::cout << ("Enter credentials again\n");
                login(mode);
            }
    }

    static void viewHealthRecord(char ldapinp[])
    {
        FILE *fp = fopen(HealthRecordPath,"r");
        char prev[20];
        while(!feof(fp))
        {
            char buffer[100];
            fscanf(fp, "%[^\n]s", buffer);
            char ldap[20]; char record[100];
            sscanf(buffer, "%s %[^\n]s",ldap,record);
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
    static void addSpecialistRequest(int spec, int loginmode)
    {   
        if(loginmode==STUDENT)
        SpecList[spec-1] ++;
        else 
        SpecList[spec-1] +=5;
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
                fprintf(fp2,"%s %d\n",specialist,SpecList[spec-1]);
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
        fp2 = fopen("temp3.txt","w");
        //remove("temp3.txt");
        fclose(fp2);
    }

    static void viewSpecialistRequest()
    {
        std::cout << "Requests for specialists are as follows: \n";
        for(int i=0;i<7;i++)
        {
            std::cout << specname[i] << ": ";
            std::cout << SpecList[i] << "\n";
        }
    }

    static void addToAppointments(char ldapinp[], char appt[])
    {
        FILE *fp = fopen(AppointmentsPath,"a+");
        fprintf(fp,"%s %s\n",ldapinp, appt);
        fclose(fp);
    }

    static void ShowAppointments()
    {
        FILE *fp = fopen(AppointmentsPath,"r");
        std::cout << "Appointments are: \n";
        while(!(feof(fp)))
        {
            fputc(fgetc(fp),stdout);
        }
        std::cout << "\n";
    }

    static int* getSpecList()
    {
        return SpecList;
    }


    static void updateHealthRecord(char ldapinp[], char details[])
    {
        FILE *fp1 = fopen(HealthRecordPath,"r");
        FILE *fp2 = fopen("temp1.txt","w");
        char prev[20];
        while(!feof(fp1))
        {
            char buffer[100];
            fscanf(fp1,"%[^\n]s",buffer);
            char ldap[20]; char record[80];
            sscanf(buffer, "%s %[^\n]s", ldap, record);
            fgetc(fp1);
            if(strcmp(ldap,prev)==0)
                break;
            fprintf(fp2,"%s",buffer);
            if(strcmp(ldapinp,ldap)==0)
                fprintf(fp2," %s",details);
            fprintf(fp2,"\n");
            strcpy(prev,ldap);
        }
    }

    static void DisplayOptions()
    {
        if(loginmode==1)     //logging in as Doctor
        {
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
                    std::cin >> roll;
                    std::cout<< "Enter the leaves granted\n";
                    scanf("%[^\n]",leaves);
                    OfficeOfAcademics::UpdateMedicalLeaveRecord(roll,leaves);
                    break;
                }
                case 3:
                {
                    DoctorsOffice::ShowAppointments();
                    break;
                }
            }
        }
        
        if(loginmode==2)        //logging in as Staff
        {
            int flag = 1,flag2 = 1;
            do
            {
                std::cout << " 1: Update Health Record\n";
                std::cout << " 2: View Specialist request\n";
                std::cout << " 3: Send prescription to Pharmacy\n";
                std::cout << "Enter your choice (The corresponding number): ";
                int choice;
                std::cin >> choice;
                switch(choice)
                {
                    case 1:
                    {
                        char ldap[15];
                        char details[100];
                        std::cout<< "Enter LDAP of the Patient\n";
                        std::cin >>ldap;
                        std::cout<<"Enter the details that are to be updated";
                        scanf("%[^\n]s", details);
                        DoctorsOffice::updateHealthRecord(ldap,details);
                        break;
                    }
                    case 2:
                    {
                        DoctorsOffice::viewSpecialistRequest();
                        break;
                    }
                    case 3:
                    {
                        //To be done later. Pay attentoin
                        break;
                    }
                    default:
                    {
                        std::cout << "Please enter a valid option!\n";
                        flag2 = 0;
                    }
                }
                if(flag2==0)
                    flag = 1;
                else
                {
                    std::cout << "Would you like to go again? (Yes/No): ";
                    std::string response;
                    std::cin >> response;
                        std::transform(response.begin(), response.end(), response.begin(), ::tolower);
                        if(response.std::string::compare("yes")==0)
                            flag=1;
                        else
                            flag = 0;
                }
            }while(flag == 1);
        }
    }

    

    

};

class Doctor: public DoctorsOffice
{
    //friend void Patient::login();
};
class HCstaff: public DoctorsOffice
{
    //friend void Patient::login();
};

int DoctorsOffice::loginmode= 0;
int DoctorsOffice::SpecList[7] = {0};
char DoctorsOffice::specname[7][40] = {"Gastroenterologist",
            "Gynaecologist",
            "Paediatrician",
            "ENT_Specialist",
            "Dermatologist",
            "Orthopaedic_Specialist",
            "Ophthalmologist"};