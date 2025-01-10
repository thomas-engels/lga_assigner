# Struggle to quickly assign the LGA questions?


*You might find this script useful. Accounts for question difficulty, three people per question, any group size, any number of questions.*

---

## Usage:
1. clone the repository
2. compile with `g++ main.cpp -o <file_name>`
3. create at least 2 text files one with the names and one with question numbers. names.txt:
```
Charlotte
Adiline
Simon
Justin
Benny
```
easy_questions.txt:
```
1 2 3 4 5
```
intermeadiate_questions.txt
```
7 8 9
```
4. then run the program like `<executable_name> names.txt <all the question files>` ex: `./main names.txt easy_questions.txt intermediate_questions.txt hard_questions.txt`