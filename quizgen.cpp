#include "quiz.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
  /* This will create an array of 100 question objects*/
  question q;
  question qArray[100];
  /* This program will reapteadly ask the user to input a question or exit. If
  the user inputs something other than a or b (capital letters too), they will
  be notified with an invalid message, but will then be asked again what option
  they would like to choose.*/
  string filename;
  char choice;
  int size = 0;
  cout << "Welcome to QuizMaker\n\n";

  do {
    cout << "What would you like to do?\n"
         << "a. Create a question\n"
         << "b. Display questions\n"
         << "c. Save questions\n"
         << "d. Load questions\n"
         << "e. Quit\n"
         << "Choice: ";
    cin >> choice;
    cin.ignore();
    cout << endl;
    switch (choice) {
    case 'a':
    case 'A':
      qArray[size] = create_question();
      // cout << qArray[size].text();
      // cout << qArray[size].answer();
      size++;
      break;
    case 'b':
    case 'B':
      display_questions(qArray, size);
      break;
    case 'c':
    case 'C':
      cout << "What filename would you like to use? ";
      getline(cin, filename);
      save_questions(qArray, size, filename);
      break;
    case 'd':
    case 'D':
      cout << "What file would you like to load? ";
      getline(cin, filename);
      load_questions(qArray, &size, filename);
      break;
    case 'e':
    case 'E':
      break;
    default:
      cout << "Invalid option\n\n";
    }
  } while (choice != 'e' && choice != 'E');
  cout << "Thank you for using QuizMaker!\n";
  return 0;
}
