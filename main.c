#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define AdminUser "admin"
#define AdminPass "admin"

//global variable
sqlite3 *db;
const char* table[5] = {"patientdetail", "doctordetail", "authentication", "appointmentdetail", "medicine"};
const char *services[10] = {"Anesthesiologists", "Cardiologists", "Endocrinologists", "Gastroenterologists", "General surgeons", "Nephrologists", "Neurologists", "Ophthalmologists", "Psychiatrists", "Radiologists"};

//function to check authorize or not for patient and doctor
int IsAuthorize(const char *username, const char *password);//done

//function to add new entry
void Add(const char *identify);//done

//function to update info
void Update(const char *identify);//done

//function to delete
void Delete(const char *identify);//done

//function to search
void Search(const char *identify);//done

//function to fetch all patients and doctors detials
void GetAll(const char *identify);//done

//Function to check patient login
void PatientDoctorLogin(const char *identify);//done
 
//Function to check Admin login
bool AdminLogin();//done

//function to manage patient details
void PatientDoctorManage(const char *identify);//done

//function to execute sql
void ExecuteSql(const char *sql);//done

//function to call back
int callback(void *data, int no_fields, char **field_values, char **field_name);//done

//function to clear creen
void clear();//done

//function to view appointment (this is for doctor)
void ViewAppointment(const char *doctor_username);//done

//function to mark ststus
void MarkAppointmentStatus(const char *username);//done

//function to book appointment
void BookAppointment(const char *doctor_username, const char *patient_username);//done

//function to reschedule appointment
void RescheduleAppointment(const char *patient_username);//done

//fucntion to cancel appointment
void CancelAppointment(const char *patient_username);//done

//function for doctor menu
void DoctorMenu(const char *username);//done

//function to get all servecies
void GetAllServices(const char *patient_usr);//done

//function to add medicine
void AddMedicine();//done

//function to view medicine
void ViewMedicines();//done

//function to remove medicine
void DeleteMedicine();//done

//function to update medicine stock
void UpdateStock();//done

//function to manage pharmacy 
void PharmacyManage();//done

//function for patient menu
void PatientMenu(const char *username);//done

//function to create table
void CreateTable();//done

//function for admin menu
void AdminMenu();//done





//function to manage bills
// void BillManage();

//function to generate report
// void GenerateReport();


//function to generate reports as pdf
// void GeneratePdf();



int main()
{
    
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
            CreateTable();
            clear();
        }
    }
    
    // GetAll("patient");


    switch (choice)
    {
    case 1:
        PatientDoctorLogin("patient");
        break;

    case 2:
        PatientDoctorLogin("doctor");
        break;

    case 3:
        if(AdminLogin())
        {
            AdminMenu();
        }
        else
        {   
            sqlite3_close(db);
            exit(0);
        }
        break;

    case 4:
        sqlite3_close(db);
        exit(0);
        break;
    }
    

    return 0;
}

void CreateTable()
{
    const char *patient_table, *doctor_table, *appointment_table, *user_pass, *medicine;
    
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

    appointment_table = "CREATE TABLE IF NOT EXISTS appointmentdetail("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "patient_username TEXT NOT NULL,"
                    "doctor_username TEXT NOT NULL,"
                    "appointment_date TEXT NOT NULL,"
                    "appointment_time TEXT NOT NULL,"
                    "status TEXT DEFAULT 'scheduled',"
                    "notes TEXT);";

    user_pass = "CREATE TABLE IF NOT EXISTS authentication("
                "username1 TEXT NOT NULL,"
                "username2 TEXT NOT NULL,"
                "password TEXT DEFAULT 'user@123');";

    medicine = "CREATE TABLE IF NOT EXISTS medicine("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL,"
                "quantity INTEGER NOT NULL,"
                "price REAL NOT NULL);";
    

    ExecuteSql(patient_table);
    ExecuteSql(doctor_table);
    ExecuteSql(user_pass);
    ExecuteSql(appointment_table);
}

