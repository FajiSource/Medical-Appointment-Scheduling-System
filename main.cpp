#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
using namespace std;

enum Gender
{
    MALE,
    FEMALE
};
struct Patient
{
    string name;
    int age;
    string address;
    Gender gender;
};
struct Schedule
{
    Patient patient;
    bool isFinished;
    string date;
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

queue<Schedule> schedules;

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
    header("Menu");
    cout << "1. View Schedules" << endl;
    cout << "2. Add New Schedule" << endl;
    cout << "3. Search Schedule" << endl;
    cout << "4. Exit" << endl;
    cout << ">> ";
    cin >> choice;
    return choice;
}
void display_schedules() {
    clear_screen();
    int choice;
    queue <Schedule> schedulesCopy = schedules;
    cout << "NAME\t\tAGE\t\tGENDER\t\tADDRESS\t\tDATE" << endl;
    while(!schedulesCopy.empty()){
        Schedule sched = schedulesCopy.front();
        schedulesCopy.pop();
        cout << sched.patient.name 
             <<"\t" << sched.patient.age 
             << "\t\t" << sched.patient.gender 
             << "\t\t" << sched.patient.address
             << "\t" << sched.date 
             << endl;
    }
    cout << ">> ";
    cin >> choice;
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
    schedule.patient.gender = gender == 0 ? MALE : FEMALE;
    schedule.isFinished = false;
    schedule.date = date;
    schedules.push(schedule);
}
void delete_schedule() {

}
void search_schedule() {}
bool check_date() { 
    return true;
}
void clear_screen() { system("cls"); }
void display_error(string error)
{
    cout << "** " << error << " ** " << endl;
    this_thread::sleep_for(chrono::seconds(1));
}