#include <iostream>
#include <vector>
using namespace std;

enum Gender{
    MALE,
    FEMALE
};
struct Patient{
    string name;
    int age;
    string address;
    Gender gender;

};
struct Appoinment{
        Patient patient;
        bool isFinished = false;
};

void display_options(){}
void display_schedules(){}
void add_schedule(){}
void delete_schedule(){}
void search_schedule(){}

vector <Appoinment> appointments;

int main() {    
    
    return 0;
}

void display_options(){}
void display_schedules(){}
void add_schedule(){}
void delete_schedule(){}
void search_schedule(){}
