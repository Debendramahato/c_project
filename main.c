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
//function to create table
void CreateTable(sqlite3 *db);
//function to execute sql
void ExecuteSql(sqlite3 *db, const char *sql);
//function to clear creen
void clear();




int main()
{
    sqlite3 *db;
    char zErrMsg = 0;
    int rc, choice;//rc = return code

    printf("-----------------Who are you?-----------------\n");
    printf("1.Patient\n2.Doctor\n3.Admin\n4.Exit\n");
    scanf("%d", &choice);

    rc = sqlite3_open("HMS.db", &db);
    if(rc != SQLITE_OK)
    {
        printf("Failed to open databese err: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    else
    {
        CreateTable(db);
    }


    switch (choice)
    {
    case 1:
        break;

    case 2:
        break;

    case 3:
        break;

    case 4:
        exit(0);
        break;
    }


    return 0;
}



void CreateTable(sqlite3 *db)
{
    char *patient_table, *doctor_table;
    
    patient_table = "CREATE TABLE patientdetail("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name TEXT NOT NULL,"
                    "age INTEGET NOT NULL,"
                    "bloodgrp TEXT NOT NULL,"
                    "gender TEXT NOT NULL,"
                    "phone TEXT NOT NULL,"
                    "email TEXT,"
                    "address TEXT);";
    
    doctor_table = "CREATE TABLE patientdetail("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name TEXT NOT NULL,"
                    "age INTEGET NOT NULL,"
                    "bloodgrp TEXT NOT NULL,"
                    "gender TEXT NOT NULL,"
                    "phone TEXT NOT NULL,"
                    "email TEXT,"
                    "address TEXT);";

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

void clear()
{
    system("clear");
}