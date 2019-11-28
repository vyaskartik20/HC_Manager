class DoctorsOffice
{
    static int loginmode;
    static int SpecList[7];
    static char specname[7][40];
    public:
        static void PreLoadStuff();
        static void login(int mode);
        static void viewHealthRecord(char ldapinp[]);
        static void addSpecialistRequest(int spec, int loginmode);
        static void viewSpecialistRequest();
        static void addToAppointments(char ldapinp[], char appt[]);
        static void ShowAppointments();
        static int* getSpecList();
        static void updateHealthRecord(char ldapinp[], char details[]);
        static void DisplayOptions();
};

class Doctor: public DoctorsOffice{};
class HCstaff: public DoctorsOffice{};