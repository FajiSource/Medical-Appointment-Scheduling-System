#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
#include <string>
#include <iomanip>
#define SIZE 100
using namespace std;

struct Patient
{
    string name;
    int age;
    string address;
    int gender;
};
struct Schedule
{
    Patient patient;
    bool isFinished;
    string date;
};

class Schedules
{
public:
    int size = 0;
    Schedule schedules[SIZE];
    bool isEmpty()
    {
        return size <= 0;
    }
    void add(Schedule sched)
    {
        schedules[size++] = sched;
    }
    void delete_schedule(int index)
    {
        for (int i = index - 1; i < size; i++)
        {
            schedules[i] = schedules[i + 1];
        }
        size--;
    }
    bool is_date_available(string date)
    {
        for (int i = 0; i < size; i++)
        {
            if (schedules[i].date == date)
                return false;
        }
        return true;
    }
};

int main_menu();
void display_schedules(Schedule scheds[]);
void display_filtered_schedules(int size, Schedule scheds[]);
void add_schedule();
void delete_schedule();
void search_schedule();
bool check_date();
void line();
void header(string);
void clear_screen();
void display_error(string error);
void selected_schedule(int index);

Schedules schedules;

int main()
{
    int choice;
loop:
    choice = main_menu();
    switch (choice)
    {
    case 1:
        display_schedules(schedules.schedules);
        goto loop;
    case 2:
        add_schedule();
        goto loop;
    case 3:
        search_schedule();
        goto loop;
    case 4:
        clear_screen();
        cout << "Are you sure want to exit [0]NO | [1]YES? " << endl;
        cout << ">> ";
        cin >> choice;
        if (choice == 0)
            goto loop;
        else if (choice == 1)
        {
            cout << "Program Exit." << endl;
            break;
        }
        else
        {
            display_error("Invalid Choice!");
            goto loop;
        }
    default:
        display_error("Invalid Choice!");
        clear_screen();
        goto loop;
    }
    return 0;
}

void line() { cout << "=======================================================" << endl
                   << endl; };
void header(string label)
{
    cout << "=======================================================" << endl;
    cout << "\tMEDICAL APPOINTMENT SCHEDULING SYSTEM" << endl;
    cout << "=======================================================" << endl;
    cout << ": " << label << endl
         << endl;
}
int main_menu()
{
    clear_screen();
    int choice;
    header("Home");
    cout << "1. View Schedules" << endl;
    cout << "2. Add New Schedule" << endl;
    cout << "3. Search Schedule" << endl;
    cout << "4. Exit" << endl;
    cout << ">> ";
    cin >> choice;
    return choice;
}
void display_schedules(Schedule scheds[])
{
    clear_screen();
    int choice;
    header("Schedules");
    Schedule filtered_scheds[SIZE];
    int filtered_size = 0;
    if (!schedules.isEmpty())
    {
        cout << setw(6) << left << "NO."
             << setw(30) << left << "NAME"
             << setw(7) << left << "AGE"
             << setw(12) << left << "GENDER"
             << setw(20) << left << "ADDRESS"
             << setw(18) << "DATE" << endl
             << endl;
        for (int i = 0; i < schedules.size; i++)
        {
            cout << setw(6) << left << i + 1
                 << setw(30) << left << scheds[i].patient.name
                 << setw(7) << left << scheds[i].patient.age
                 << setw(12) << left << (scheds[i].patient.gender == 0 ? "MALE" : "FEMALE")
                 << setw(20) << left << scheds[i].patient.address
                 << setw(18) << scheds[i].date << endl;
        }
    }
    else
    {
        cout << "No Schedules." << endl;
    }
    cout << endl;
    cout << "*******************" << endl;
    cout << "1. Select Schedule" << endl;
    cout << "2. Filter" << endl;
    cout << "3. Back" << endl;
    cout << ">> ";
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
    case 1:
        cout << "*******************" << endl;
        cout << "Enter Schedule Number: ";
        cin >> choice;
        if (choice > schedules.size || choice <= 0)
        {
            display_error("Invalid Schedule Number!");
            display_schedules(scheds);
        }
        selected_schedule(choice);
        break;
    case 2:
        cout << "*******************" << endl;
        cout << "1. Filter by Date" << endl;
        cout << "2. Filter By Gender" << endl;
        cout << "3. Filter By Age" << endl;
        cout << "4. Back" << endl;
        cout << ">> ";
        cin >> choice;
        cin.ignore();
        if (choice > 4 || choice <= 0)
        {
            display_error("Invalid Filter Choice!");
            display_schedules(scheds);
        }
        if (choice == 1)
        {
            int day, month, year;
            cout << "*******************" << endl;
            cout << "Filter by Date" << endl;
            cout << "Enter Date [mm/dd/yyyy]: ";
            cin >> month >> day >> year;
            string date = to_string(month) + "/" + to_string(day) + "/" + to_string(year);
            for (int i = 0; i < schedules.size; i++)
            {
                if (schedules.schedules[i].date == date)
                {
                    filtered_scheds[filtered_size++] = schedules.schedules[i];
                }
            }
            display_filtered_schedules((filtered_size), filtered_scheds);
            break;
        }
        else if (choice == 2)
        {
            int gender;
            cout << "*******************" << endl;
            cout << "Fildter by Gender" << endl;
            cout << "Enter Gender [0]MALE [1]FEMALE: ";
            cin >> gender;
            for (int i = 0; i < schedules.size; i++)
            {
                if (schedules.schedules[i].patient.gender == gender)
                {
                    filtered_scheds[filtered_size++] = schedules.schedules[i];
                }
            }
            display_filtered_schedules((filtered_size), filtered_scheds);
            break;
        }
        else if (choice == 3)
        {
            int age;
            cout << "*******************" << endl;
            cout << "Fildter by Age" << endl;
            cout << "Enter Age : ";
            cin >> age;
            for (int i = 0; i < schedules.size; i++)
            {
                if (schedules.schedules[i].patient.age == age)
                {
                    filtered_scheds[filtered_size++] = schedules.schedules[i];
                }
            }
            display_filtered_schedules((filtered_size), filtered_scheds);
            break;
        }else if (choice == 4)
        {
            display_schedules(scheds);
            break;
        }
        else
        {
            display_error("Invalid Filter Choice!");
            display_schedules(scheds);
        }
        break;
    case 3:
        return;
    default:
        display_error("Invalid Choice!");
        display_schedules(scheds);
    }
}
void display_filtered_schedules(int size, Schedule scheds[])
{
    cin.ignore();
    clear_screen();
    char con;
    header("Filtered Schedules");
    cout << setw(6) << left << "NO."
         << setw(30) << left << "NAME"
         << setw(7) << left << "AGE"
         << setw(12) << left << "GENDER"
         << setw(20) << left << "ADDRESS"
         << setw(18) << "DATE" << endl
         << endl;
    for (int i = 0; i < size; i++)
    {
        cout << setw(6) << left << i + 1
             << setw(30) << left << scheds[i].patient.name
             << setw(7) << left << scheds[i].patient.age
             << setw(12) << left << (scheds[i].patient.gender == 0 ? "MALE" : "FEMALE")
             << setw(20) << left << scheds[i].patient.address
             << setw(18) << scheds[i].date << endl;
    }
    cout << endl;
    cout << "*******************" << endl;
    cout << "enter 1 continue..." << endl;
    cout << ">> ";
    cin >> con;
    cin.ignore();
    display_schedules(schedules.schedules);
}

