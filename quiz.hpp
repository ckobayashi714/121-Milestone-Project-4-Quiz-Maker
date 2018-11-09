// Filename: quiz.hpp
#pragma once

// #ifndef QUIZ_HPP
// #define QUIZ_HPP

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Definition of the class Question.
class question {
private:
  string _text;
  string _answer;

public:
  void set_text(string text) { _text = text; }
  void set_answer(string answer) { _answer = answer; }
  string text() { return _text; }
  string answer() { return _answer; }
};
question create_question();

void display_questions(question qArray[], int size);

void save_questions(question qArray[], int size, string filename);

void load_questions(question qArray[], int *size, string filename);

// #endif
