#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define AdminUser "admin"
#define AdminPass "admin"

//global variable
const char* table[3] = {"patientdetail", "doctordetail", "authentication"};
const char *services[10] = {"Anesthesiologists", "Cardiologists", "Endocrinologists", "Gastroenterologists", "General surgeons", "Nephrologists", "Neurologists", "Ophthalmologists", "Psychiatrists", "Radiologists"};

//function to check authorize or not for patient and doctor
bool IsAuthorize(sqlite3 *db, const char *username, const char *password);//done

//Function to check patient login
void PatientDoctorLogin(sqlite3 *db, const char *identify);//done
 
//Function to check Admin login
bool AdminLogin();//done

//function for admin menu
void AdminMenu(sqlite3 *db);

//function for patient menu
void PatientMenu(sqlite3 *db,  const char *username);

//function to book appointment
void BookAppointment(sqlite3 *db, int doctor_id, const char *patient_username);

//function to reschedule appointment
void RescheduleAppointment(sqlite3 *db);

//fucntion to cancel appointment
void CancelAppointment(sqlite3 *db);

//function for doctor menu
void DoctorMenu(sqlite3 *db);

//function to manage pharmacy 
void PharmacyManage();

//function to manage bills
void BillManage();

//function to manage patient details
void PatientDoctorManage(sqlite3 *db, const char *identify);//done

//function to generate report
void GenerateReport();

//function to get all servecies
void GetAllServices(sqlite3 *db, const char *patient_usr);

//function to add new entry
void Add(sqlite3 *db, const char *identify);//done

//function to update info
void Update(sqlite3 *db, const char *identify);//done

//function to delete
void Delete(sqlite3 *db, const char *identify);//done

//function to search
void Search(sqlite3 *db, const char *identify);//done

//function to fetch all patients and doctors detials
void GetAll(sqlite3 *db, const char *identify);//done

//function to generate reports as pdf
void GeneratePdf();

//function to create table
void CreateTable(sqlite3 *db);//ongoing

//function to execute sql
void ExecuteSql(sqlite3 *db, const char *sql);//done

//function to call back
int callback(void *data, int no_fields, char **field_values, char **field_name);//done

//function to clear creen
void clear();//done

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
        PatientDoctorLogin(db, "patient");
        break;

    case 2:
        PatientDoctorLogin(db, "doctor");
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
    clear();
    printf("Choose what do you want to do?\n");
    printf("1.Add new\n2.Update info\n3.Delete record\n4.Get specific record\n5.Get detail of all\n6.Return Previoud Page\n7.exit\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        Add(db, identify);
        break;

    case 2:
        Update(db, identify);
        break;

    case 3:
        Delete(db, identify);
        break;
    
    case 4:
        Search(db, identify);
        break;
    
    case 5:
        GetAll(db, identify);
        break;

    case 6:
        AdminMenu(db);
        break;

    case 7:
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
    sprintf(sql, "SELECT * FROM %s WHERE phone = '%s' OR email = '%s';", selected_table, username, username);
    ExecuteSql(db, sql);
}

void GetAll(sqlite3 *db, const char *identify)
{
    char *sql, *selected_talble;

    if(strcmp(identify, "patient") == 0)
    {
        strcpy(selected_talble, table[0]);
    }
    else
    {
        strcpy(selected_talble, table[1]);
    }
    sprintf(sql, "SELECT * FROM %s;", selected_talble);
    ExecuteSql(db, sql);
}

void Update(sqlite3 *db, const char *identify)
{
    int more, age, experience;
    char username[50], name[50], phone[20], email[30], address[50], bloodgrp[10], gender[10], specialization[50], sql[500], sql_[100];
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

        sprintf(sql, "UPDATE %s SET name = '%s', age = %d, bloodgrp = '%s', gender = '%s', phone = '%s', email = '%s', address = '%s' WHERE  phone = '%s' OR email = '%s';",table[0], name, age, bloodgrp, gender, phone, email, address, username, username);
        ExecuteSql(db, sql);        
    }
    else
    {
        printf("address: ");
        scanf("%d", experience);
        
        printf("specialization: ");
        fgets(specialization, sizeof(specialization), stdin);
        specialization[strcspn(specialization, "\n")] = '\0';
        sprintf(sql, "UPDATE %s SET name = '%s', age = %d, phone = '%s', email = '%s', gender = '%s', experience = '%s', specialization = '%s' WHERE phone = '%s' OR email = '%s';",table[1], name, age, phone, email, gender, experience, specialization, username, username);
        ExecuteSql(db, sql);
    }
    sprintf(sql_, "UPDATE %s SET username1 = '%s', username2 = '%s' WHERE username1 = '%s' OR username2 = '%s';",table[2], phone, email, username, username);
    ExecuteSql(db, sql_);
    
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

