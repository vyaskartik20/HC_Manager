class Patient
{
    static char currldap[40];
    static int loginmode;
    
    public:
        static void login(int mode);
        static void GetHealthRecord();
        static void EnquireSpecialist();
        static void GetTestResults();
        static void MedSupp();
        static void DisplayOptions();
};
class student : public Patient{};
class faculty : public Patient{};
class staff : public Patient{};