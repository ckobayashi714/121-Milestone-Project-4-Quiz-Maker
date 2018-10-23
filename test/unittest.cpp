#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <cstdio>
#include <cstring>
#include "gtest_ext.h"
#include "../quiz.hpp"
using ::testing::HasSubstr;
using ::testing::StartsWith;
using ::testing::MatchesRegex;
using ::testing::ContainsRegex;

TEST(Quiz, PublicMethodsPresent) {
  question q;
  ASSERT_NO_THROW({
    q.text();
    q.answer();
    q.set_text("a");
    q.set_answer("b");
  });
}

TEST(Quiz, MutatorsAndAccessors) {
  question q;
  std::string text, answer;
  text = generate_string(10);
  answer = generate_string(10);
  ASSERT_NO_THROW({
    q.set_text(text);
    q.set_answer(answer);
  });
  ASSERT_EQ(q.text(), text);
  ASSERT_EQ(q.answer(), answer);
}

TEST(Quiz, CreateQuestion) {
  for(int i = 0; i < 10; i++) {
    std::string text, answer;
    text = generate_string(10);
    answer = generate_string(10);
    question temp, actual;
    temp.set_text(text);
    temp.set_answer(answer);
    std::string input = text+"\n"+answer;
    SIMULATE_CIN(input, {
      actual = create_question();
    });
    ASSERT_EQ(temp.text(), actual.text());
    ASSERT_EQ(temp.answer(), actual.answer());
  }
}


TEST(Quiz, SaveQuestion) {
  for(int i = 0; i < 10; i++) {
    int repetitions = rand() % 10 + 1;
    question questions[repetitions];
    for (int i = 0; i < repetitions; i++) {
      std::string text, answer;
      text = generate_string(10);
      answer = generate_string(10);
      questions[i].set_text(text);
      questions[i].set_answer(answer);
    }
    std::string filename = generate_string(5) + ".txt";
    ASSERT_DURATION_LE(3, {
      ASSERT_SIO_EQ("", "File saved successfully!\n\n", {
        save_questions(questions, repetitions, filename);
      });
    });
    ifstream test_file(filename.c_str());
    ASSERT_TRUE(test_file.good());
    remove(filename.c_str());
  }
}

TEST(Quiz, SaveFileFormat) {
  for(int i = 0; i < 10; i++) {
    int repetitions = rand() % 10 + 1;
    question questions[repetitions];
    std::string expected = std::to_string(repetitions) + "\n";
    for (int j = 0; j < repetitions; j++) {
      std::string text, answer;
      text = generate_string(10);
      answer = generate_string(10);
      questions[j].set_text(text);
      questions[j].set_answer(answer);
      expected += "[SQ]\n";
      expected += text + "\n";
      expected += answer + "\n";
    }

    std::string filename = generate_string(5) + ".txt";
    ASSERT_DURATION_LE(3, {
      ASSERT_SIO_EQ("", "File saved successfully!\n\n", {
        save_questions(questions, repetitions, filename);
      });
    });

    ifstream save_file(filename);
    ASSERT_TRUE(save_file.good()) << "Save file was not created";
    std::string file_contents, temp_holder;
    while(save_file >> temp_holder) {
      file_contents += temp_holder + "\n";
    }
    save_file.close();
    remove(filename.c_str());

    ASSERT_EQ(file_contents, expected);
  }
}

TEST(Quiz, LoadQuestions) {
  for(int i = 0; i < 10; i++) {
    int file_questions_size = rand() % 10 + 1;
    question file_questions[file_questions_size];
    std::string file_contents = std::to_string(file_questions_size) + "\n";
    for (int j = 0; j < file_questions_size; j++) {
      std::string text, answer;
      text = generate_string(10);
      answer = generate_string(10);
      file_questions[j].set_text(text);
      file_questions[j].set_answer(answer);
      file_contents += "[SQ]\n";
      file_contents += text + "\n";
      file_contents += answer + "\n";
    }

    std::string filename = generate_string(5) + ".txt";
    ofstream out_file(filename);
    out_file << file_contents;
    out_file.close();

    question question_list[100];
    int size = 0;
    ASSERT_DURATION_LE(3, {
      ASSERT_SIO_EQ("", "File loaded successfully!\n\n", {
        load_questions(question_list, &size, filename);
      });
    });
    ASSERT_EQ(size, file_questions_size);
    for (int j = 0; j < file_questions_size; j++) {
      ASSERT_EQ(question_list[j].text(), file_questions[j].text());
      ASSERT_EQ(question_list[j].answer(), file_questions[j].answer());
    }

    remove(filename.c_str());

  }
}