void ExecuteSql(const char *sql)
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

void AdminMenu()
{
    int choice;
    
    clear();
    printf("---------------Welcome Cheif---------------\n");
    printf("What do you want to do?\n");
    printf("1.Manage Patient\n2.Manage Doctor\n3.Manage Pharmacy\n4.exit\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        PatientDoctorManage("patient");
        break;

    case 2:
        PatientDoctorManage("doctor");
        break;

    case 3:
        PharmacyManage();
        break;

    case 4:
        sqlite3_close(db);
        exit(0);
        break;
    }
}

void PatientDoctorManage(const char *identify)
{
    int choice;
    clear();
    printf("Choose what do you want to do?\n");
    printf("1.Add new\n2.Update info\n3.Delete record\n4.Get specific record\n5.Get detail of all\n6.Return Previoud Page\n7.exit\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        Add(identify);
        break;

    case 2:
        Update(identify);
        break;

    case 3:
        Delete(identify);
        break;
    
    case 4:
        Search(identify);
        break;
    
    case 5:
        GetAll(identify);
        break;

    case 6:
        AdminMenu();
        break;

    case 7:
        sqlite3_close(db);
        exit(0);
        break;
    }

}

void Search(const char *identify)
{
    char sql[500], username[50], *selected_table;

    getchar();
    printf("username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    if(strlen(username) == 0)
    {
        printf("Invalid!\n");
        Search(identify);
    }
    if(strcmp(identify, "patient") == 0)
    {
        strcpy(selected_table, table[0]);
    }
    else if(strcmp(identify, "doctor") == 0)
    {
        strcpy(selected_table, table[1]);
    }  
    sprintf(sql, "SELECT * FROM %s WHERE phone = '%s' OR email = '%s';", selected_table, username, username);
    ExecuteSql(sql);
    printf("Hit enter!\n");
    getchar();
    PatientDoctorManage(identify);
}

void GetAll(const char *identify)
{
    char sql[100], selected_talble[50];

    if(strcmp(identify, "patient") == 0)
    {
        strcpy(selected_talble, table[0]);
    }
    else
    {
        strcpy(selected_talble, table[1]);
    }
    sprintf(sql, "SELECT * FROM %s;", selected_talble);
    ExecuteSql(sql);
}

void Update(const char *identify)
{
    int more, age, experience, count = 0;
    char username[50], name[50], phone[20], email[30], address[50], bloodgrp[10], gender[10], specialization[50], sql[500], sql_[100];
    while(true)
    {
        if(count > 0)
        {
            printf("\nHit enter to exit\n");
        }
        printf("Enter username(phone or email): ");
        getchar();
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';
        if(strlen(username) == 0 && count > 0)
        {
            PatientDoctorManage(identify);
        }
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
        if(strlen(name) == 0 || strlen(phone) == 0)
        {
            clear();
            printf("Invalid!");
            Update(identify);
        }
        if(strcmp(identify, "patient") == 0)
        {
            printf("address: ");
            fgets(address, sizeof(address), stdin);
            address[strcspn(address, "\n")] = '\0';

            printf("bloodgrp: ");
            fgets(bloodgrp, sizeof(bloodgrp), stdin);
            bloodgrp[strcspn(bloodgrp, "\n")] = '\0';

            sprintf(sql, "UPDATE %s SET name = '%s', age = %d, bloodgrp = '%s', gender = '%s', phone = '%s', email = '%s', address = '%s' WHERE  phone = '%s' OR email = '%s';",table[0], name, age, bloodgrp, gender, phone, email, address, username, username);
            ExecuteSql(sql);    
        }
        else
        {
            printf("address: ");
            scanf("%d", experience);
            
            printf("specialization: ");
            fgets(specialization, sizeof(specialization), stdin);
            specialization[strcspn(specialization, "\n")] = '\0';
            sprintf(sql, "UPDATE %s SET name = '%s', age = %d, phone = '%s', email = '%s', gender = '%s', experience = '%s', specialization = '%s' WHERE phone = '%s' OR email = '%s';",table[1], name, age, phone, email, gender, experience, specialization, username, username);
            ExecuteSql(sql);
        }
        sprintf(sql_, "UPDATE %s SET username1 = '%s', username2 = '%s' WHERE username1 = '%s' OR username2 = '%s';",table[2], phone, email, username, username);
        ExecuteSql(sql_);
    }
    
}

void Add(const char *identify)
{
    int more, age, experience, count = 0;
    char name[50], phone[20], email[30], address[50], bloodgrp[10], gender[10], specialization[50], sql[500], sqla[100];
    getchar();
    do
    {
    
        
        if(count > 0)
        {
            printf("\nHit enter to exit!\n");
        }
        printf("name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        if(strlen(name) == 0 && count > 0)
        {
            PatientDoctorManage(identify);
        }
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
        if(strlen(name) < 1 && strlen(phone) <1)
        {
            clear();
            printf("Invalid!\n");
            Add(identify);
        }
        if(strcmp(identify, "patient") == 0)
        {
            printf("address: ");
            fgets(address, sizeof(address), stdin);
            address[strcspn(address, "\n")] = '\0';

            printf("bloodgrp: ");
            fgets(bloodgrp, sizeof(bloodgrp), stdin);
            bloodgrp[strcspn(bloodgrp, "\n")] = '\0';

            sprintf(sql, "INSERT INTO %s (name, age, bloodgrp, gender, phone, email, address) VALUES ('%s', %d, '%s', '%s', '%s', '%s', '%s');", table[0], name, age, bloodgrp, gender, phone, email, address);
            ExecuteSql(sql);
            
        }
        else
        {
            printf("experience: ");
            scanf("%d", &experience);
            getchar();

            printf("specialization: ");
            fgets(specialization, sizeof(specialization), stdin);
            specialization[strcspn(specialization, "\n")] = 0;
            sprintf(sql, "INSERT INTO doctordetail(name, age, phone, email, gender, experience, specialization) VALUES ('%s', %d, '%s', '%s', '%s', %d, '%s');", name, age, phone, email, gender, experience, specialization);
            ExecuteSql(sql);;
            printf("Added successfully!\n");
        }
        sprintf(sqla, "INSERT INTO authentication (username1, username2) VALUES ('%s', '%s');", phone, email);
        ExecuteSql(sqla);
        count++;
        printf("Added successfully!\n");
    }while(true);
    
    
}

void Delete(const char *identify)
{
    int count = 0;
    char username[50], sql[300], sql_[200], selected_table[20];
    while(true)
    {
        if(count > 0)
        {
            printf("Hit enter to exit!\n");
        }
        printf("Enter username(phone or email): ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        if(strlen(username) == 0 && count > 0)
        {
            PatientDoctorManage(identify);
        }
        else if(strlen(username) == 0)
        {
            printf("Invalid!\n");
            Delete(identify);
        }
        if(strcmp(identify, "patient") == 0)
        {
            strcpy(selected_table, table[0]);
        }
        else if(strcmp(identify, "doctor") == 0)
        {
            strcpy(selected_table, table[1]);
        }
        printf("SQL querry: %s\n", sql);
        sprintf(sql, "DELETE FROM %s WHERE phone = '%s' OR email = '%s';", selected_table, username, username);
        ExecuteSql(sql);
        sprintf(sql_, "DELETE FROM %s WHERE username1 = '%s' OR username2 = '%s';", table[2], username, username);
        ExecuteSql(sql_);
        printf("Deleted successfully!\n");
        count++;
    }
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

void PatientDoctorLogin(const char *identify)
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
        clear();
        printf("username: ");
        scanf("%49s", username);
        printf("password: ");
        scanf("%49s", password);

        if(IsAuthorize(username, password))
        {
            if(strcmp(identify, "patient") == 0)
            {
                clear();
                PatientMenu(username);
            }
            else if(strcmp(identify, "doctor") == 0)
            {
                DoctorMenu(username);
            }
        }
        else
        {
            clear();
            printf("Invalid username and password!\n");
        }
        attempt++;

    } while(!IsAuthorize(username, password));   
}

int IsAuthorize(const char *username, const char *password)
{
    sqlite3_stmt *stmt;
    char sql[256], sql_[256], update_pass[256], confirm_pass[256];
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
                    // char *update_pass, *confirm_pass;
                    do{
                        clear();
                        printf("At first you've to change password!\n");
                        printf("Type new password: ");
                        scanf("%s", update_pass);
                        printf("Retype new password: ");
                        scanf("%s", confirm_pass);
                        clear();
                    }while(strcmp(update_pass, confirm_pass) != 0);

                    // char *sql_;
                    sprintf(sql_, "UPDATE %s SET password = '%s' WHERE username1 = '%s' OR username2 = '%s';", table[2], confirm_pass, username, username);
                    ExecuteSql(sql_);
                    IsAuthorize(username, password);
                }
                return 1;
            }
            return 0;
        }
    }
    return 0;


}

