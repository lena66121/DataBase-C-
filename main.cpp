#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Functions.h"

using namespace std;


// global variables
int _stateMenu;
string path_to_file = "data.txt";


void Menu() {
  cout<< "What are you going to do: " << endl
  
  << "(1) Data input" << endl
  << "(2) Data output" << endl
  << "(3) Adding data" << endl
  << "(4) Data deletion" << endl
  << "(5) Data sorting" << endl
  << "(6) Data search" << endl
  << "(0) Exit" << endl
  << "Your choice: "; 
  cin>> _stateMenu;
}



int main()
{
  Menu();
  int _actions;

  vector<PersonInfo> data;

  while (_stateMenu != 0) {

    switch(_stateMenu) {
      //------------------CASE 1-------------------
      case 1:
      system("cls");
      cout<<"Enter data manually (1) or read from a file (2): "; cin >> _actions;

      if (_actions == 1) {
          DataEntry(data);
      } else if (_actions == 2) {

        ifstream output(path_to_file);
        ReadFromFile(output, data);
        system("cls");
        PrintData(data);
        system("pause");

      } else {

        cout << "Unknown option!"<<endl;
        _actions = 0;  
        system("pause");

      }
      system("cls");
      Menu();
      break;

      //------------------CASE 2-------------------
      case 2:
      system("cls");
      PrintData(data);
      system("pause");
      system("cls");
      Menu();
      break;

      //------------------CASE 3-------------------
      case 3:
      system("cls");
      DataEntry(data);
      system("cls");
      Menu();
      break;

      //------------------CASE 4-------------------
      case 4:
      system("cls");
      UnemployedDeletion(data);
      system("cls");
      Menu();
      break;

      //------------------CASE 5-------------------
      case 5:
      cout<<"Do you want to sort by surname (1) or date of birth (2): "; cin >> _actions;
      if (_actions == 1) {
        SortBySurname(data);
      } else if (_actions == 2) {
        SortByDateOfBirth(data);
      } else {
        cout << "Unknown option!"<<endl;
        _actions = 0;  
        system("pause");
      }
      system("cls");
      Menu();
      break;

      //------------------CASE 6-------------------
      case 6:
     cout<<"Do you want to search by surname (1), employment history ID (2) or passport ID (3): "; cin >> _actions;
      if (_actions == 1) {
        SearchBySurname(data);
      } else if (_actions == 2) {
        SearchByEmploymentHistory(data);
      } else if (_actions == 3) {
        SearchByPassportId(data);
      } else {
        cout << "Unknown option!"<<endl;
        _actions = 0;  
        system("pause");
      }
      system("cls");
      Menu();
      break;

      default:
		    cout << "Error! Unknown option"<<endl;
	 	   break;
    }
  }

  cout<<"Do you want to save data to a file (1/0)?  ";  cin >> _actions;

  if (_actions == 1) {
    ofstream input(path_to_file);
    WriteToFile(input, data);
    cout<<endl<<"Done! Thank you for using our database!"<<endl<<endl;
  } else {
    cout<<endl<<"OK. Thank you for using our database!"<<endl<<endl;
  }

  system("pause");
  return 0;
}









  