TEST(Quiz, DisplayQuestions) {
  for(int i = 0; i < 10; i++) {
    int repetitions = rand() % 10 + 1;
    question questions[repetitions];
    std::string expected = "Question and Answer list\n";
    for (int i = 0; i < repetitions; i++) {
      std::string text, answer;
      text = generate_string(10);
      answer = generate_string(10);
      questions[i].set_text(text);
      questions[i].set_answer(answer);
      expected += std::to_string(i+1) + ". "+ text +"\nAnswer: "
                  + answer + "\n";
    }
    expected += "\n";
    ASSERT_DURATION_LE(3, {
      ASSERT_SIO_EQ("", expected, display_questions(questions, repetitions));
    });
  }
}


TEST(Quiz, CreateQuestionChoice) {
  std::string expected = "Welcome to QuizMaker\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nPlease enter your question: Please enter the "
                         "answer: Question added!\n\nWhat would you like to do?"
                         "\na. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit"
                         "\nChoice: \nThank you for using QuizMaker!\n";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECIO_EQ("quizgen", "a\nX\nX\ne", expected);
  });
}

TEST(Quiz, FiniteChoiceLoop) {
  srand (time(NULL));
  ASSERT_DURATION_LE(3, {
    main_output("quizgen", "a\nX\nX\ne");
  });
}

TEST(Quiz, DisplayQuestionsChoice) {
  std::string expected = "Welcome to QuizMaker\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nPlease enter your question: Please enter the "
                         "answer: Question added!\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nQuestion and Answer list\n1. X\nAnswer: X"
                         "\n\nWhat would you like to do?\na. Create a question"
                         "\nb. Display questions\nc. Save questions\nd. Load "
                         "questions\ne. Quit\nChoice: \nThank you for using "
                         "QuizMaker!\n";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECIO_EQ("quizgen", "a\nX\nX\nb\ne", expected);
  });
}

TEST(Quiz, SaveQuestionsChoice) {
  std::string expected = "Welcome to QuizMaker\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nWhat filename would you like to use? File "
                         "saved successfully!\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nThank you for using QuizMaker!\n";
  string filename = generate_string(5) + ".txt";
  string input = "c\n" + filename + "\ne";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECIO_EQ("quizgen", input, expected);
  });
  std::remove(filename.c_str());
}

TEST(Quiz, LoadQuestionsChoice) {
  std::string expected = "Welcome to QuizMaker\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nWhat file would you like to load? File "
                         "loaded successfully!\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nThank you for using QuizMaker!\n";
  string filename = generate_string(5) + ".txt";
  string input = "d\n" + filename + "\ne";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECIO_EQ("quizgen", input, expected);
  });
  std::remove(filename.c_str());
}

TEST(Quiz, QuitChoice) {
  std::string expected = "Welcome to QuizMaker\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nThank you for using QuizMaker!\n";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECIO_EQ("quizgen", "e", expected);
  });
}

TEST(Quiz, InvalidOptionChoice) {
  std::string expected = "Welcome to QuizMaker\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nInvalid option\n\nWhat would you like to "
                         "do?\na. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nThank you for using QuizMaker!\n";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECIO_EQ("quizgen", "x\ne",expected);
  });
}