void PatientMenu(const char *username)
{
    int choice;
    char *sql, specialization_[50], doctor_username[20];
    printf("Please entry your choice:\n");
    printf("1.Get self detail\n2.Get all services with doctor\n3.Doctor Detail\n4.Book Appoinment\n5.Reschedule Appointment\n6.Cancel Appointment\n7.Exit");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        sprintf(sql, "SELECT * FROM %s WHERE phone = '%s' OR email = '%s';", table[0], username, username);
        ExecuteSql(sql);
        break;

    case 2:
        GetAllServices(username);
        break;

    case 3:
        printf("Enter doctor specialization or username of doctor: ");
        fgets(specialization_, sizeof(specialization_), stdin);
        specialization_[strcspn(specialization_, "\n")] = '\0';
        sprintf(sql, "SELECT * FROM %s WHERE phone = '%s' OR email = '%s' OR specialization = '%s';", table[1], specialization_, specialization_, specialization_);      
        ExecuteSql(sql);
        break;

    case 4:
        printf("Enter doctor username(phone): ");
        scanf("%20s", &doctor_username);
        BookAppointment(doctor_username, username);
        break;

    case 5:
        RescheduleAppointment(username);
        break;

    case 6:
        CancelAppointment(username);
        break;

    case 7:
        sqlite3_close(db);
        exit(0);
    }
}

