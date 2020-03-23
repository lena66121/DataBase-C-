#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Data.h"

using namespace std;


//----------functions that is responsible for outputting data-----------
void HeaderTable () {
  cout<<"--------------------------------------------------------------";
  cout<<"------------------------------------------------"<<endl;
  
    cout<< left
    <<"|"<< setw(15) << "SURNAME"
    <<"|"<<setw(15) << "NAME"
    <<"|"<< setw(15) << "PATRONYMIC"
    <<"|"<< setw(12) << "DATE"
    <<"|"<< setw(15) << "IDENT CODE"
    <<"|"<< setw(15) << "PASSPORT ID"
    <<"|"<< setw(15) << "EMPLOYMENT ID"
    <<"|"<<endl;

  cout<<"-------------------------------------------------------------";
  cout<<"-------------------------------------------------"<<endl;
}


void PrintData (const vector<PersonInfo>& vector) {

    if (vector.size() != 0) {

      HeaderTable();

      for (auto person : vector) {
        cout<< left
        <<"|"<< setw(15) << person.personal_info.surname
        <<"|"<<setw(15) << person.personal_info.name
        <<"|"<< setw(15) << person.personal_info.patronymic
        <<"|"<< setw(2) << person.date_of_birth.day 
        << setw(1) <<"/"
        << setw(2) << person.date_of_birth.month 
        << setw(1) <<"/"
        << setw(6) << person.date_of_birth.year
        <<"|"<< setw(15) << person.identification_code
        <<"|"<< setw(15) << person.passport_id
        <<"|"<< setw(15) << person.employment_history_id
        <<"|"<<endl;
        cout<<"-------------------------------------------------------------";
        cout<<"-------------------------------------------------"<<endl;
      }

    } else {
        cout<<endl<<"DATA BASE IS EMPTY "<<endl;
        cout<<endl;
    }
}



//----------functions that is responsible for writing or reading a date-----------

void DataEntry (vector<PersonInfo>& vector) {

   Initials personal_info;
   Date date_of_birth;
   string passport_id, employment_history_id, identification_code;
   int n;
   char s;

   cout<<"How many persons are you going to add: "; cin >> n;

   for (int i = 1; i <= n; i++) {

     cout<<endl;
     cout<<"SURNAME: "; cin >> personal_info.surname;
     cout<<"NAME: "; cin >> personal_info.name;
     cout<<"PATRONYMIC: "; cin >> personal_info.patronymic;
     cout<<"DATE OF BIRTH (DD/MM/YYYY): "; 
     cin >> date_of_birth.day >> s >> date_of_birth.month >> s >> date_of_birth.year;
     cout<<"IDENTIFICATION CODE (12 signs): "; cin >> identification_code;
     cout<<"PASSPORT ID (9 signs): "; cin >> passport_id;
     cout<<"EMPLOYMENT HISTORY ID (10 signs): "; cin >> employment_history_id;

     cout<<endl;

     // Validation of the entered data
     if (date_of_birth.day < 0 || date_of_birth.month < 0 || date_of_birth.year < 0 || date_of_birth.day > 31 || date_of_birth.month > 12) {
        cout<<"Incorrect date of birth. Try again."<<endl<<endl;
        system("pause");
     } else if (identification_code.size() > 12 || passport_id.size() > 9 || employment_history_id.size() > 11) {
        cout<<"Incorrect date of documents. Try again."<<endl<<endl;
        system("pause");
     } else {
        PersonInfo newPerson = {personal_info, date_of_birth, identification_code, passport_id, employment_history_id};
        vector.push_back(newPerson);
     }

    cout<<endl;
   }
   system("cls");
   PrintData(vector);
   system("pause");
}


void ReadFromFile (ifstream& stream, vector<PersonInfo>& vector) {

    Initials personal_info;
    Date date_of_birth;
    string identification_code, passport_id, employment_history_id;

    if (stream.is_open()) {

        while (!stream.eof()) {
           // read surname, name, patronymic
           getline(stream, personal_info.surname, ' ');
           getline(stream, personal_info.name, ' ');
           getline(stream, personal_info.patronymic);
       
           // read date of birth
           stream >>  date_of_birth.day; 
           stream.ignore(1);
           stream >>  date_of_birth.month; 
           stream.ignore(1);
           stream >>  date_of_birth.year;
           stream.ignore(1);
       
           // read unique codes of documents
           getline(stream, identification_code);
           getline(stream, passport_id);
           getline(stream, employment_history_id);
       
           PersonInfo new_unemployed = {personal_info, date_of_birth, identification_code, passport_id, employment_history_id};
           if (personal_info.surname.size() != 1) vector.push_back(new_unemployed);
        }
        stream.close();

    } else {
        cout<<endl<<"File is not open or does not exist"<<endl<<endl;
    } 
}


