#include <iostream>
#include <cstring>

#include "OfficeOfAcademics.h"

#define LDAPPath "LDAP.txt"
#define LeaveRecordPath "LeaveRecord.txt"

#define SUCCESSFUL 1

void OfficeOfAcademics::GetMedicalLeaveRecord(char roll[15])
{
    FILE* fp=fopen(LeaveRecordPath,"r");
    while(!feof(fp))
    {    
        char buffer[100];    
        fscanf(fp,"%[^\n]s",buffer);
        fgetc(fp);
        char croll[15];
        char leaves[100];
    
        sscanf(buffer,"%s %[^\0]s",croll,leaves);
        if(!strcmp(croll,roll))
        {
            printf("%s\n",buffer);
            break;
        } 
    }
}

void OfficeOfAcademics::UpdateMedicalLeaveRecord(char rollinp[],char leavesinp[])
{
    FILE *fp1 = fopen(LeaveRecordPath,"r");
    FILE *fp2 = fopen("temp.txt","w");
    char prev[20];
    while(!feof(fp1))
    {
        char buffer[100];
        fscanf(fp1,"%[^\n]s",buffer);
        char roll[20]; char leaves[80];
        sscanf(buffer, "%s %[^\n]s", roll, leaves);
        fgetc(fp1);
        if(strcmp(roll,prev)==0)
            break;
        fprintf(fp2,"%s",buffer);
        if(strcmp(rollinp,roll)==0)
            fprintf(fp2," %s",leavesinp);
        fprintf(fp2,"\n");
        strcpy(prev,roll);
    }
    fclose(fp1);
    fclose(fp2);
    fp1 = fopen(LeaveRecordPath,"w");
    fp2 = fopen("temp.txt","r");
    while(!feof(fp2))
    {  
        fputc(fgetc(fp2),fp1);
    }
    fclose(fp2);
    fp2 = fopen("temp.txt","w");
    remove("temp.txt");
    fclose(fp2);
}


int OfficeOfAcademics::VerifyCredentials(char ldapinp[],char passinp[])
{
    FILE *fp = fopen(LDAPPath,"r");
    if(fp==NULL) 
    {
        std::cout << "Error opening the file\n" ;
        exit(1);
    }
    char ldap[40];
    char pass[40]; 
    while(!(feof(fp)))
    {
        char buffer[100];
        fscanf(fp,"%[^\n]s",buffer);
        fgetc(fp);
        sscanf(buffer,"%s %s",ldap,pass);
        if (strcmp(ldap, ldapinp)==0)
        {
            if(!strcmp(pass, passinp)) // check password hash
            {
                return(1);
            }
            else
            {
                return(0);
            }
        }
    }
    return 0;
}