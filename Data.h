#include <iostream>
#include <string>


using namespace std;

struct Initials {
    string  surname, name, patronymic;
};

struct Date {
    int day = 0, month = 0, year = 0;
};

struct PersonInfo {
   Initials personal_info;
   Date date_of_birth;
   string identification_code;
   string passport_id;
   string employment_history_id;
};