void selected_schedule(int index)
{
    int choice;
    clear_screen();

    header("Schedule Number: " + to_string(index));
    cout << setw(6) << left << "NO."
         << setw(30) << left << "NAME"
         << setw(7) << left << "AGE"
         << setw(12) << left << "GENDER"
         << setw(20) << left << "ADDRESS"
         << setw(18) << "DATE" << endl
         << endl;
    cout << setw(30) << left << schedules.schedules[index - 1].patient.name
         << setw(7) << left << schedules.schedules[index - 1].patient.age
         << setw(12) << left << (schedules.schedules[index - 1].patient.gender == 0 ? "MALE" : "FEMALE")
         << setw(20) << left << schedules.schedules[index - 1].patient.address
         << setw(18) << schedules.schedules[index - 1].date << endl;
    cout << "*******************" << endl;
    cout << "1. Delete Record" << endl;
    cout << "2. Mark as Done" << endl;
    cout << ">> ";
    cin >> choice;
    if (choice == 1)
    {
        cout << "Are you sure want to delete this schedule [0]NO | [1]YES? " << endl;
        cout << ">> ";
        cin >> choice;
        if (choice == 0)
        {
            selected_schedule(index);
        }
        else if (choice == 1)
        {
            cout << "Deleting schedule..." << endl;
            schedules.delete_schedule(index);
            this_thread::sleep_for(chrono::seconds(1));
            cout << "Schedule Deleted!" << endl;
            display_schedules(schedules.schedules);
        }
        else
        {
            display_error("Invalid Choice!");
            selected_schedule(index);
        }
    }
    else if (choice == 2)
    {
        cout << "Marking schedule as done..." << endl;
        schedules.schedules[index - 1].isFinished = true;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Schedule Marked as Done!" << endl;
        display_schedules(schedules.schedules);
    }
}
void add_schedule()
{
    clear_screen();
    cin.ignore();
    header("Add New Schedule");
    Schedule schedule;
    string name, address, date;
    int age;
    int gender;
    cout << "** Patient Information **" << endl;
    cout << "Enter Name\t\t: ";
    getline(cin, name);
    cout << "Enter Age\t\t: ";
    cin >> age;
    cout << "Enter Gender [0]M [1]F\t: ";
    cin >> gender;
    cin.ignore();
    cout << "Enter Address\t\t:";
    getline(cin, address);
    cout << endl;
    cout << "** Date of Appointment **" << endl;
    cout << "Enter Date mm/dd/yyyy\t: ";
    cin >> date;
    if (!schedules.is_date_available(date))
    {
        cout << "Date is already taken!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        add_schedule();
    }
    schedule.patient.name = name;
    schedule.patient.age = age;
    schedule.patient.address = address;
    schedule.patient.gender = gender;
    schedule.isFinished = false;
    schedule.date = date;
    schedules.add(schedule);
}
void delete_schedule()
{
}
void search_schedule() {}
bool check_date()
{
    return true;
}
void clear_screen() { system("cls"); }
void display_error(string error)
{
    cout << "** " << error << " ** " << endl;
    this_thread::sleep_for(chrono::seconds(1));
}