void PatientDoctorLogin(sqlite3 *db, const char *identify)
{ 
    char username[50], password[50];
    int attempt = 0;
    do
    {
        if(attempt == 5)
        {
            printf("Try agian leter! or contact to reception.\n");
            sqlite3_close(db);
            exit(0);
        }
        printf("username: ");
        scanf("%s", username);
        printf("password: ");
        scanf("%s", password);

        if(IsAuthorize(db, username, password))
        {
            if(strcmp(identify, "patient") == 0)
            {
                PatientMenu(db, username);
            }
            else if(strcmp(identify, "doctor") == 0)
            {
                // DoctorMenu(db);
            }
        }
        else
        {
            printf("Invalid username and password!\n");
        }
        attempt++;

    } while(!IsAuthorize(db, username, password));   
}

bool IsAuthorize(sqlite3 *db, const char *username, const char *password)
{
    sqlite3_stmt *stmt;
    char *sql;
    int rc;

    sprintf(sql, "SELECT * FROM %s;", table[2]);

    // rc --> return code
    // -1 --> calculate the lenget of the string automatic
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statemetn: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        exit(0);
    }
    while((rc = sqlite3_step(stmt) == SQLITE_ROW))
    {
        const char *stored_user1 = (const char *)sqlite3_column_text(stmt, 0);
        const char *stored_user2 = (const char *)sqlite3_column_text(stmt, 1);
        const char *stored_pass = (const char *)sqlite3_column_text(stmt, 2);

        if(strcmp(username, stored_user1) == 0 || strcmp(username, stored_user2))
        {
            if(strcmp(password, stored_pass) == 0)
            {
                if(strcmp(stored_pass, "user@123") == 0)
                {
                    char *update_pass, *confirm_pass;
                    do{
                        printf("Type new password: ");
                        scanf("%s", update_pass);
                        printf("Retype new password: ");
                        scanf("%s", confirm_pass);
                        clear();
                    }while(strcmp(update_pass, confirm_pass) != 0);

                    char *sql_;
                    sprintf(sql_, "UPDATE %s SET password = '%s' WHERE username1 = '%s' OR username2 = '%s';", table[3], confirm_pass, username, username);
                    ExecuteSql(db, sql_);
                }
                return true;
            }
            return false;
        }
    }
    return false;


}

void PatientMenu(sqlite3 *db, const char *username)
{
    int choice, doctor_id;
    char *sql, specialization_[50];
    printf("Please entry your choice:\n");
    printf("1.Get self detail\n2.Get all services with doctor\n3.Doctor Detail\n4.Book Appoinment\n5.Reschedule Appointment\n6.Cancel Appointment\n7.Exit");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        sprintf(sql, "SELECT * FROM %s WHERE phone = '%s' OR email = '%s';", table[0], username, username);
        ExecuteSql(db, sql);
        break;

    case 2:
        GetAllServices(db, username);
        break;

    case 3:
        printf("Enter doctor specialization or username of doctor: ");
        fgets(specialization_, sizeof(specialization_), stdin);
        specialization_[strcspn(specialization_, "\n")] = '\0';
        sprintf(sql, "SELECT * FROM %s WHERE phone = '%s' OR email = '%s' OR specialization = '%s';", table[1], specialization_, specialization_, specialization_);      
        ExecuteSql(db, sql);
        break;

    case 4:
        printf("Enter doctor ID: ");
        scanf("%d", &doctor_id);
        // BookAppointment(db, doctor_id, username);
        break;

    case 5:
        // RescheduleAppointment(db);
        break;

    case 6:
        //CancelAppointment(db);
        break;

    case 7:
        sqlite3_close(db);
        exit(0);
    }
}

void GetAllServices(sqlite3 *db, const char *patient_usr)
{   
    int i, choice, doctor_id;
    char *sql, want;
    printf("We have these services, Please choose any services to get doctor of that particular services\n");
    for(i = 0; i < 10; i++)
    {
        printf("%d.%s\n", i + 1, services[i]);
    }
    scanf("%d", &choice);
    
    sprintf(sql, "SELECT * FROM %s WHERE specialization = '%s';", table[1], services[choice - 1]);
    ExecuteSql(db, sql);

    printf("Want to book Appointment (y/n)?\n");
    scanf("%c", &want);
    if(want == 'y' || want == 'Y')
    {
        printf("Enter Doctor ID: ");
        scanf("%d", &doctor_id);
        // BookAppointment(db, doctor_id, patient_usr);
    }

}

void clear()
{
    system("clear");
}