#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define AdminUser "admin"
#define AdminPass "admin"

//global variable
const char* table[3] = {"patientdetail", "doctordetail", "authentication"};

//Function to check patient login
bool PatientLogin();
 
//Function to check Admin login
bool AdminLogin();//completed

//function for admin menu
void AdminMenu(sqlite3 *db);

//function for patient menu
void PatientMenu();

//function to manage pharmacy 
void PharmacyManage();

//function to manage bills
void BillManage();

//function to manage patient details
void PatientDoctorManage(sqlite3 *db, const char *identify);//done

//function to generate report
void GenerateReport();

//function to add new entry
void Add(sqlite3 *db, const char *identify);//done

//function to update info
void Update(sqlite3 *db, const char *identify);//done

//function to delete
void Delete(sqlite3 *db, const char *identify);//done

//function to search
void Search(sqlite3 *db, const char *identify);//done

//function to generate reports as pdf
void GeneratePdf();

//function to create table
void CreateTable(sqlite3 *db);//ongoing

//function to execute sql
void ExecuteSql(sqlite3 *db, const char *sql);//done

//function to call back
int callback(void *data, int no_fields, char **field_values, char **field_name);//done

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
        if(true/*AdminLogin()*/)
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

    user_pass = "CREATE TABLE IF NOT EXISTS authentication("
                "username1 TEXT NOT NULL,"
                "username2 TEXT NOT NULL,"
                "password TEXT DEFAULT 'user@123');";
    

    ExecuteSql(db, patient_table);
    ExecuteSql(db, doctor_table);
    ExecuteSql(db, user_pass);
}

void ExecuteSql(sqlite3 *db, const char *sql)
{
    char *ErrMsg = NULL;
    int rc;
    //sqlite3_exec(sqlite3 *, const char *sql, int (*callback), void *, char **errmsg);
    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
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
        PatientDoctorManage(db, "patient");
        break;

    case 2:
        PatientDoctorManage(db, "doctor");
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

void PatientDoctorManage(sqlite3 *db, const char *identify)
{
    int choice;
    // char *identify = "patient";
    clear();
    printf("Choose what do you want to do?\n");
    printf("1.Add new\n2.Update info\n3.Delete record\n4.Get specific record\n5.Return Previoud Page\n6.exit\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        Add(db, identify);
        break;

    case 2:
        Update(db, identify);//incomplete
        break;

    case 3:
        Delete(db, identify);
        break;
    
    case 4:
        Search(db, identify);
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

void Search(sqlite3 *db, const char *identify)
{
    char sql[500], username[50], *selected_table;

    getchar();
    printf("username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    if(strcmp(identify, "patient") == 0)
    {
        strcpy(selected_table, table[0]);
    }
    else if(strcmp(identify, "doctor") == 0)
    {
        strcpy(selected_table, table[1]);
    }  
    sprintf(sql, "SELECT * FROM %s WHERE phone = '%s' OR email = '%s';",table[0], username, username);
    ExecuteSql(db, sql);
}

void Update(sqlite3 *db, const char *identify)
{
    int more, age, experience;
    char username[50], name[50], phone[20], email[30], address[50], bloodgrp[10], gender[10], specialization[50], sql[500], sqla[100];
    // getchar();
    printf("Enter username(phone or email): ");
    getchar();
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    clear();
    
    printf("---------------Enter new deatil---------------\n");
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

    if(strcmp(identify, "patient") == 0)
    {
        printf("address: ");
        fgets(address, sizeof(address), stdin);
        address[strcspn(address, "\n")] = '\0';

        printf("bloodgrp: ");
        fgets(bloodgrp, sizeof(bloodgrp), stdin);
        bloodgrp[strcspn(bloodgrp, "\n")] = '\0';

        sprintf(sql, "UPDATE patientdetail SET name = '%s', age = %d, bloodgrp = '%s', gender = '%s', phone = '%s', email = '%s', address = '%s' WHERE  phone = '%s' OR email = '%s';", name, age, bloodgrp, gender, phone, email, address, username, username);
        ExecuteSql(db, sql);        
    }
    else
    {
        printf("address: ");
        scanf("%d", experience);
        
        printf("specialization: ");
        fgets(specialization, sizeof(specialization), stdin);
        specialization[strcspn(specialization, "\n")] = '\0';
        sprintf(sql, "UPDATE doctordetail SET name = '%s', age = %d, phone = '%s', email = '%s', gender = '%s', experience = '%s', specialization = '%s' WHERE phone = '%s' OR email = '%s';", name, age, phone, email, gender, experience, specialization, username, username);
        ExecuteSql(db, sql);
    }
    sprintf(sqla, "UPDATE authentication SET username1 = '%s', username2 = '%s' WHERE username1 = '%s' OR username2 = '%s';", phone, email, username, username);
    ExecuteSql(db, sqla);
    
}

void Add(sqlite3 *db, const char *identify)
{
    int more, age, experience = 0;
    char name[50], phone[20], email[30], address[50], bloodgrp[10], gender[10], specialization[50], sql[500], sqla[100];
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

    if(strcmp(identify, "patient") == 0)
    {
        printf("address: ");
        fgets(address, sizeof(address), stdin);
        address[strcspn(address, "\n")] = '\0';

        printf("bloodgrp: ");
        fgets(bloodgrp, sizeof(bloodgrp), stdin);
        bloodgrp[strcspn(bloodgrp, "\n")] = '\0';

        sprintf(sql, "INSERT INTO patientdetail (name, age, bloodgrp, gender, phone, email, address) VALUES ('%s', %d, '%s', '%s', '%s', '%s', '%s');",name, age, bloodgrp, gender, phone, email, address);
        ExecuteSql(db, sql);
        
    }
    else
    {
        printf("experience: ");
        scanf("%d", &experience);

        printf("specialization: ");
        fgets(specialization, sizeof(specialization), stdin);
        specialization[strcspn(specialization, "\n")] = '\0';
        sprintf(sql, "INSERT INTO doctordetail(name, age, phone, email, gender, experience, specialization) VALUES ('%s', %d, '%s', '%s', '%s', '%s', '%s');", name, age, phone, email, gender, experience, specialization);
        ExecuteSql(db, sql);;
    }
    sprintf(sqla, "INSERT INTO authentication (username1, username2) VALUES ('%s', '%s');", phone, email);
    ExecuteSql(db, sqla);
    
    
}

void Delete(sqlite3 *db, const char *identify)
{
    int more;
    char username[50], sql[300], sql_[200];
    printf("Enter username(phone or email): ");
    getchar();
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    // clear();

    if(strcmp(identify, "patient") == 0)
    {
        sprintf(sql, "DELETE FROM patientdetail WHERE phone = '%s' OR email = '%s';", username, username);
        ExecuteSql(db, sql);
    }
    else if(strcmp(identify, "doctor") == 0)
    {
        sprintf(sql, "DELETE FROM doctordetail WHERE phone = '%s' OR email = '%s';", username, username);
        ExecuteSql(db, sql);
    }
    sprintf(sql_, "DELETE FROM authentication WHERE username1 = '%s' OR username2 = '%s';", username, username);
    ExecuteSql(db, sql_);
}

int callback(void *data, int no_fields, char **field_values, char **field_name)
{
    int i;
    for(i = 0; i < no_fields; i++)
    {
        printf("%s: %s\n", field_name[i], field_values[i]?field_values[i]:NULL);
    }
    return 0;
}

void clear()
{
    system("clear");
}