void GetAllServices(const char *patient_usr)
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
    ExecuteSql(sql);

    printf("Want to book Appointment (y/n)?\n");
    scanf("%c", &want);
    if(want == 'y' || want == 'Y')
    {
        printf("Enter Doctor ID: ");
        scanf("%d", &doctor_id);
        // BookAppointment(db, doctor_id, patient_usr);
    }

}

void BookAppointment(const char *doctor_username, const char *patient_username)
{
    char date[20], time[20], status[20], notes[100], sql[300], *errMsg;

    printf("Enter Date(YYYY-MM-DD): ");
    scanf("%20s", &date);
    date[strcspn(date, "\n")] = 0;

    printf("Enter Time(HH:MM): ");
    scanf("%20s", &time);
    time[strcspn(time, "\n")] = 0;

    sprintf("sql", "INSERT INTO appointmentdetail (patient_username, doctor_username, appointment_date, appointment_time) VALUES ('%s', '%s', '%s', '%s');", patient_username, doctor_username, date, time);
    ExecuteSql(sql);

    printf("Appointment booked successfully!\n");

}

void MarkAppointmentStatus(const char *username)
{
    char sql[300], note[200];

    printf("Suggestion:\n");
    fgets(sql, sizeof(note), stdin);
    note[strcspn(note, "\n")] = 0;

    sprintf(sql, "UPDATE %s SET status = 'completed', notes = '%s';", table[3], note);
    ExecuteSql(sql);
    DoctorMenu(username);

}

