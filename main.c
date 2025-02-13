#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>



//Function to check patient login
void PatientLogin();

//Fucntion to check doctor login
void DoctorLogin();

//Function to check Admin login
void AdminLogin();

//function to clear creen
void clear();


int main()
{

    char choice;

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


// void clear()
// {
//     system("clear");
// }