TEST(Quiz, ChoiceLoopLowercase) {
  int repetitions = rand() % 10 + 1;
  for (int i = 0; i < repetitions; i++) {
    std::string input = "";
    std::string question_list = "Question and Answer list\n";
    std::string expected = "Welcome to QuizMaker\n\n";
    std::vector<std::string> filenames;
    std::string load_file_name = generate_string(10) + ".txt";
    ofstream out_file(load_file_name);
    out_file << 1 << "\n" << "[SQ]\nq\na\n";
    out_file.close();
    int question_ctr = 1;
    char choice;
    do {
      choice = rand() % 5 + 97;
      expected += "What would you like to do?\na. Create a question\n"
                  "b. Display questions\nc. Save questions\nd. Load questions\n"
                  "e. Quit\nChoice: \n";
      std::string s_choice(1, choice);
      input += s_choice + "\\n";
      switch (choice) {
        case 'a':
          expected += "Please enter your question: Please enter the answer: "
                      "Question added!\n\n";
          input += "q\\na\\n";
          question_list += std::to_string(question_ctr) +". q\nAnswer: a\n";
          question_ctr++;
          break;
        case 'b':
          expected += question_list + "\n";
          break;
        case 'c':
          {
            expected += "What filename would you like to use? File saved successfully!\n\n";
            std::string filename = generate_string(5) + ".txt";
            filenames.push_back(filename);
            input += filename+"\n";
            break;
          }
        case 'd':
          {
            expected += "What file would you like to load? File loaded successfully!\n\n";
            input += load_file_name+"\n";
            question_list = "Question and Answer list\n1. q\nAnswer: a\n";
            question_ctr = 2;
            break;
          }
        case 'e':
          expected += "Thank you for using QuizMaker!\n";
          break;
        default:
          expected += "Invalid option\n\n";
      }
    } while(choice!= 'e');
    ASSERT_DURATION_LE(3, {
      ASSERT_EXECIO_EQ("quizgen", input, expected);
    });
    remove(load_file_name.c_str());
    for(std::string fn : filenames) {
      remove(fn.c_str());
    }
  }
}

TEST(Quiz, ChoiceLoopUppercase) {
  int repetitions = rand() % 10 + 1;
  for (int i = 0; i < repetitions; i++) {
    std::string input = "";
    std::string question_list = "Question and Answer list\n";
    std::string expected = "Welcome to QuizMaker\n\n";
    std::vector<std::string> filenames;
    std::string load_file_name = generate_string(10) + ".txt";
    ofstream out_file(load_file_name);
    out_file << 1 << "\n" << "[SQ]\nq\na\n";
    out_file.close();
    int question_ctr = 1;
    char choice;
    do {
      choice = rand() % 5 + 65;
      expected += "What would you like to do?\na. Create a question\n"
                  "b. Display questions\nc. Save questions\nd. Load questions\n"
                  "e. Quit\nChoice: \n";
      std::string s_choice(1, choice);
      input += s_choice + "\\n";
      switch (choice) {
        case 'A':
          expected += "Please enter your question: Please enter the answer: "
                      "Question added!\n\n";
          input += "q\\na\\n";
          question_list += std::to_string(question_ctr) +". q\nAnswer: a\n";
          question_ctr++;
          break;
        case 'B':
          expected += question_list + "\n";
          break;
        case 'C':
          {
            expected += "What filename would you like to use? File saved successfully!\n\n";
            std::string filename = generate_string(5) + ".txt";
            filenames.push_back(filename);
            input += filename+"\n";
            break;
          }
        case 'D':
          {
            expected += "What file would you like to load? File loaded successfully!\n\n";
            input += load_file_name+"\n";
            question_list = "Question and Answer list\n1. q\nAnswer: a\n";
            question_ctr = 2;
            break;
          }
        case 'E':
          expected += "Thank you for using QuizMaker!\n";
          break;
        default:
          expected += "Invalid option\n\n";
      }
    } while(choice!= 'E');
    ASSERT_DURATION_LE(3, {
      ASSERT_EXECIO_EQ("quizgen", input, expected);
    });
    remove(load_file_name.c_str());
    for(std::string fn : filenames) {
      remove(fn.c_str());
    }
  }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