void ViewAppointment(const char *doctor_username)
{
    char sql[300];
    sprintf(sql, "SELECT * FROM appointmentdetail WHERE doctor_username = '%s';", doctor_username);
    ExecuteSql(sql);
    DoctorMenu(doctor_username);
}

void DoctorMenu(const char *username)
{
    int choice;
    printf("1.View Assigned Appointment.\n2.Mark As Completed\n3.Exit");
    scanf("%d", choice);

    do
    {
        switch (choice)
        {
        case 1:
            clear();
            ViewAppointment(username);
            break;
        case 2:
            clear();
            MarkAppointmentStatus(username);
        case 3:
            clear();
            sqlite3_close(db);
        }
    } while (choice > 3);
    
}

void RescheduleAppointment(const char *patient_username)
{
    char sql[256], date[20], time[20];

    printf("Enter new date(YYYY-MM-DD): ");
    scanf("%20s", &date);
    date[strcspn(date, "\n")] = 0;

    printf("Enter new time(HH:MM): ");
    scanf("%20s", &time);
    time[strcspn(time, "\n")] = 0;

    sprintf(sql, "UPDATE %s SET appointment_date = '%s', appointment_time = '%s', status = 'rescheduled';", table[3], date, time);
    ExecuteSql(sql);
    clear();
    PatientMenu(patient_username);
}

void CancelAppointment(const char *patient_username)
{
    char sql[256];

    sprintf(sql, "DELETE FORM %s WHERE patient_username = '%s';", table[3], patient_username);
    ExecuteSql(sql);
    printf("Appointment calcel successfully\n");
    PatientMenu(patient_username);
}

void PharmacyManage()
{
    int choice;
    do {
        printf("\nPharmacy Management System\n");
        printf("1. Add Medicine\n");
        printf("2. View Medicines\n");
        printf("3. Update Stock\n");
        printf("4. Delete Medicine\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                AddMedicine(); 
                break;
            case 2:
                ViewMedicines(); 
                break;
            case 3:
                UpdateStock();
                break;
            case 4:
                DeleteMedicine();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
            printf("Invalid choice!\n");
        }
    } while (choice != 5);
}

void AddMedicine()
{
    char name[50], sql[256];
    int quantity;
    float price;

    printf("Enter medicine name: ");
    scanf("%s", name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    printf("Enter price: ");
    scanf("%f", &price);

    snprintf(sql, sizeof(sql), 
             "INSERT INTO medicine (name, quantity, price) VALUES ('%s', %d, %.2f);", 
             name, quantity, price);

    ExecuteSql(sql);
    printf("Medicine added successfully!\n");
}

void ViewMedicines() {
    sqlite3_stmt *stmt;
    char *sql = "SELECT * FROM medicine;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        printf("Failed to fetch medicines.\n");
        return;
    }

    printf("\nID | Name        | Quantity | Price\n");
    printf("------------------------------------\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%d | %-10s | %d | %.2f\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_int(stmt, 2),
               sqlite3_column_double(stmt, 3));
    }

    sqlite3_finalize(stmt);
}

void UpdateStock() {
    char name[50];
    int quantity;
    char sql[256];

    printf("Enter medicine name: ");
    scanf("%s", name);
    printf("Enter new quantity: ");
    scanf("%d", &quantity);

    snprintf(sql, sizeof(sql), 
             "UPDATE %s SET quantity = %d WHERE name = '%s';", 
             table[4], quantity, name);

    ExecuteSql(sql);
    printf("Stock updated successfully!\n");
}

void DeleteMedicine() {
    char name[50];
    char sql[256];

    printf("Enter medicine name to delete: ");
    scanf("%s", name);

    snprintf(sql, sizeof(sql), 
             "DELETE FROM %s WHERE name = '%s';", 
             table[4], name);

    ExecuteSql(sql);
    printf("Medicine deleted successfully!\n");
}

void clear()
{
    system("clear");
}