void WriteToFile (ofstream& stream, const vector<PersonInfo>& vector) {

        for (auto unemployed : vector) {
        stream << unemployed.personal_info.surname << " " 
        << unemployed.personal_info.name << " "
        << unemployed.personal_info.patronymic << '\n';

        stream << unemployed.date_of_birth.day << "/" 
        << unemployed.date_of_birth.month << "/"
        << unemployed.date_of_birth.year << '\n';

        stream << unemployed.identification_code << "\n";
        stream << unemployed.passport_id << "\n";
        stream << unemployed.employment_history_id << "\n";
    }

    stream.close(); 
}



//--------function that is responsible for removing a person by the identification code-----------

void UnemployedDeletion (vector<PersonInfo>& vector) {
    string identification_code;
    cout<<"Enter the identification code of unemployed you want delete: "; cin>>identification_code;

    int count = 0;
    for (auto unemployed : vector) {
        if(unemployed.identification_code == identification_code) {
            cout<<endl<<unemployed.personal_info.surname
            <<" "<<unemployed.personal_info.name
            <<" "<<unemployed.personal_info.patronymic
            <<" "<<"successfully deleted."<<endl<<endl;
            vector.erase(vector.begin() + count);
            system("pause");
            return;
        }
       count++;
    }
    cout<<"Such an unemployed does not exist."<<endl<<endl;
    system("pause");
}



//----------functions that is responsible for sorting by criteria-----------

void SortBySurname (vector<PersonInfo>& vector) {

   sort(begin(vector), end(vector), [](PersonInfo first, PersonInfo second) {
        if(first.personal_info.surname < second.personal_info.surname) {return true;}
        return false;
   });

   system("cls");
   PrintData(vector);
   system("pause");
}


void SortByDateOfBirth (vector<PersonInfo>& vector) {

   sort(begin(vector), end(vector), [](PersonInfo first, PersonInfo second) {
       int firstNumber = first.date_of_birth.day + first.date_of_birth.month*100 + first.date_of_birth.year*1000;
       int secondNumber = second.date_of_birth.day + second.date_of_birth.month*100 + second.date_of_birth.year*1000;      
        if(firstNumber < secondNumber) {return true;}
        return false;
   });
   system("cls");
   PrintData(vector);
   system("pause");
}




//----------functions that is responsible for searching by criteria-----------

void SearchBySurname (const vector<PersonInfo>& data_vector) {
    string surname;
    vector<PersonInfo> new_vector;
    cout<<"Enter the surname you are looking for: "; cin>>surname;

    for_each(surname.begin(), surname.end(), [](char & c) {
		c = tolower(c);
	});
 

    for (auto unemployed : data_vector) {

        for_each(unemployed.personal_info.surname.begin(), unemployed.personal_info.surname.end(), [](char & c) {
		   c = tolower(c);
	    });

        if(unemployed.personal_info.surname == surname) {

            for_each(unemployed.personal_info.surname.begin(), unemployed.personal_info.surname.begin() + 1, [](char & c) {
		         c = toupper(c);
	        });

            new_vector.push_back(unemployed);
        }
    }

    if (new_vector.size() != 0) {
      system("cls");
      PrintData(new_vector);
      system("pause");
    } else {
        cout<<endl<<"Not found"<<endl<<endl;
        system("pause");
    }
    
}


void SearchByEmploymentHistory (const vector<PersonInfo>& data_vector) {
    string employment_history_id;
    vector<PersonInfo> new_vector;
    cout<<"Enter the employment history ID you are looking for: "; cin>>employment_history_id;
 

    for (auto unemployed : data_vector) {

        if(unemployed.employment_history_id == employment_history_id) {
            new_vector.push_back(unemployed);
        }
    }

    if (new_vector.size() != 0) {
      system("cls");
      PrintData(new_vector);
      system("pause");
    } else {
        cout<<endl<<"Not found"<<endl<<endl;
        system("pause");
    }
}


void SearchByPassportId (const vector<PersonInfo>& data_vector) {
    string passport_id;
    vector<PersonInfo> new_vector;
    cout<<"Enter the passport ID you are looking for: "; cin>>passport_id;
 

    for (auto unemployed : data_vector) {

        if(unemployed.passport_id == passport_id) {
            new_vector.push_back(unemployed);
        }
    }

    if (new_vector.size() != 0) {
      system("cls");
      PrintData(new_vector);
      system("pause");
    } else {
        cout<<endl<<"Not found"<<endl<<endl;
        system("pause");
    }
}

