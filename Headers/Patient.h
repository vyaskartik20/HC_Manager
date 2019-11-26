// Patients Header File
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DoctorsOffice.h"

#include <string>
#include "Pharmacy.h"
//#include <windows.h>
#include <bits/stdc++.h>
#define AVAILABLE 1
#define STUDENT 1
#define FACULTY 2
#define STAFF 3
#define SUCCESSFUL 1
#define YES 1
#define NO 0
class Patient 
{
    static char currldap[40];
    static int loginmode;
    public:
        static void login(int mode)
        {
            char ldap[40], pass[40];
            std::cout << "Enter LDAP ID: " ;
            std::cin >> ldap;
            std::cout << "Enter Password: " ;
            std::cin >> pass;
            int loginverify = OfficeOfAcademics::VerifyCredentials(ldap, pass);
            if(loginverify==SUCCESSFUL)
            {
                std::cout << ("You have been successfully logged in\n");
                strcpy(currldap, ldap);
                Patient::loginmode = mode;
                DisplayOptions();
            }
            else
            {
                std::cout << ("Enter credentials again\n");
                login(mode);
            }
        }
        static void GetHealthRecord()
        {
            std::cout << "The record below shows your past visits to the health center::\n";
            DoctorsOffice::viewHealthRecord(currldap);
        }
        
        static void EnquireSpecialist()
        {
            int repeat = YES;
            do
            {
                std::cout << "List of Specialists::\n";
                std::cout << " 1:Gastroenterologist\n";
                std::cout << " 2:Gynaecologist\n";
                std::cout << " 3:Paediatrician\n";
                std::cout << " 4:ENT Specialist\n";
                std::cout << " 5:Dermatologist\n";
                std::cout << " 6:Orthopaedic Specialist\n";
                std::cout << " 7:Ophthalmologist\n";
                std::cout << "Please enter the corresponding no. for the specialist which you wish to enquire about: ";
                int spec;
                std::cin >> spec;
                int *speclist;
                speclist = DoctorsOffice::getSpecList();
                
                char specname[7][40] = {"Gastroenterologist",
                "Gynaecologist",
                "Paediatrician",
                "ENT Specialist",
                "Dermatologist",
                "Orthopaedic Specialist",
                "Ophthalmologist"};
                
                if(speclist[spec-1]==1)
                {
                    std::cout << specname[spec-1] << " will be available this weekend.\n";
                    if(loginmode==FACULTY) // if faculty
                    {
                        std::cout << "Do you wish to book an appointment? (Yes/No): ";
                        std::string response;
                        std::cin >> response;
                        std::transform(response.begin(), response.end(), response.begin(), ::tolower);
                        if(response.std::string::compare("yes")==0)
                        {
                            char appt[100];
                            std::cout << "Please enter the date & time: " ;
                            scanf("%[^\n]s",appt);
                            DoctorsOffice::addToAppointments(currldap,appt);
                            std::cout << "Your appointment has been booked.\n" ;
                        }
                    }
                }
                else
                {
                    std::cout << specname[spec-1] << " won't be available this weekend.\n" ;
                    std::cout << "Do you wish to put in a request for the above specialist? (Yes/No): " ;
                    std::string response;
                    std::cin >> response;
                    std::transform(response.begin(), response.end(), response.begin(), ::tolower);
                    if(response.std::string::compare("yes")==0)
                    {
                        DoctorsOffice::addSpecialistRequest(spec,loginmode);       // n - mode whether faculty or student is requesting.
                        std::cout << "The request was successfully registered!\n" ;
                    }   
                    
                }
                std::cout << "Do you wish to perform another enquiry? (yes/no): ";
                std::string response;
                std::cin >> response;
                std::transform(response.begin(), response.end(), response.begin(), ::tolower);
                if(response.std::string::compare("yes")==0)
                {
                    repeat = YES;
                }
                else repeat = NO;
            } while(repeat == YES);
        }

        static void GetTestResults()
        {
            std::cout << "Enter the e-mail to which you wish to get your report mailed: \n";
            char email[60];
            scanf("%s",email);
            // int len1 = strlen(email);
            // email[len1] = '\\';
            // email[len1+1] = '\0';
            // const char* command = "curl smtp://smtp.gmail.com:587 -v --mail-from \"gargdevin@gmail.com\" --mail-rcpt \email --ssl -u gargdevin@gmail.com:Dev@G307561 -T \"\" -k --anyauth";
            // WinExec(command, SW_HIDE);
        }

        static void MedSupp()
        {
        	while(1)
        	{
        		std::cout << "Enter the medicine you wish to enquire about:\n";
            	char med[40];
                scanf("%s",med);
                int check = pharmacy::checkMedsInPharmacy(med);
				// check availability in pharmacy
				if(check==AVAILABLE)
					std::cout << "That medicine/supplement is currently available at the Health Center.\n";
				else 
				{
					std::cout << "That medicine/supplement isn't currently available at the Health Center.\n";
					std::cout << "Would you like to put in a request for the same? (Yes/No): ";
					std::string response;
					std::cin >> response;
					std::transform(response.begin(), response.end(), response.begin(), ::tolower);
					if(response.std::string::compare("yes")==0)
                    {
                    	// send the medicine's request
                        pharmacy::addMedRequest(med,currldap);
                    	std::cout << "Your request has been successfully registered.\n";
                    }
				}  
                std::cout << "Do you wish to enquire about any other medicines/supplements? (Yes/No): ";
                std::string response; int flag;
                std::cin >> response;
                std::transform(response.begin(), response.end(), response.begin(), ::tolower);
                if(response.std::string::compare("yes")==0)
                {
                    flag = 1;
                }
                else flag = 0;
                if(flag==0)
                break;
            }
        }

        // static void MedCert()
        // {
            

        // }

        static void DisplayOptions()
        {
            int flag = 0;
            do
            {            	
                int flag2 = 0;
		        std::cout << " 1:Get your health record\n";
		        std::cout << " 2:Enquire/Book Appointment for Specialist\n";
		        std::cout << " 3:Get Test Results\n";
		        std::cout << " 4:Request Medical Supplements\n";
		        //std::cout << " 5:Get Medical Certificate\n";
		        std::cout << "Enter your choice (The corresponding number): ";
		        int choice;
		        std::cin >> choice;

		        switch(choice)
		        {
		            case 1:         //getting health record
		            {   
		                GetHealthRecord();
		                break;
		            }
		            case 2:         // enquiring regarding specialist
		            {
		                EnquireSpecialist();
		                break;
		            }
		            case 3:         // getting test results
		            {
		                GetTestResults();
		                break;
		            }            
		            case 4:         // requeesting otc medicines
		            {
		                MedSupp();
		                break;
		            }
		            // case 5:         // getting medical certificate
		            // {
		            //     MedCert();
		            //     break;
		            // }
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
class student : public Patient
{
    //friend void Patient::login();
};

class faculty : public Patient
{
	//friend void Patient::login();
};
class staff : public Patient
{
	//friend void Patient::login();
};

char Patient::currldap[40] ={0};
int  Patient::loginmode = 0;