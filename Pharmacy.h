class Pharmacy
{
    static char currEmployeeID[40];
    public:
        static int checkMedsInPharmacy(char medinp[]);
        static void addMedRequest(char med[], char ldap[]);
        static void showMedRequests();
        static void login();
        static void ShowMedsList();
        static void UpdateMedsList(char med_nameinp[],  int amtinp);
        static void DisplayOptions();
};