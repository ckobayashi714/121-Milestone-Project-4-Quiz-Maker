# QuizMaker Project Milestone 4

This is milestone 4 of the [QuizMaker Project](https://docs.google.com/document/d/1kxz9GX_Fm1rGeQZCyvOVQ7Szpre8MZwEgXG5zyMIcI8/edit?usp=sharing).

# Requirements
This milestone adds a new function for loading questions from a text file. The
program should be capable of loading existing questions so that you can continue
adding questions, display the list of all questions, and save the updated list
of questions.

## Loading questions
Create a `load_questions` function that accepts three parameters: a `question`
array, the size of the array, and the filename of the text file containing
questions.

The function performs the opposite of the `save_questions` function where it
loads the contents of the file and stores it into an array. Specifically, the
function should open the file according to the `filename` passed as a parameter.
The data from the file should be stored into the `question` array also passed as
a parameter.

In order for the program to work with the other previously created
functionalities, the data should be properly passed between `main` and
`load_questions`. The `questions` array passed to the function should be the
same array in the `main` function so that changes to the array are reflected
properly. Our discussions on arrays and how they are pointers in disguise will
help you understand how this works.

Another aspect to consider for this milestone is that the size (number of
elements) should change according to the number of elements in the text file. If
you recall, size is declared in the `main` function, but it should change
after calling this function. Therefore, the size parameter in `load_questions` 
should be declared as a pointer so that the change in size is als reflected in 
`main`. Take note that size is the number of elements and not the capacity of the 
array which is 100.

Finally, calling `load_questions` should overwrite the contents of the `question`
array in `main`. For example, if the array contained five questions, but the
file contains three questions, then the array and the size variables should be
changed appropriately so that when `display_questions` is called, it will only
show the three questions loaded from the file.

We will use the same file format as in Milestone 3.

### Sample text file
```
3
[SQ]
Who is the mother of the COBOL programming language?
Grace Hopper
[SQ]
Who developed C++?
Bjarne Stroustrup
[SQ]
Who developed the Ruby programming language?
Yukihiro Matsumoto
```

## Updated menu
The menu that your program uses should be updated to include the option to load
a question. When the user selects the option to load a file, it should ask the
user to provide a filename (inside `main`). The filename is used as a parameter
for calling the `load_questions` function. Take a look at the sample output
below.

### Sample output
```
Welcome to QuizMaker

What would you like to do?
a. Create a question
b. Display questions
c. Save questions
d. Load questions
e. Quit
Choice: d

What file would you like to load? questions.txt
File loaded successfully!

What would you like to do?
a. Create a question
b. Display questions
c. Save questions
d. Load questions
e. Quit
Choice: b

Question and Answer list
1. Who is the mother of the COBOL programming language?
Answer: Grace Hopper
2. Who developed C++?
Answer: Bjarne Stroustrup
3. Who developed the Ruby programming language?
Answer: Yukihiro Matsumoto

What would you like to do?
a. Create a question
b. Display questions
c. Save questions
d. Load questions
e. Quit
Choice: a

Please enter your question: Who developed Java?
Please enter the answer: James Gosling
Question added!

What would you like to do?
a. Create a question
b. Display questions
c. Save questions
d. Load questions
e. Quit
Choice: b

Question and Answer list
1. Who is the mother of the COBOL programming language?
Answer: Grace Hopper
2. Who developed C++?
Answer: Bjarne Stroustrup
3. Who developed the Ruby programming language?
Answer: Yukihiro Matsumoto
4. Who developed Java?
Answer: James Gosling

What would you like to do?
a. Create a question
b. Display questions
c. Save questions
d. Load questions
e. Quit
Choice: c

What filename would you like to use? questions.txt
File saved successfully!

What would you like to do?
a. Create a question
b. Display questions
c. Save questions
d. Load questions
e. Quit
Choice: e

Thank you for using QuizMaker!
```

Place the function prototypes and classes in `quiz.hpp`, the function
implementations in `quiz.cpp`, and the main function in `quizgen.cpp`.

# Coding style
We are rolling out a CSUF coding style that we have been using in class. Please
use this new style for this milestone and your following milestones. See [CSUF C++ Style Guide](https://drive.google.com/file/d/1KmXTwiDfpGUN-5GTVZn_xfwJ4yXDMJ4k/view?usp=sharing).

# Documentation
See [google's style guide](https://google.github.io/styleguide/cppguide.html#Comments) for
commenting details.

*Take note that we only use th Google document for commenting
style and not coding style.*

## File comments
Describe the contents of the file on the first line. For example:

```cpp
// This file implements a simple calculator
```

## Function comments
Describe the use of the function and how it is implemented if it is non-obvious. For example:

```cpp
// Displays a greeting on the command line using the name parameter.
void show_greeting(string name) {
  // ...
}
```

## Implementation comments
Provide comments in tricky, non-obvious, interesting, or important parts of your code.

```cpp
// Compute the distance between two points using the distance formula
// sqrt((x1-x2)^2 + (y1-y2)^2)
double dist = sqrt(pow(x1 - x2, 2) + pow(y1-y2, 2));
```

# Code evaluation
Open the terminal and navigate to the folder that contains this milestone. Assuming you have pulled the code inside of `/home/student/project01-tuffy` and you are currently in `/home/student` you can issue the following commands

```
cd project01-tuffy
```

Use the `g++` command to compile your code and the `./` command to run it. The sample commands below shows how you would compile code save in `quizgen.cpp` and into the executable file `quizgen`. Make sure you use the correct filenames required in this problem.  Take note that if you make any changes to your code, you will need to compile it first before you see changes when running it.

```
g++ -std=c++17 quizgen.cpp quiz.cpp -o quizgen
./quizgen
```

You can run one, two, or all the commands below to `test` your code, `stylecheck` your code's design, or `formatcheck` your work. Kindly make sure that you have compiled and executed your code before issuing any of the commands below to avoid errors.

```
make test
make stylecheck
make formatcheck
```

A faster way of running all these tests uses the `all` parameter.

```
make all
```

# Submission
1. When everything runs correctly, let's copy your code into the Github repository. The first step is to add your code to what is called the staging area using git's `add` command. The parameter after `add` is the name of the file you want to add. There are cases when you have multiple changed files, so you can just type . (period) to add all modified files.

    ```
    git add .
    ```

1. Once everything is in the staging area, we use the `commit` command to tell git that we have added everything we need into the staging area.

    ```
    git commit
    ```

1. In case it asks you  to configure global variables for an email and name, just copy the commands it provides then replace the dummy text with your email and Github username.

    ```
    git config --global user.email "tuffy@csu.fullerton.edu"
    git config --global user.name "Tuffy Titan"
    ```

    When you're done, make sure you type `git commit` again.   

1. Git will ask you to describe what you have added to the staging area. By default, you will use a command-line based editor called *nano*. Go ahead and provide a description then press <kbd>Ctrl</kbd> + <kbd>x</kbd> to exit. Press <kbd>Y</kbd> to confirm that you want to make changes and then press <kbd>Enter</kbd>.

1. Lets push all changes to the Github repository using git's `push` command. Provide your Github username and password when you are asked.

    ```
    git push
    ```

1. When you finish the exercise, go back to Titanium and click on the `Add submission` button in the project milestone page. Provide a short message in the text area such as "finished milestone" and click on `Save changes`. Finally click on `Submit assignment` to inform your instructor that you are done.
