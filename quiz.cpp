// Filename quiz.cpp
#include "quiz.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

question create_question() {
  question q;
  string text, answer;
  cout << "Please enter your question: ";
  getline(cin, text);
  cout << "Please enter the answer: ";
  getline(cin, answer);
  q.set_text(text);
  q.set_answer(answer);
  cout << "Question added!\n\n";
  return q;
}
void display_questions(question qArray[], int size) {
  cout << "Question and Answer list\n";
  for (int i = 0; i < size; i++) {
    cout << (i + 1) << ". " << (qArray + i)->text() << "\n"
         << "Answer: " << (qArray + i)->answer() << "\n";
    // cout << (i + 1) << ". " << qArray[i].text() << "\n";
    // cout << "Answer: " << qArray[i].answer() << "\n";
  }
  cout << "\n";
}
void save_questions(question qArray[], int size, string filename) {
  ofstream outfile;
  outfile.open(filename);
  outfile << size << "\n";
  for (int i = 0; i < size; i++) {
    // outfile << "[SQ]\n";
    //         << (qArray + i)->text() << "\n"
    //         << (qArray + i)->answer() << "\n";
    outfile << "[SQ]" << endl;
    outfile << qArray[i].text() << endl;
    outfile << qArray[i].answer() << endl;
  }
  outfile.close();
  cout << "File saved successfully!\n\n";
}
void load_questions(question qArray[], int *size, string filename) {
  ifstream infile;
  infile.open(filename);
  if (infile.is_open()) {
    string trash;
    string a, q;
    infile >> *size;
    infile.ignore();
    for (int i = 0; i < *size; i++) {
      getline(infile, trash);
      getline(infile, q);
      getline(infile, a);
      (*(qArray + i)).set_text(q);
      (*(qArray + i)).set_answer(a);
    }
  }
  infile.close();
  cout << "File loaded successfully!\n\n";
}
