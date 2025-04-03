#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
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
};

int main_menu();
void display_schedules();
void add_schedule();
void delete_schedule();
void search_schedule();
bool check_date();
void line();
void header(string);
void clear_screen();
void display_error(string error);

Schedules schedules;

int main()
{
    int choice;
loop:
    choice = main_menu();
    switch (choice)
    {
    case 1:
        display_schedules();
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
void display_schedules()
{
    clear_screen();
    int choice;
    header("Schedules");
    if (!schedules.isEmpty())
    {
        cout << setw(30) << left << "NAME"
             << setw(7) << left << "AGE"
             << setw(12) << left << "GENDER"
             << setw(20) << left << "ADDRESS"
             << setw(18) << "DATE" << endl << endl;
        for (int i = 0; i < schedules.size; i++)
        {
            cout << setw(30) << left << schedules.schedules[i].patient.name
                 << setw(7) << left << schedules.schedules[i].patient.age
                 << setw(12) << left << (schedules.schedules[i].patient.gender == 0 ? "MALE" : "FEMALE")
                 << setw(20) << left << schedules.schedules[i].patient.address
                 << setw(18) << schedules.schedules[i].date << endl;
        }
    }
    else
    {
        cout << "No Schedules." << endl;
    }
    cout << endl;
    cout << "*******************" << endl;
    cout << "1. Select Schedule" << endl;
    cout << "2. Back" << endl;
    cout << ">> ";
    cin >> choice;
    if (choice == 1)
    {
    }
    else if (choice == 2)
    {
        return;
    }
    else
    {
        display_error("Invalid Choice!");
        display_schedules();
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
    cout << "Enter Name\t: ";
    getline(cin, name);
    cout << "Enter Age\t: ";
    cin >> age;
    cout << "Enter Gender\t: ";
    cin >> gender;
    cin.ignore();
    cout << "Enter Address\t:";
    getline(cin, address);
    cout << endl;
    cout << "** Date of Appointment **" << endl;
    cout << "Enter Date mm/dd/yyyy\t: ";
    cin >> date;
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