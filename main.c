#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define AdminUser "admin"
#define AdminPass "admin"

//Function to check patient login
bool PatientLogin();
//Fucntion to check doctor login
bool DoctorLogin();
//Function to check Admin login
bool AdminLogin();//completed
//function for doctor menu
void DoctorMenu();
//function for admin menu
void AdminMenu(sqlite3 *db);
//function for patient menu
void PatientMenu();
//function to manage pharmacy 
void PharmacyManage();
//function to manage bills
void BillManage();
//function to manage doctors detail
void DoctorManage();
//function to manage patient details
void PatientManage(sqlite3 *db);
//function to generate report
void GenerateReport();
//function to add new entry
void Add(sqlite3 *db, const char identify);
//function to update info
void Update(sqlite3 *db, const char identify);
//function to delete
void Delete(sqlite3 *db, const char identify);
//function to search
void Search(sqlite3 *db, const char identify);
//function to generate reports as pdf
void GeneratePdf();
//function to create table
void CreateTable(sqlite3 *db);
//function to execute sql
void ExecuteSql(sqlite3 *db, const char *sql);
//function to clear creen
void clear();




int main()
{
    sqlite3 *db;
    // char zErrMsg = 0;
    int rc, choice;//rc = return code

    printf("-----------------Who are you?-----------------\n");
    printf("1.Patient\n2.Doctor\n3.Admin\n4.Exit\n");
    scanf("%d", &choice);

    rc = sqlite3_open("HMS.db", &db);
    if(choice < 4)
    {
        if(rc != SQLITE_OK)
        {
            printf("Failed to open databese err: %s\n", sqlite3_errmsg(db));
            return 1;
        }
        else
        {
            CreateTable(db);
            clear();
        }
    }


    switch (choice)
    {
    case 1:
        // PatientLogin();
        break;

    case 2:
        // DoctorLogin();
        break;

    case 3:
        if(AdminLogin())
        {
            AdminMenu(db);
        }
        else
        {
            exit(0);
        }
        break;

    case 4:
        exit(0);
        break;
    }


    return 0;
}



void CreateTable(sqlite3 *db)
{
    const char *patient_table, *doctor_table, *user_pass;
    
    patient_table = "CREATE TABLE IF NOT EXISTS patientdetail("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name TEXT NOT NULL,"
                    "age INTEGER NOT NULL,"
                    "bloodgrp TEXT NOT NULL,"
                    "gender TEXT NOT NULL,"
                    "phone TEXT NOT NULL,"
                    "email TEXT,"
                    "address TEXT);";
    
    doctor_table = "CREATE TABLE IF NOT EXISTS doctordetail("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name TEXT NOT NULL,"
                    "age INTEGER NOT NULL,"
                    "phone TEXT NOT NULL,"
                    "email TEXT,"
                    "gender TEXT NOT NULL,"
                    "experience INTEGER,"
                    "specialization TEXT);";

    user_pass = "CREATE TABLE IF NOT EXISTS AUTHENTICATION("
                "username TEXT NOT NULL,"
                "password TEXT DEFAULT 'user@123');";
    

    ExecuteSql(db, patient_table);
    ExecuteSql(db, doctor_table);
}

void ExecuteSql(sqlite3 *db, const char *sql)
{
    char *ErrMsg = NULL;
    int rc;
    //sqlite3_exec(sqlite3 *, const char *sql, int (*callback), void *, char **errmsg);
    rc = sqlite3_exec(db, sql, 0, 0, &ErrMsg);
    if(rc != SQLITE_OK)
    {
        printf("SQL err: %s\n", ErrMsg);
        sqlite3_free(ErrMsg);
    }
}

bool AdminLogin()
{
    char username[50], password[50];
    int attempt = 0;
    do
    {
        if(attempt == 5)
        {
            printf("Try agian leter!");
            return false;
        }
        printf("username: ");
        scanf("%s", username);
        printf("password: ");
        scanf("%s", password);
        if(strcmp(username, AdminUser) != 0)
        {
            if(strcmp(password, AdminPass) != 0)
            {
                printf("\bWrong username and password!\n");
            }
            else
            {
                printf("/bWrong username\n");
            }
        }
        else
        {
            if(strcmp(username, AdminPass) != 0)
            {
                printf("\bWrong password!\n");
            }
        }
        
        attempt++;

    } while(strcmp(username, AdminUser) != 0 || strcmp(password, AdminPass) != 0);
    return true;
}

void AdminMenu(sqlite3 *db)
{
    int choice;
    
    printf("---------------Welcome Cheif---------------\n");
    printf("What do you want to do?\n");
    printf("1.Manage Patient\n2.Manage Doctor\n3.Manage Pharmacy\n4.exit\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        PatientManage(db);
        break;

    case 2:
        // DoctorManage();
        break;

    case 3:
        // PharmacyManage();
        break;

    case 4:
        sqlite3_close(db);
        exit(0);
        break;
    }
}

void PatientManage(sqlite3 *db)
{
    int choice;
    char identify = 'p';
    clear();
    printf("Choose what do you want to do?\n");
    printf("1.Add new patient\n2.Update patient info\n3.Delete Paitent Record\n4.Get Specific Patient\n5.Return Previoud Page\n6.exit\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        Add(db, identify);
        break;

    case 2:
        // Update(db, identify);
        break;

    case 3:
        // Delete(db, identify);
        break;
    
    case 4:
        // Search(db, identify);
        break;

    case 5:
        AdminMenu(db);
        break;

    case 6:
        sqlite3_close(db);
        exit(0);
        break;
    }

}

void Add(sqlite3 *db, const char identify)
{
    int more, age, experience;
    char name[50], phone[15], email[30], address[50], bloodgrp[10], gender[10], specialization[50], sql[500];
    getchar();
    printf("name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("age: ");
    scanf("%d", &age);
    getchar();
    printf("phone: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = '\0';

    printf("email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';
    
    printf("gender: ");
    fgets(gender, sizeof(gender), stdin);
    gender[strcspn(gender, "\n")] = '\0';

    if(identify == 'p')
    {
        printf("address: ");
        fgets(address, sizeof(address), stdin);
        address[strcspn(address, "\n")] = '\0';

        printf("bloodgrp: ");
        fgets(bloodgrp, sizeof(bloodgrp), stdin);
        bloodgrp[strcspn(bloodgrp, "\n")] = '\0';

        sprintf(sql, "INSERT INTO patientdetail (name, age, bloodgrp, gender, phone, email, address) VALUES ('%s', '%d', '%s', '%s', '%s', '%s', '%s');",name, age, bloodgrp, gender, phone, email, address);
        ExecuteSql(db, sql);

    }
    else
    {
        printf("address: ");
        scanf("%d", experience);

        printf("specialization: ");
        fgets(specialization, sizeof(specialization), stdin);
        specialization[strcspn(specialization, "\n")] = '\0';
    }

    
}

void clear()
{
    system("clear");
}