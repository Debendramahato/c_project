#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>



//Function to check patient login
void PatientLogin();
//Fucntion to check doctor login
void DoctorLogin();
//Function to check Admin login
void AdminLogin();
//function for doctor menu
void DoctorMenu();
//function for admin menu
void AdminMenu();
//function for patient menu
void PatientMenu();
//function to manage pharmacy 
void PharmacyManagement();
//function to manage bills
void BillManage();
//function to manage doctors detail
void DoctorManage();
//function to manage patient details
void PatientManage();
//function to generate report
void GenerateReport();
//function to add new entry
void Add();
//function to update info
void Update();
//function to delete
void Delete();
//function to search
void Search();
//function to generate reports as pdf
void GeneratePdf();
//function to clear creen
void clear();




int main()
{
    sqlite3 *db;
    char zErrMsg = 0, choice;
    int rc;

    printf("-----------------Who are you?-----------------\n");
    printf("1.Patient\n2.Doctor\n3.Admin\n4.Exit\n");
    fgets(choice, sizeof(choice), stdin);

    switch (choice)
    {
    case '1':
        break;

    case '2':
        break;

    case '3':
        break;

    case '4':
        exit(0);
        break;

    default:
        break;
    }


    return 0;
}


void clear()
{
    system("clear");
}